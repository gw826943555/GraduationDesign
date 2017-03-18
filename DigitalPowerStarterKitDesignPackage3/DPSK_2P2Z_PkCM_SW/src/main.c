////////////////////////////////////////////////////////////////////////////////
// © 2015 Microchip Technology Inc.
//
// MICROCHIP SOFTWARE NOTICE AND DISCLAIMER:  You may use this software, and any 
//derivatives, exclusively with Microchip?s products. This software and any 
//accompanying information is for suggestion only.  It does not modify Microchip?s 
//standard warranty for its products.  You agree that you are solely responsible 
//for testing the software and determining its suitability.  Microchip has no 
//obligation to modify, test, certify, or support the software.
//
// THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER EXPRESS,
//IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF
//NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE, OR ITS 
//INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE 
//IN ANY APPLICATION.
 
//IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL 
//OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE 
//SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR 
//THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S 
//TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED 
//THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

//MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE TERMS. 

////////////////////////////////////////////////////////////////////////////////

#include "main.h"

_FOSCSEL(FNOSC_FRC)
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON)
_FWDT(WDTEN_OFF)
_FICD(ICS_PGD2 & JTAGEN_OFF)
_FDEVOPT(PWMLOCK_OFF)

//// Interrupt Priority Level For Alternate Working Registers
_FALTREG(CTXT1_IPL7 & CTXT2_IPL6)
// Boost = IPL6
// Buck  = IPL7  
        
        
#if((BUCK == DISABLED)&&(BOOST == ENABLED))
uint8_t anaMuxSetting = 1;
#else
uint8_t anaMuxSetting = 0;
#endif


int main(void)
{

    dpskFaultFlags.systemFaults = 0;    // Clear all flags

    // I/O pin RB13 controls analog MUX for temp sense selection:
    // 0 = BUCK temp sensor
    // 1 = BOOST temp sensor
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB12 = 0;        // Set as output
    LATBbits.LATB13   = anaMuxSetting;

    InitClock();            // Initialize Primary and Auxiliary oscillators

    InitI2C();              // Initialize communication to MCP23008 for load control
                            // Also sets initial load for the converters

    InitTimer();            // Initialize timer for load dynamics
                            // and timer for soft start

    InitCMP();              // Initialize comparators to be used for cycle-by-cycle protection
    InitADC();              // Configures ADC for reading input voltage, output voltages,
                            // load currents, and temperature

    InitADCMP();            // Initialize digital Comparators for Vin/Temp faults

    // This function also displays initial startup messages
    LCD_Init();             // Initialize LCD

    // Setup PWM resolution and Period
    PTPER = PERIODVALUE;    // Buck/Boost converter switching Frequency (350 kHz)
    PTCON2bits.PCLKDIV = (PWMRESOLUTION_REG-1); // PWM Resolution

    InitPWM3();             // Used for synchronizing triggers to ADC

    IO_DRV            = 0;  // Initialize to LOW state

    #if (BUCK == ENABLED)
        InitBuckPWM();                // PWM Setup for Buck converter

        #if(OPENLOOP == DISABLED)
            InitBuckComp();         // Initialize Buck compensator
        #endif

        dpskFlags.buckSSActive = ENABLED;
        
    #else
        // Need to clear IOCON to ensure PWML is not 100% DC as PENL enabled at
        // device reset
        IOCON1 = 0x0000;

    #endif

    #if (BOOST == ENABLED)
        InitBoostPWM();               // PWM Setup for Boost converter

        #if(OPENLOOP == DISABLED)
            InitBoostComp();        // Initialize Boost compensator
        #endif

        dpskFlags.boostSSActive = ENABLED;
        
    #else
        // Need to clear IOCON to ensure PWML is not 100% DC as PENL enabled at
        // device reset
        IOCON2 = 0x0000;

    #endif

    PTCONbits.PTEN = 1;     // Enable the PWM

    __delay_us(3);          // Wait one PWM cycle then give ownership

    #if (BUCK == ENABLED)
        // To eliminate PWM glitch at start-up (Errata), enable PWM module
        // and then give PWM ownership of the pin
        IOCON1bits.PENH  = 1;       // PWM1H is controlled by PWM module
        IOCON1bits.PENL  = 1;       // PWM1L is controlled by PWM module

        IEC6bits.ADCAN1IE = 1;	    // Enable ADC AN1 interrupt
        ADIELbits.IE1     = 1;

    #endif

    #if(BOOST == ENABLED)
        IOCON2bits.PENL    = 1;     // PWM2L is controlled by PWM module
 
       //  SW Trigger AN3 for initial Boost output voltage Measurement
       //  Since boost voltage does not start from '0' volts
        ADCON3Lbits.SWCTRG = 1;
        while(ADSTATLbits.AN3RDY != 1);
        boostControlReference = ADCBUF3;

        ADTRIG0Hbits.TRGSRC3  = 6;       // Change trigger back to PWM2
        IEC7bits.ADCAN3IE     = 1;       // Enable AN3 interrupt
        ADIELbits.IE3         = 1;

    #endif

    // Initial load settings to be displayed on LCD
    #if(BOOSTLOAD1 != EXTERNALLOAD)
    LCD_BoostLoad = BOOSTLOAD1LCD;
    #endif

    #if(BUCKLOAD1 != EXTERNALLOAD)
    LCD_BuckLoad = BUCKLOAD1LCD;
    #endif

    // Enable Timer2 for SoftStart
    T2CONbits.TON = 1;              // Enable Timer

    while(1)
    {
        if(PushButtonSW1()==1)
        {
            LCD_DPSK_SwitchDisplay();
        }
        LCD_DPSK_Write();        
    }                       // End of While loop

    return 0;
}





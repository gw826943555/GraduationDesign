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

#include "isr.h"

//Define variables  
uint16_t buckVoltage  = 0,boostVoltage = 0, inputVoltage = 0;
uint16_t buckCurrent  = 0,boostCurrent = 0;
uint16_t tempSense    = 0;
int16_t buckControlReference = 0, boostControlReference = 0;
volatile uint8_t messageComplete = 0;


void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{
    #if(BUCKDYNAMICLOAD == ENABLED)

    if(dpskFlags.buckSSActive == DISABLED)
    {
        I2CLoadWrite &= 0x38;           // Clear lower 3-bits for Buck write

        //Code to switch on-board load for dynamic load testing
        if(dpskFlags.buckDynLoad == 0)
        {
            I2CLoadWrite |= I2CBUCKLOAD2WRITE;

            LCD_BuckLoad = BUCKLOAD2LCD;
            dpskFlags.buckDynLoad = 1;
        }    
        else
        {
            I2CLoadWrite |= I2CBUCKLOAD1WRITE;

            LCD_BuckLoad = BUCKLOAD1LCD;
            dpskFlags.buckDynLoad = 0;
        }
    }
    #else
    I2CLoadWrite |= I2CBUCKLOAD1WRITE;    //Restores load setting after fault

    #endif

    #if(BOOSTDYNAMICLOAD == ENABLED)

    if(dpskFlags.boostSSActive == DISABLED)
    {
        I2CLoadWrite &= 0x07;            // Clear bits 4-6 for Boost write

        //Code to switch on-board load for dynamic load testing
        if(dpskFlags.boostDynLoad == 0)
        {
            I2CLoadWrite |= I2CBOOSTLOAD2WRITE;

            LCD_BoostLoad = BOOSTLOAD2LCD;
            dpskFlags.boostDynLoad = 1;
        }
        else
        {
            I2CLoadWrite |= I2CBOOSTLOAD1WRITE;

            LCD_BoostLoad = BOOSTLOAD1LCD;
            dpskFlags.boostDynLoad = 0;
        }
    }
    #else
    I2CLoadWrite |= I2CBOOSTLOAD1WRITE;    //Restores load setting after fault

    #endif
    
    I2C1CON1bits.SEN = 1;      // Initiate start sequence

    IFS0bits.T1IF = 0;
}


void __attribute__((__interrupt__, no_auto_psv)) _MI2C1Interrupt(void)
{
    static int8_t cmd = 0;

    Nop();

    switch(cmd)
    {
        case MASTERWRITESLAVEADDR:
        //Write slave address
        I2C1TRN = (SLAVEADDRESS << 1) | 0;
        break;

        case MASTERWRITESREGADDR:
       if(I2C1STATbits.ACKSTAT == 0)
        {
            I2C1TRN =  I2CRegAddr;
        }

        break;

        case MASTERWRITESREGDATA:
            if(I2C1STATbits.ACKSTAT == 0)
            {
            I2C1TRN = I2CLoadWrite;
            }
        break;
    
        case STOPCONDITION:
             if(I2C1STATbits.ACKSTAT == 0)
            {
                I2C1CON1bits.PEN = 1;
             }
        break;

        case RESET:
        messageComplete = 1;
        cmd = -1;
        break;
    }

    cmd++;

    IFS1bits.MI2C1IF = 0;
}

#if(__XC16_VERSION__ == 1024)           // for XC16 v1.24 compiler
void __attribute__((__interrupt__, no_auto_psv)) _ADCMP1Interrupt(void)
#else                                   
void __attribute__((__interrupt__, no_auto_psv)) _ADCMP0Interrupt(void)
#endif
{
    if(ADCMP0HI == WARNINGTEMPADC)
    {
        // Change digital cmp settings
        ADCMP0CONbits.LOLO = 1;
        ADCMP0LO = TEMPREINITADC;
        ADCMP0HI = TEMPMAXADC;

        if(dpskFaultFlags.overTemp == 0)
        {
            // set bit, indicates hi temp warning fault
            dpskFaultFlags.tempWarning = 1;
        }
    }
    else if (ADCBUF7 >= TEMPMAXADC)
    {
       // Change digital cmp settings
        ADCMP0CONbits.HIHI         = 0;

        dpskFaultFlags.overTemp    = 1;
        dpskFaultFlags.tempWarning = 0;

        I2CLoadWrite     = 0x09;   // If over-temp condition, change loads to 0.5W (minimum load)

        I2C1CON1bits.SEN = 1;      // Initiate start sequence

        #if((BUCKDYNAMICLOAD == ENABLED) || (BOOSTDYNAMICLOAD == ENABLED))
        IEC0bits.T1IE = 0;
        #endif
    }
    else if (ADCBUF7 <= TEMPREINITADC)
    {
        // Change digital cmp settings
        ADCMP0CONbits.LOLO = 0;
        ADCMP0CONbits.HIHI = 1;
        ADCMP0HI = WARNINGTEMPADC;

        if(dpskFaultFlags.tempWarning == 1)
        {
            // Clear bit to disable 'HI TEMP WARNING' on display
            dpskFaultFlags.tempWarning = 0;
        }
        else if (dpskFaultFlags.overTemp == 1)
        {
            // Clear bit to disable 'OVER TEMP FAULT' on display
            dpskFaultFlags.overTemp = 0;

           // Re-enable loads
           I2CLoadWrite = (I2CBUCKLOAD1WRITE | I2CBOOSTLOAD1WRITE);
           I2C1CON1bits.SEN = 1;            // Initiate start sequence

           #if((BUCKDYNAMICLOAD == ENABLED) || (BOOSTDYNAMICLOAD == ENABLED))
           IEC0bits.T1IE = 1;
           #endif
        }
    }

    IFS11bits.ADCMP0IF = 0;
}


#if(__XC16_VERSION__ == 1024)                 // for XC16 v1.24 compiler
void __attribute__((__interrupt__, no_auto_psv)) _ADCMP2Interrupt(void)
#else
void __attribute__((__interrupt__, no_auto_psv)) _ADCMP1Interrupt(void)
#endif
{
    if(ADCMP1HI == INPUTOVERVOLTAGEADC)
    {
        // Change digital comparator settings
        ADCMP1CONbits.HIHI = 0;
        ADCMP1CONbits.LOLO = 0;

        ADCMP1HI = INPUTVOLTMAXHYST;
        ADCMP1LO = INPUTVOLTMINHYST;

        if(inputVoltage >= INPUTOVERVOLTAGEADC)
        {
            ADCMP1CONbits.HILO = 1;      // Interrupt when ADCBUF is less than DCMP HI
        }
        else
        {
          ADCMP1CONbits.LOHI = 1;        // Interrupt when ADCBUF is >= than DCMP LO
        }

        IOCON1bits.OVRENH = 1;           // Override the PWM1H/L - Buck FETs to inactive state
        IOCON1bits.OVRENL = 1;
        IOCON2bits.OVRENL = 1;           // Override the PWMHL - Boost FET to inactive state

        IEC6bits.ADCAN1IE = 0;           // Disable interrupts
        IEC7bits.ADCAN3IE = 0;

        CMP1DAC = 0;
        CMP2DAC = 0;

        dpskFaultFlags.inputVoltage = 1;

        I2CLoadWrite = NOLOAD;     // If fault condition exists, disable ALL loads
        I2CLoadWrite = 0x09;
        I2C1CON1bits.SEN = 1;      // Initiate start sequence
    }
    else
    {
        // Change digital comparator settings
        ADCMP1CONbits.HILO = 0;
        ADCMP1CONbits.LOHI = 0;

        ADCMP1HI = INPUTOVERVOLTAGEADC;
        ADCMP1LO = INPUTUNDERVOLTAGEADC;

        ADCMP1CONbits.HIHI = 1;
        ADCMP1CONbits.LOLO = 1;

        dpskFaultFlags.inputVoltage = 0;

        #if(BUCK == ENABLED)

            #if(OPENLOOP == DISABLED)

                MACRO_CLR_BUCKHISTORY()
                buckControlReference = 0;

                IEC6bits.ADCAN1IE    = 1;

                IOCON1bits.OVRENH    = 0;       // Remove Override
                IOCON1bits.OVRENL    = 0;
            #endif

            dpskFlags.buckSSActive = ENABLED;   // Reinitiate softstart

        #endif

        #if(BOOST == ENABLED)

            #if(OPENLOOP == DISABLED)

                MACRO_CLR_BOOSTHISTORY()  // Clear error history

                // SW Trigger AN3 for initial Boost output voltage Measurement
                ADTRIG0Hbits.TRGSRC3 = 1;
                ADCON3Lbits.SWCTRG   = 1;
                while(ADSTATLbits.AN3RDY != 1);
                boostControlReference = ADCBUF3;
                ADTRIG0Hbits.TRGSRC3 = 6;       // Change trigger back to PWM2
                IEC7bits.ADCAN3IE    = 1;
                IOCON2bits.OVRENL    = 0;       // Remove Override

            #endif

            dpskFlags.boostSSActive = ENABLED;   // Reinitiate softstart

         #endif

       // Re-enable loads
       I2CLoadWrite = (I2CBUCKLOAD1WRITE | I2CBOOSTLOAD1WRITE);
       I2C1CON1bits.SEN = 1;            // Initiate start sequence

       // Fire up soft start timer
       TMR2            = 0;
       T2CONbits.TON   = 1;

    }


    IFS11bits.ADCMP1IF = 0;


}





void __attribute__((__interrupt__, no_auto_psv)) _ADCAN7Interrupt(void)
{
    refreshLCD++;

    // Read Vin and Temperature for LCD display, fault management performed
    // in digital comparator ISRs
 
    inputVoltage = ADCBUF4;
    tempSense    = ADCBUF7;

    IFS7bits.ADCAN7IF = 0;
}

void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt(void)
{
    #if(BUCK == ENABLED)
    static uint8_t buckErrorCount = 0;

    #if(OPENLOOP == DISABLED)  // If in closed-loop, perform soft-start routine
    {
       if(dpskFlags.buckSSActive == ENABLED)
       {
          if(buckControlReference < BUCKVOLTAGEREFERENCEADC)
          {
             buckControlReference += BUCKINCREMENT;

             if((buckErrorControlHistory[0]) > ( BUCK_FB_LOOP_CHECK)) // Used to check feedback loop (is feedback loop open?)
             {                                                        // and ensure that output follows Vreference
                ++buckErrorCount;

                if(buckErrorCount > 2)
                {
                   // Disable Buck converter PWMs
                   IOCON1bits.OVRENH = 1;                   // Over ride the PWM1H to inactive state
                   IOCON1bits.OVRENL = 1;                   // Over ride the PWM1L to inactive state
                   I2CLoadWrite = I2CLoadWrite & ~0x07;     // Configure Buck loads to be off
                   I2C1CONLbits.SEN = 1;                    // Initiate start sequence

                   dpskFaultFlags.buckSoftStart = ENABLED;  // Display: Bck Output Fault
                   IFS6bits.ADCAN1IF = 0;
                 }
              }
           }
           else
           {
              buckErrorCount         = 0;
              buckControlReference   = BUCKVOLTAGEREFERENCEADC;
              dpskFlags.buckSSActive = DISABLED;    // Soft-start is complete
           }
        }
    }

    #else

    if(PDC1 < BUCKOPENLOOPDC)
    {
      PDC1 += BUCKINCREMENT;
    }
    else
    {
      PDC1 = BUCKOPENLOOPDC;
      dpskFlags.buckSSActive = DISABLED;
    }
    #endif

#endif

    #if(BOOST == ENABLED)
    static uint8_t boostErrorCount = 0;

    #if(OPENLOOP == DISABLED)  // If in closed-loop, perform soft-start routine
    {
      if(dpskFlags.boostSSActive == ENABLED)
      {

        if(boostControlReference < BOOSTVOLTAGEREFERENCEADC)
        {
           boostControlReference += BOOSTINCREMENT;

           if ((boostErrorControlHistory[0]) > (BOOST_FB_LOOP_CHECK))  // Used to check feedback loop (is feedback loop open?)
           {                                                          // and ensure that output follows Vreference
             ++boostErrorCount;

             if(boostErrorCount > 2)
             {
               //Disable Boost converter PWMs
               IOCON2bits.OVRENL = 1;                       // Override PWM2H to inactive state

               I2CLoadWrite = I2CLoadWrite & 0x07;          // Configure boost loads off
               I2C1CONLbits.SEN = 1;                        // Initiate start sequence

               dpskFaultFlags.boostSoftStart = ENABLED;     // Display: Bst Output Fault
               IFS7bits.ADCAN3IF = 0;
             }
           }
         }
         else
         {
            boostErrorCount         = 0;
            boostControlReference   = BOOSTVOLTAGEREFERENCEADC;
            dpskFlags.boostSSActive = DISABLED;    // Soft-start is complete
         }
      }
    }

    #else

    if(PDC2 < BOOSTOPENLOOPDC)
    {
      PDC2 += BOOSTINCREMENT;
    }
    else
    {
      PDC2 = BOOSTOPENLOOPDC;
      dpskFlags.boostSSActive = DISABLED;
    }
    #endif

#endif

   // Disable Timer once both softstart flags are disabled
   if((dpskFlags.buckSSActive == DISABLED) && (dpskFlags.boostSSActive == DISABLED))
   {
       T2CONbits.TON = 0;
   }

    IFS0bits.T2IF = 0;
}






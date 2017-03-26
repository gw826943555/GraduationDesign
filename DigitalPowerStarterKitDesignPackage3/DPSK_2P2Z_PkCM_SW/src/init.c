
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


#include "init.h"

//initialize variables used in I2C configuration
uint8_t I2CLoadWrite = 0, I2CRegAddr = 0;

void InitClock(void)
{
   // Configure Oscillator to operate the device at 68 MHz
   // Fosc = Fin*M/(N1*N2), Fcy = Fosc/2
   // Fosc = 7.37*(76)/(2*2)= ~140Mhz for Fosc, Fcy = 70 MHz

   // Configure PLL prescaler, PLL postscaler, PLL divisor
   PLLFBD             = 74;   // M = PLLFBD + 2
   CLKDIVbits.PLLPOST =  0;   // N1 = 2
   CLKDIVbits.PLLPRE  =  0;   // N2 = 2

   __builtin_write_OSCCONH(0x01);     // New Oscillator selection FRC w/ PLL
   __builtin_write_OSCCONL(0x01);     // Enable Switch

   while(OSCCONbits.COSC != 0b001);    // Wait for Osc. to switch to FRC w/ PLL
   while(OSCCONbits.LOCK != 1);        // Wait for PLL to Lock

   // Setup the ADC and PWM clock for 120MHz
   // ((FRC * 16) / APSTSCLR ) = (7.37MHz * 16) / 1 = 117.9MHz

   ACLKCONbits.FRCSEL   = 1;	  // FRC provides input for Auxiliary PLL (x16)
   ACLKCONbits.SELACLK  = 1;	  // Aux Osc. provides clock source for PWM & ADC
   ACLKCONbits.APSTSCLR = 7;	  // Divide Auxiliary clock by 1
   ACLKCONbits.ENAPLL   = 1;	  // Enable Auxiliary PLL

   while(ACLKCONbits.APLLCK != 1);  // Wait for Auxiliary PLL to Lock
   __delay_us(50);                  // Errata#1 (reference:DS80000656A)
}


void InitI2C(void)
{
    I2C1CON1bits.I2CEN = 1;      // Enable I2C Module
  
    //Configure I2C as MASTER to communicate with Load IC
    I2C1CON1bits.A10M   = 0;     // 7-bit slave address/data
    I2C1CON1bits.DISSLW = 1;     // Slew rate control disabled ??????

    I2C1BRG = I2CBAUDRATE;       // 100kHz

    IFS1bits.MI2C1IF = 0;        //?????????
    IEC1bits.MI2C1IE = 1;        // Enable Master I2C interrupt

    IPC4bits.MI2C1IP = 5;       //?????????? 0-7???????????
    
    // Code Configures MCP23008 and sets up the initial load
    I2CRegAddr   = IOCON_REGADDR;
    I2CLoadWrite = 0x20;         // Disabled sequential operation
    
    I2C1CON1bits.SEN = 1;        // Initiate start sequence

    while(messageComplete == 0);
    messageComplete = 0;

    I2CRegAddr = IODIR_REGADDR;
    I2CLoadWrite = 0x00;         // Configures all I/O pins as output

    I2C1CON1bits.SEN = 1;        // Initiate start sequence

    while(messageComplete == 0);
    messageComplete = 0;

    I2CRegAddr = GPIO_REGADDR;
    I2CLoadWrite = (I2CBUCKLOAD1WRITE | I2CBOOSTLOAD1WRITE);

    I2C1CON1bits.SEN = 1;        // Initiate start sequence

    while(messageComplete == 0);
    messageComplete = 0;

}

void InitTimer(void)
{
    //Load Dynamics applied after the softstart

    #if((BUCKDYNAMICLOAD == ENABLED) || (BOOSTDYNAMICLOAD == ENABLED))
    PR1 = TMRPERIOD;
    T1CONbits.TCKPS = TMRSCALER;    //?????????8
    T1CONbits.TCS = 0;              // Clock source is internal Fcy???? 70Mhz

    IFS0bits.T1IF = 0;              //
    IPC0bits.T1IP = 4;              //?????4
    IEC0bits.T1IE = 1;              //?????1??
    T1CONbits.TON = 1;              //?????1
    #endif

    // Configure Timer 2 for soft start
    PR2 = TMR2PERIOD;
    T2CONbits.TCKPS = TMR2SCALER;   //?????????1
    T2CONbits.TCS = 0;              // Clock source is internal Fcy

    IFS0bits.T2IF = 0;
    IPC1bits.T2IP = 4;
    IEC0bits.T2IE = 1;   
}

void InitBuckPWM(void)
{
    IOCON1bits.PENH = 0;            // GPIO controls I/O port
    IOCON1bits.PENL = 0;            //PWMxH/PWMxL Output Pin Ownership bit

    IOCON1bits.PMOD = 0;            // Complementary Mode
                                    //PWMx I/O Pin Mode bits
    
    IOCON1bits.POLH = 0;            // Drive signals are active-high
    IOCON1bits.POLL = 0;            // Drive signals are active-high
                                    //PWMxH/PWMxL Output Pin Polarity bit

    IOCON1bits.OVRENH = 0;          // Override disabled
    IOCON1bits.OVRENL = 0;          // Override Enable for PWMxH Pin bit
                                    // PWMx generator provides data for the PWMxH/PWMxL pin
    IOCON1bits.OVRDAT = 0b00;       // Override data PWMH and PWML
                                    // Data for PWMxH, PWMxL Pins if Override is Enabled bits
    IOCON1bits.FLTDAT = 0b01;       // If fault occurs:
                                    // PWMH = 0 & PWML = 1
                                    // State for PWMxH and PWMxL Pins if FLTMOD<1:0> are Enabled bits

    PWMCON1bits.DTC   = 0;          // Positive Deadtime enabled
                                    // Dead-Time Control bits
    DTR1    = 80;                   // PWM1 DEAD-TIME REGISTER
    ALTDTR1 = 110;                  // PWM1 ALTERNATE DEAD-TIME REGISTER 
				  
    PWMCON1bits.IUE = 0;            // Disable Immediate duty cycle updates
                                    // Immediate Update Enable bit
    PWMCON1bits.ITB = 0;            // Select Primary Timebase mode 
                                    // Independent Time Base Mode bit
                                    // PTPER register provides timing for this PWM1 generator

    FCLCON1bits.FLTSRC = 0b01101;   // Fault Control Signal assigned to CMP1
                                    // Fault Control Signal Source Select for PWM1 Generator bits
    FCLCON1bits.FLTPOL = 0;         // Fault Signal is active-high
                                    //  Fault Polarity for PWM1 Generator bit
    FCLCON1bits.FLTMOD = 1;         // Cycle-by-Cycle current limiting
                                    // Fault Mode for PWM1 Generator bits

    // In order to block the sensed current spike at the
    // turn on edge of the HS FET, use Leading Edge blanking(LEB).
    LEBCON1bits.PHR      = 1;       // Enable LEB bit for HS MOSFET rising edge
                                    // PWMxH Rising Edge Trigger Enable bit
    LEBCON1bits.FLTLEBEN = 1;       // Fault Input LEB Enabled
                                    // Fault Input Leading-Edge Blanking Enable bit
    LEBDLY1bits.LEB      = 20;      // 8.32n Steps x 20 = 160ns
                                    // Leading-Edge Blanking Delay for Current-Limit and Fault Inputs bits
    TRGCON1bits.TRGDIV  = 1;        // Trigger interrupt generated every 2 PWM cycles
                                    // Trigger # Output Divider bits
    TRGCON1bits.TRGSTRT = 0;        // Trigger generated after waiting 0 PWM cycles
                                    // Trigger Postscaler Start Enable Select bits
    // Initialize PDC1 depending on configuration

    #if(OPENLOOP == ENABLED)
    PDC1 = BUCKOPENLOOPDC;
    #else
    PDC1 = BUCKMAXDUTYCYCLE;        // PWM1 Generator Duty Cycle Value bits
    #endif

    TRIG1 = 30;                     // Set Initial Trigger location

}

void InitBoostPWM(void)
{
    IOCON2bits.PENH = 0;                // PWM2H is controlled by I/O module
    IOCON2bits.PENL = 0;                // PWM2L is controlled by I/O module

    IOCON2bits.PMOD = 1;                // Redundant Mode w/ PWMH not used
    IOCON2bits.POLL = 0;                // Drive signal- active-high

    IOCON2bits.OVRENL = 0;		// Override disabled
    IOCON2bits.OVRDAT = 0b00;           // Override data:
                                        // PWMH = 0 & PWML = 0
    PWMCON2bits.DTC = 2;                // Deadtime disabled

    PWMCON2bits.IUE = 0;                // Disable Immediate duty cycle updates
    PWMCON2bits.ITB = 0;                // Select Primary Timebase mode
    
    FCLCON2bits.FLTSRC = 0b01110;       // Fault Control Signal assigned to CMP2
    FCLCON2bits.FLTPOL = 0;             // Fault Signal is active-high
    FCLCON2bits.FLTMOD = 1;             // Cycle-by-Cycle Fault Mode

    //Enable LEB to blank (mask) any turn-on spike
    LEBCON2bits.PLR      =  1;          // Enable LEB bit for PWML
    LEBCON2bits.FLTLEBEN =  1;          // Fault Input LEB Enabled
    LEBDLY2bits.LEB      = 20;          // 8.32n Steps x 20 = 160ns

    TRGCON2bits.TRGDIV  = 1;            // Trigger interrupt generated every 2 PWM cycles

    TRGCON2bits.TRGSTRT = 1;            // Trigger generated after waiting 1 PWM cycles

    PHASE2 = PTPER>>1;			// Introduce phase shift from Buck converter to reduce Vin distortion
                                        // 180 Deg phase-shift from Buck converter

    // Initialize PDC1 depending on configuration

    #if(OPENLOOP == ENABLED)
    PDC2 = BOOSTOPENLOOPDC;
    #else
    PDC2  = BOOSTMAXDUTYCYCLE;
    #endif

    TRIG2 = 30;                        // Trigger generated at beginning of PWM period
}

void InitPWM3(void)
{
    // PWM3 only used as clock source for triggering AN4/AN7

    #if(BOOST == ENABLED)
    PHASE3 = PTPER >> 1;
    TRGCON3bits.TRGSTRT = 2;    // Trigger generated after waiting 3 PWM cycles

    #else
    TRGCON3bits.TRGSTRT = 0;    // Trigger generated after waiting 0 PWM cycles
                                //Trigger Postscaler Start Enable Select bits

    #endif

    TRIG3 = 500;
    TRGCON3bits.TRGDIV = 5;    // Trigger interrupt generated once every 6 PWM cycle
                               // Trigger # Output Divider bits
    FCLCON3bits.FLTMOD = 3;    //Fault Mode for PWMx Generator bits
                               //Fault input is disabled
    IOCON3bits.PMOD    = 1;    //PWMx I/O pin pair is in the Redundant Output mode
                               //PWMx I/O Pin Mode bits

    IOCON3bits.PENL = 0;        // Give Ownership of PWM3 to device pin
    IOCON3bits.PENH = 0;        //GPIO module controls the PWMxH pin
                                //PWMxH/PWMxL Output Pin Ownership bit
}


void InitCMP(void)   // Buck & Boost overcurrent protection
{
    //PDF Page 267
    #if(BUCK == ENABLED)
    CMP1CONbits.INSEL  = 0;          // Input: CMP1A CS_Buck
    CMP1CONbits.HYSSEL = 1;          // 5mV of Hysteresis

    CMP1CONbits.RANGE = 1;           // AVdd is the max DACx output voltage
    
    CMP1DAC = BUCKMAXCURRENTDAC;     // Buck DAC voltage for overcurrent
                                     // 2964 counts (2.39V)
    CMP1CONbits.CMPON = 1;
    #endif

    #if(BOOST == ENABLED)
    CMP2CONbits.INSEL  = 0;          // Input: CMP2A
    CMP2CONbits.HYSSEL = 1;          // 5mV of Hysteresis

    CMP2CONbits.RANGE = 1;           // AVdd is the max DACx output voltage

    CMP2DAC = BOOSTMAXCURRENTDAC;    // Boost DAC voltage for overcurrent
                                     // 2904 counts (2.34V)
    CMP2CONbits.CMPON = 1;
    
    #endif
}

void InitADC(void)
{
    // Setup ADC Clock Input Max speed of 70 MHz --> Fosc = 140 MHz
    ADCON3Hbits.CLKSEL  = 1;    // 0-Fsys, 1-Fosc, 2-FRC, 3-APLL
    ADCON3Hbits.CLKDIV  = 0;    // Global Clock divider (1:1)
    ADCORE0Hbits.ADCS   = 0;    // Core 0 clock divider (1:2)
    ADCORE1Hbits.ADCS   = 0;    // Core 1 clock divider (1:2)
    ADCORE2Hbits.ADCS   = 0;    // Core 2 clock divider (1:2)
    ADCORE3Hbits.ADCS   = 0;    // Core 3 clock divider (1:2)
    ADCON2Lbits.SHRADCS = 0;    // 1/2 clock divider

    ADCON1Hbits.FORM    = 0;    // Integer format
    ADCON3Lbits.REFSEL  = 0;    // AVdd as voltage reference

     // ADC Cores in 12-bit resolution mode
    ADCON1Hbits.SHRRES  = 3;    // Shared ADC Core in 12-bit resolution mode
    ADCORE0Hbits.RES    = 3;    // Core 0 ADC Core in 12-bit resolution mode
    ADCORE1Hbits.RES    = 3;    // Core 1 ADC Core in 12-bit resolution mode
    ADCORE2Hbits.RES    = 3;    // Core 2 ADC Core in 12-bit resolution mode
    ADCORE3Hbits.RES    = 3;    // Core 3 ADC Core in 12-bit resolution mode
    ADCON2Hbits.SHRSAMC = 2;    // Shared ADC Core sample time 4Tad

    // Configure ANx for unsigned format and single ended (0,0)
    ADMOD0L = 0x0000;

    InitCalibrateADC();

    
#if(BUCK == ENABLED)
    ADTRIG0Lbits.TRGSRC0 = 5;    // ADC AN0 triggered by PWM1
    ADTRIG0Lbits.TRGSRC1 = 5;    // ADC AN1 triggered by PWM1

    IFS6bits.ADCAN1IF  = 0;      // Clear ADC interrupt flag
    IPC27bits.ADCAN1IP = 7;      // Set Buck ADC interrupt priority to 7

#endif

#if (BOOST == ENABLED)
    ADTRIG0Hbits.TRGSRC2 = 6;    // ADC AN2/AN3 triggered by PWM2
    ADTRIG0Hbits.TRGSRC3 = 1;    // Initial trigger by SW for softstart

    IFS7bits.ADCAN3IF    = 0;    // Clear ADC interrupt flag
    IPC28bits.ADCAN3IP   = 6;    // Set Boost ADC interrupt priority

#endif
    ADTRIG1Lbits.TRGSRC4 = 7;    // ADC AN4/AN7 triggered by PWM3
    ADTRIG1Hbits.TRGSRC7 = 7;    // for synchronizing trigger event

    IFS7bits.ADCAN7IF    = 0;    // Clear ADC interrupt flag
    IPC29bits.ADCAN7IP   = 5;	 // Set ADC interrupt priority
    IEC7bits.ADCAN7IE    = 1;	 // Enable the ADC AN7 interrupt
    ADIELbits.IE7        = 1;    // Enable ADC Common Interrupt
}

void InitCalibrateADC(void)
{
    // Power Up delay: 2048 Core Clock Source Periods (TCORESRC) for all ADC cores
    // (~14.6 us)
    _WARMTIME = 11;

    // Turn on ADC module
    ADCON1Lbits.ADON  = 1;

    // Turn on analog power for dedicated core 0
    ADCON5Lbits.C0PWR = 1;
    while(ADCON5Lbits.C0RDY == 0);
    ADCON3Hbits.C0EN  = 1;   // Enable ADC core 0

    // Turn on analog power for dedicated core 1
    ADCON5Lbits.C1PWR = 1;
    while(ADCON5Lbits.C1RDY == 0);
    ADCON3Hbits.C1EN  = 1;   // Enable ADC core 1

    // Turn on analog power for dedicated core 2
    ADCON5Lbits.C2PWR = 1;
    while(ADCON5Lbits.C2RDY == 0);
    ADCON3Hbits.C2EN  = 1;   // Enable ADC core 2

    // Turn on analog power for dedicated core 3
    ADCON5Lbits.C3PWR = 1;
    while(ADCON5Lbits.C3RDY == 0);
    ADCON3Hbits.C3EN  = 1;   // Enable ADC core 3

    // Turn on analog power for shared core
    ADCON5Lbits.SHRPWR = 1;
    while(ADCON5Lbits.SHRRDY == 0);
    ADCON3Hbits.SHREN  = 1;  // Enable shared ADC core

    // Enable calibration for the dedicated core 0
    ADCAL0Lbits.CAL0EN   = 1;
    ADCAL0Lbits.CAL0DIFF = 0;         // Single-ended input calibration
    ADCAL0Lbits.CAL0RUN  = 1;         // Start Cal
    while(ADCAL0Lbits.CAL0RDY == 0);
    ADCAL0Lbits.CAL0EN   = 0;         // Cal complete

    // Enable calibration for the dedicated core 1
    ADCAL0Lbits.CAL1EN   = 1;
    ADCAL0Lbits.CAL1DIFF = 0;         // Single-ended input calibration
    ADCAL0Lbits.CAL1RUN  = 1;         // Start Cal
    while(ADCAL0Lbits.CAL1RDY == 0);
    ADCAL0Lbits.CAL1EN   = 0;         // Cal complete

    // Enable calibration for the dedicated core 2
    ADCAL0Hbits.CAL2EN   = 1;
    ADCAL0Hbits.CAL2DIFF = 0;         // Single-ended input calibration
    ADCAL0Hbits.CAL2RUN  = 1;         // Start Cal
    while(ADCAL0Hbits.CAL2RDY == 0);
    ADCAL0Hbits.CAL2EN   = 0;         // Cal complete

    // Enable calibration for the dedicated core 3
    ADCAL0Hbits.CAL3EN   = 1;
    ADCAL0Hbits.CAL3DIFF = 0;         // Single-ended input calibration
    ADCAL0Hbits.CAL3RUN  = 1;         // Start Cal
    while(ADCAL0Hbits.CAL3RDY == 0);
    ADCAL0Hbits.CAL3EN   = 0;         // Cal complete

    // Enable calibration for the shared core
    ADCAL1Hbits.CSHREN   = 1;
    ADCAL1Hbits.CSHRDIFF = 0;        // Single-ended input calibration
    ADCAL1Hbits.CSHRRUN  = 1;        // Start calibration cycle
    while(ADCAL1Hbits.CSHRRDY == 0); // while calibration is still in progress

    ADCAL1Hbits.CSHREN   = 0;        // Calibration is complete
}

void InitADCMP(void)
{
    // Digital Comparator 0 for temperature
    ADCMP0CONbits.HIHI   = 1;       // Interrupt when ADCBUF is greater than DCMP HI
    ADCMP0ENLbits.CMPEN7 = 1;       // ADCBUF7 processed by digital comparator

    ADCMP0HI = WARNINGTEMPADC;

    ADCMP0CONbits.CMPEN = 1;        // Enable digital comparator

    ADCMP0CONbits.IE    = 1;        // Enable interrupt for CMP
   

    IPC44bits.ADCMP0IP = 4;         // Set ADC Digital Comparator 0 Interrupt Priority Level to 4
    IFS11bits.ADCMP0IF = 0;         // Clear ADC Digital Comparator 0 Flag
    IEC11bits.ADCMP0IE = 1;         // Enable ADC Digital Comparator 0 Interrupt

   

    // Digital Comparator 1 for input voltage
    ADCMP1CONbits.HIHI   = 1;       // Interrupt when ADCBUF is greater than DCMP HI
    ADCMP1CONbits.LOLO   = 1;       // Interrupt when ADCBUF is less than DCMP LO
    ADCMP1ENLbits.CMPEN4 = 1;       // ADCBUF4 processed by digital comparator

    ADCMP1HI = INPUTOVERVOLTAGEADC;
    ADCMP1LO = INPUTUNDERVOLTAGEADC;

    ADCMP1CONbits.CMPEN = 1;        // Enable digital comparator

    ADCMP1CONbits.IE    = 1;        // Enable interrupt for CMP

    IPC44bits.ADCMP1IP = 4;         // Set ADC Digital Comparator 1 Interrupt Priority Level to 4
    IFS11bits.ADCMP1IF = 0;         // Clear ADC Digital Comparator 1 Flag
    IEC11bits.ADCMP1IE = 1;         // Enable ADC Digital Comparator 1 Interrupt
    
}

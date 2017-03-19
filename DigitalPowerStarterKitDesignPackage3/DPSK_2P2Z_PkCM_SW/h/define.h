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
#ifndef DEFINE_H
#define DEFINE_H

#define ENABLED  1
#define DISABLED 0

#define FCY 70000000UL              // Define intruction clock rate for delay routine
                                    // this definition constant is needed for delay() function calls

#define LCD_REFRESHCOUNT 45000      // Refresh LCD rate = value * ~17us = 750ms
#define DEBOUNCE_DELAY 	    20	    // Push button debounce delay (ms)

#define IO_DRV  LATBbits.LATB12

//PWM&ADC Configuration
#define CONVSWITCHFREQ 350000       // PWMx Switching frequency in Hz

// PWM Resolution (~1.06 ns)
#define PWMRESOLUTION_REG 1         // 1 ~= 1ns, 2 ~= 2ns, 3~=4ns
                                    // 4 ~= 8ns, Used in PTCON2 register

#define PWMDIVIDERSETTING 1         // 1, 2, 4, 8, 16 (aligns w/ above #define)
#define F_ACLK  (unsigned long)(7372800 * 128)             
#define T_ACLK	((float)(1/(float)(F_ACLK/PWMDIVIDERSETTING)))

// PWM Period Calculation ( PTPER = 2696 for ~350 kHz )
#define PERIODVALUE  ((unsigned int)(((float)((1/(float)(CONVSWITCHFREQ))/T_ACLK)-1))) 

#define ADCRESOLUTION  1241      // 4096/3.3V
#define DACRESOLUTION  1241

//Input Voltage Feedback Gain 
#define VINFBGAIN     0.181000   // 2.21k/(2.21k+10k)


//Input Voltage #defines
#define INPUTUNDERVOLTAGE 7      // Under Voltage threshold in volts
#define INPUTUNDERVOLTAGEADC (int)(INPUTUNDERVOLTAGE*VINFBGAIN*ADCRESOLUTION)

#define INPUTOVERVOLTAGE 11      // Over Voltage threshold in volts
#define INPUTOVERVOLTAGEADC  (int)(INPUTOVERVOLTAGE*VINFBGAIN*ADCRESOLUTION)

#define INPUTVOLTAGEHYST 0.5     // Hysteresis in volts
#define INPUTVOLTAGEHYSTADC  (int)(INPUTVOLTAGEHYST*VINFBGAIN*ADCRESOLUTION)

#define INPUTVOLTMINHYST (INPUTUNDERVOLTAGEADC + INPUTVOLTAGEHYSTADC)
#define INPUTVOLTMAXHYST (INPUTOVERVOLTAGEADC - INPUTVOLTAGEHYSTADC)


// Calculate temperature of MCP9700
// Vout = TCoefficient * TempAmbient + V0C, V_0C = 500mV , TCoeff = 10m
#define V_0C (int)(0.5*ADCRESOLUTION)											        
#define TEMPCOEFFICIENT (int)(32767/(.01*ADCRESOLUTION))

#define WARNINGTEMP     60              // In degrees Celsius
#define WARNINGTEMPADC  (int)  (((.01*WARNINGTEMP)+ 0.5)*(ADCRESOLUTION))

#define TEMPMAX         80              // In degrees Celsius
#define TEMPMAXADC	(int)  (((.01*TEMPMAX)+ 0.5)*(ADCRESOLUTION))

#define TEMPHYST	10		// In degrees Celsius

#define TEMPREINIT     (WARNINGTEMP - TEMPHYST)   // 50 C temperature of re-initialization
#define TEMPREINITADC  (int)  (((.01*TEMPREINIT)+ 0.5)*(ADCRESOLUTION))

//----------------- BUCK CONFIGURATIONS --------------- //
 
// Enable/Disable Buck Converter        
#define BUCK  ENABLED

// Output Voltage Setpoint        
#define BUCKVOLTAGEREFERENCE   3.3   // Buck output voltage in volts (max 3.8V with on-board load)        

//buck feedback gains   
#define VBUCKFBGAIN   0.755981   // 3.16k/(1.02k+3.16k)
#define IBUCKFBGAIN       0.96   // 1/125 * 120R

// Buck current limits
#define BUCKMAXCURRENT         2.8   // In Amps - taking into account the slope compensation ramp
#define BUCKMAXCURRENTDAC (unsigned int) (((BUCKMAXCURRENT*IBUCKFBGAIN)-0.3) * (DACRESOLUTION)) // ((2.8*0.96) - 0.3)*1241 = 2964 counts


#define BUCKVOLTAGEREFERENCEADC (unsigned int)(VBUCKFBGAIN*ADCRESOLUTION*BUCKVOLTAGEREFERENCE)
#define BUCKMAXDUTYCYCLE (PERIODVALUE - 50)  // Max duty cycle
#define BUCK_FB_LOOP_CHECK  (BUCKVOLTAGEREFERENCEADC*0.25)
        
// ----------------- BOOST CONFIGURATIONS --------------- //

// Enable/Disable Boost Converter
#define BOOST DISABLED


// Output Voltage Setpoint
#define BOOSTVOLTAGEREFERENCE   15   // Boost output voltage in volts (max 17.3V with on-board load)

//Boost feedback gains
#define VBOOSTFBGAIN  0.163399   // 1k/(1k + 5.12k)
#define IBOOSTFBGAIN      1.95   // two 3.9R in parallel

// Boost current limits
#define BOOSTMAXCURRENT       0.95   // Fuse rated for 1 Amp - modified so that fuse is just slightly below.
#define BOOSTMAXCURRENTDAC (unsigned int)(BOOSTMAXCURRENT*DACRESOLUTION*IBOOSTFBGAIN)           // 0.95*1241*1.95 = 2299 counts

#define BOOSTVOLTAGEREFERENCEADC (unsigned int)(VBOOSTFBGAIN*ADCRESOLUTION*BOOSTVOLTAGEREFERENCE*0.98)
#define BOOSTMAXDUTYCYCLE (PERIODVALUE*0.9)  // Max duty cycle
#define BOOST_FB_LOOP_CHECK (BOOSTVOLTAGEREFERENCEADC*0.27)

//   ----------- OPEN LOOP CONFIGURATIONS ----------------- //

#define OPENLOOP  DISABLED        // Removes the compensator and puts a fixed duty
                                  // cycle value when defined
#if (OPENLOOP == ENABLED)
#define BUCKOPENLOOPDC 1000
#define BUCKINCREMENT 1

#define BOOSTOPENLOOPDC 870
#define BOOSTINCREMENT  1

#else
#define BUCKINCREMENT   8
#define BOOSTINCREMENT  6 
#endif

#define SOFTSTARTRATE   15        // Time in us

#define TMR2PERIOD      (unsigned int)SOFTSTARTRATE*70  // us/14n = 70 (based on instruction clock)
#define TMR2SCALER      0

#endif	/* DEFINE_H */

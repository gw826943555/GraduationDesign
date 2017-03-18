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

#include "define.h"

#ifndef LOAD_CONFIG_H
#define	LOAD_CONFIG_H

// I2C setup for Loads
#define I2CBAUDRATE      690     // (((1/100k) - 110n) * 70M) - 2
#define SLAVEADDRESS    0x20

#define IODIR_REGADDR   0x00
#define IOCON_REGADDR   0x05
#define GPIO_REGADDR    0x09

// On-Board Load Options              Power
// ------------------------           -----
#define NOLOAD            0    //       0 W
#define LOADBANK1         1    //     ~0.5W
#define LOADBANK2         2    //    ~1.25W
#define LOADBANK1_2      12    //    ~1.75W
#define LOADBANK2_3      23    //     ~2.5W
#define LOADBANK1_2_3   123    //       ~3W
#define EXTERNALLOAD      7    //     ! User not to exceed 5W external load per converter !

// Note: If EXTERNALLOAD is selected, the following maximum
// currents should NOT be exceeded:

// Buck Converter:  1.52A  (5W)
// Boost Converter: 0.33A  (5W)

// It is recommended to only enable dynamic loading for one converter at a time
// although the software supports enabling both converters they will use the
// same frequency

//Buck Load configurations
#define BUCKDYNAMICLOAD  ENABLED

#if(BUCKDYNAMICLOAD == ENABLED)
#define BUCKLOAD1   LOADBANK1
#define BUCKLOAD2   LOADBANK2_3
#else
//Set static load condition
#define BUCKLOAD1   LOADBANK2

#endif

#define BUCKMINLOAD   (int)(((float)(BUCKVOLTAGEREFERENCE*BUCKVOLTAGEREFERENCE)/21.5)*100)

// Determine the load to be displayed on LCD based on output voltage set point of the buck converter
// Multiply by 100 for displaying the load (3-dig) to the LCD

#if(BUCKLOAD1 != EXTERNALLOAD)
 
    #if(BUCKLOAD1 == NOLOAD)
    #define BUCKLOAD1LCD 0
    #elif(BUCKLOAD1 == LOADBANK1)
    #define BUCKLOAD1LCD            (int)(((float)(BUCKVOLTAGEREFERENCE*BUCKVOLTAGEREFERENCE)/21.5)*100)    
    #elif(BUCKLOAD1 == LOADBANK2)
    #define BUCKLOAD1LCD            (int)(((float)(BUCKVOLTAGEREFERENCE*BUCKVOLTAGEREFERENCE)/8.71)*100)  
    #elif(BUCKLOAD1 == LOADBANK1_2)
    #define BUCKLOAD1LCD            (int)(((float)(BUCKVOLTAGEREFERENCE*BUCKVOLTAGEREFERENCE)/6.22)*100)  
    #elif(BUCKLOAD1 == LOADBANK2_3)
    #define BUCKLOAD1LCD            (int)(((float)(BUCKVOLTAGEREFERENCE*BUCKVOLTAGEREFERENCE)/4.356)*100) 
    #elif(BUCKLOAD1 == LOADBANK1_2_3)
    #define BUCKLOAD1LCD            (int)(((float)(BUCKVOLTAGEREFERENCE*BUCKVOLTAGEREFERENCE)/3.618)*100) 
    #endif

    #if(BUCKDYNAMICLOAD == ENABLED)
        #if(BUCKLOAD2 == LOADBANK1)
        #define BUCKLOAD2LCD            (int)(((float)(BUCKVOLTAGEREFERENCE*BUCKVOLTAGEREFERENCE)/21.5)*100)
        #elif(BUCKLOAD2 == LOADBANK2)
        #define BUCKLOAD2LCD            (int)(((float)(BUCKVOLTAGEREFERENCE*BUCKVOLTAGEREFERENCE)/8.71)*100)
        #elif(BUCKLOAD2 == LOADBANK1_2)
        #define BUCKLOAD2LCD            (int)(((float)(BUCKVOLTAGEREFERENCE*BUCKVOLTAGEREFERENCE)/6.22)*100)
        #elif(BUCKLOAD2 == LOADBANK2_3)
        #define BUCKLOAD2LCD            (int)(((float)(BUCKVOLTAGEREFERENCE*BUCKVOLTAGEREFERENCE)/4.356)*100)
        #elif(BUCKLOAD2 == LOADBANK1_2_3)
        #define BUCKLOAD2LCD            (int)(((float)(BUCKVOLTAGEREFERENCE*BUCKVOLTAGEREFERENCE)/3.618)*100)
        #endif
    #endif

#endif

// Value to write to MCP device to enable the corresponding loads

#if(BUCK == ENABLED)
    #if (BUCKLOAD1 ==  LOADBANK1)
        #define I2CBUCKLOAD1WRITE 0x01
        #elif (BUCKLOAD1 == LOADBANK2)
        #define I2CBUCKLOAD1WRITE 0x02
        #elif (BUCKLOAD1 == LOADBANK1_2)
        #define I2CBUCKLOAD1WRITE 0x03
        #elif (BUCKLOAD1 == LOADBANK2_3)
        #define I2CBUCKLOAD1WRITE 0x06
        #elif (BUCKLOAD1 == LOADBANK1_2_3)
        #define I2CBUCKLOAD1WRITE 0x07
        #else
        #define I2CBUCKLOAD1WRITE 0x00
    #endif

    #if(BUCKDYNAMICLOAD == ENABLED)
        #if(BUCKLOAD2 == LOADBANK1)
        #define I2CBUCKLOAD2WRITE 0x01
        #elif (BUCKLOAD2 == LOADBANK2)
        #define I2CBUCKLOAD2WRITE 0x02
        #elif (BUCKLOAD2 == LOADBANK1_2)
        #define I2CBUCKLOAD2WRITE 0x03
        #elif (BUCKLOAD2 == LOADBANK2_3)
        #define I2CBUCKLOAD2WRITE 0x06
        #elif (BUCKLOAD2 == LOADBANK1_2_3)
        #define I2CBUCKLOAD2WRITE 0x07
        #else
        #define I2CBUCKLOAD2WRITE 0x00
        #endif
    #endif
#else
#define I2CBUCKLOAD1WRITE 0x00
#endif

//Boost Load configurations
#define BOOSTDYNAMICLOAD DISABLED

#if(BOOSTDYNAMICLOAD == ENABLED)
#define BOOSTLOAD1   LOADBANK1
#define BOOSTLOAD2   LOADBANK2_3
#else
// Set static load condition
#define BOOSTLOAD1   LOADBANK2


#endif

#define BOOSTMINLOAD  (int)(((float)(BOOSTVOLTAGEREFERENCE*BOOSTVOLTAGEREFERENCE)/450)*100)

// Determine the load to be displayed on LCD based on output voltage set point of the boost converter
// Multiply by 100 for displaying the load (3-dig) to the LCD
#if(BOOSTLOAD1 != EXTERNALLOAD)

    #if(BOOSTLOAD1 == NOLOAD)
    #define BOOSTLOAD1LCD 0
    #elif(BOOSTLOAD1 == LOADBANK1)
    #define BOOSTLOAD1LCD           (int)(((float)(BOOSTVOLTAGEREFERENCE*BOOSTVOLTAGEREFERENCE)/450)*100)
    #elif(BOOSTLOAD1 == LOADBANK2)
    #define BOOSTLOAD1LCD           (int)(((float)(BOOSTVOLTAGEREFERENCE*BOOSTVOLTAGEREFERENCE)/180)*100)
    #elif(BOOSTLOAD1 == LOADBANK1_2)
    #define BOOSTLOAD1LCD           (int)(((float)(BOOSTVOLTAGEREFERENCE*BOOSTVOLTAGEREFERENCE)/128.57)*100)
    #elif(BOOSTLOAD1 == LOADBANK2_3)
    #define BOOSTLOAD1LCD           (int)(((float)(BOOSTVOLTAGEREFERENCE*BOOSTVOLTAGEREFERENCE)/90)*100)
    #elif(BOOSTLOAD1 == LOADBANK1_2_3)
    #define BOOSTLOAD1LCD           (int)(((float)(BOOSTVOLTAGEREFERENCE*BOOSTVOLTAGEREFERENCE)/75)*100)
    #endif

    #if(BOOSTDYNAMICLOAD == ENABLED)
        #if(BOOSTLOAD2 == LOADBANK1)
        #define BOOSTLOAD2LCD           (int)(((float)(BOOSTVOLTAGEREFERENCE*BOOSTVOLTAGEREFERENCE)/450)*100)
        #elif(BOOSTLOAD2 == LOADBANK2)
        #define BOOSTLOAD2LCD           (int)(((float)(BOOSTVOLTAGEREFERENCE*BOOSTVOLTAGEREFERENCE)/180)*100)
        #elif(BOOSTLOAD2 == LOADBANK1_2)
        #define BOOSTLOAD2LCD           (int)(((float)(BOOSTVOLTAGEREFERENCE*BOOSTVOLTAGEREFERENCE)/128.57)*100)
        #elif(BOOSTLOAD2 == LOADBANK2_3)
        #define BOOSTLOAD2LCD           (int)(((float)(BOOSTVOLTAGEREFERENCE*BOOSTVOLTAGEREFERENCE)/90)*100)
        #elif(BOOSTLOAD2 == LOADBANK1_2_3)
        #define BOOSTLOAD2LCD           (int)(((float)(BOOSTVOLTAGEREFERENCE*BOOSTVOLTAGEREFERENCE)/75)*100)
        #endif
    #endif

#endif



// Value to write to MCP device to enable the corresponding loads

#if (BOOST == ENABLED)
    #if(BOOSTLOAD1 == LOADBANK1)
        #define I2CBOOSTLOAD1WRITE 0x08
        #elif (BOOSTLOAD1 == LOADBANK2)
        #define I2CBOOSTLOAD1WRITE 0x20
        #elif (BOOSTLOAD1 == LOADBANK1_2)
        #define I2CBOOSTLOAD1WRITE 0x28
        #elif (BOOSTLOAD1 == LOADBANK2_3)
        #define I2CBOOSTLOAD1WRITE 0x30
        #elif (BOOSTLOAD1 == LOADBANK1_2_3)
        #define I2CBOOSTLOAD1WRITE 0x38
        #else
        #define I2CBOOSTLOAD1WRITE 0x00
    #endif

    #if(BOOSTDYNAMICLOAD == ENABLED)
        #if(BOOSTLOAD2 == LOADBANK1)
        #define I2CBOOSTLOAD2WRITE 0x08
        #elif (BOOSTLOAD2 == LOADBANK2)
        #define I2CBOOSTLOAD2WRITE 0x20
        #elif (BOOSTLOAD2 == LOADBANK1_2)
        #define I2CBOOSTLOAD2WRITE 0x28
        #elif (BOOSTLOAD2 == LOADBANK2_3)
        #define I2CBOOSTLOAD2WRITE 0x30
        #elif (BOOSTLOAD2 == LOADBANK1_2_3)
        #define I2CBOOSTLOAD2WRITE 0x38
        #else
        #define I2CBOOSTLOAD2WRITE 0x00
        #endif
    #endif
#else
#define I2CBOOSTLOAD1WRITE 0x00
#endif

#if((BUCKDYNAMICLOAD == ENABLED) || (BOOSTDYNAMICLOAD == ENABLED))
#define  DYNAMICPERIOD    1000            // Value in us (min value ~400us)

#if(DYNAMICPERIOD > 936)
#define TMRPERIOD       (unsigned int)DYNAMICPERIOD*9   // us/(8*14n) = ~9 (based on instruction clock)
#define TMRSCALER       1

#else
#define TMRPERIOD       (unsigned int)DYNAMICPERIOD*70  // us/14n = 70 (based on instruction clock)
#define TMRSCALER       0
#endif

#endif

#endif	/* LOAD_CONFIG_H */

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

#if((OPENLOOP == DISABLED) && (BUCK == ENABLED))

int16_t buckErrorControlHistory[4] __attribute__ ((space (ymemory), far));
int16_t buckABCoefficients[5]__attribute__ ((section (".xbss")));

SMPS_Controller_Options_T buckOptions;   // Create variable for buck converter options

#endif

#if((OPENLOOP == DISABLED) && (BOOST == ENABLED))

int16_t boostErrorControlHistory[4] __attribute__ ((space (ymemory), far));
int16_t boostABCoefficients[5]__attribute__ ((section (".xbss")));

SMPS_Controller_Options_T boostOptions;  // Create variable for boost converter options

#endif



#if((OPENLOOP == DISABLED) && (BUCK == ENABLED))
void InitBuckComp(void)
{

    MACRO_CLR_BUCKHISTORY();

    buckABCoefficients[0] = BUCK_COMP_2P2Z_COEFF_B0;
    buckABCoefficients[1] = BUCK_COMP_2P2Z_COEFF_B1;
    buckABCoefficients[2] = BUCK_COMP_2P2Z_COEFF_B2;

    buckABCoefficients[3] = BUCK_COMP_2P2Z_COEFF_A1;
    buckABCoefficients[4] = BUCK_COMP_2P2Z_COEFF_A2;

    // Library options:        // For 'triggerSelectFlag', only one bit may be set:

    buckOptions.triggerSelectFlag = 0;  // 00 = Trigger functions disabled (0)
                                        // 10 = Trigger On-Time enabled    (1)
                                        // 10 = Trigger Off-Time enabled   (2)
    buckOptions.delayValue = 0;
    buckOptions.trigger    = &TRIG1;  // Pointer to TRIG1 register
    buckOptions.period     = &PTPER;  // Pointer to period register

    InitAltRegContext1Setup();       // Setup  working registers to be used with compensator

}
#endif

#if((OPENLOOP == DISABLED) && (BOOST == ENABLED))
void InitBoostComp(void)
{

    MACRO_CLR_BOOSTHISTORY();

    boostABCoefficients[0] = BOOST_COMP_2P2Z_COEFF_B0;
    boostABCoefficients[1] = BOOST_COMP_2P2Z_COEFF_B1;
    boostABCoefficients[2] = BOOST_COMP_2P2Z_COEFF_B2;

    boostABCoefficients[3] = BOOST_COMP_2P2Z_COEFF_A1;
    boostABCoefficients[4] = BOOST_COMP_2P2Z_COEFF_A2;

    // Library options:        // For 'triggerSelectFlag', only one bit may be set:

    boostOptions.triggerSelectFlag = 0; // 00 = Trigger functions disabled (0)
                                        // 10 = Trigger On-Time enabled    (1)
                                        // 10 = Trigger Off-Time enabled   (2)
    boostOptions.delayValue = 0;
    boostOptions.trigger    = &TRIG2; // Pointer to TRIG2 register
    boostOptions.period     = &PTPER; // Pointer to period register

    InitAltRegContext2Setup();         // Setup working registers to be used with compensator

}
#endif
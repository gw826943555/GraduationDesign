////////////////////////////////////////////////////////////////////////////////
// � 2015 Microchip Technology Inc.
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
#include  "main.h"

#ifndef ISR_H
#define ISR_H

#define MASTERWRITESLAVEADDR 0
#define MASTERWRITESREGADDR  1
#define MASTERWRITESREGDATA  2
#define STOPCONDITION        3
#define RESET                4


//Declare variables 

extern uint8_t I2CLoadWrite, I2CRegAddr;
extern uint16_t refreshLCD;

#if(BUCK == ENABLED)
extern int16_t buckErrorControlHistory[4] __attribute__ ((space (ymemory), far));
#endif

#if(BOOST == ENABLED)
extern int16_t boostErrorControlHistory[4] __attribute__ ((space (ymemory), far));
#endif

DPSK_FAULTS dpskFaultFlags;
DPSK_FLAGS  dpskFlags;

#endif	/* ISR_H */
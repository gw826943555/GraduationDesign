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


#include "p33Exxxx.h"
#include "stdint.h"
#include "init.h"
#include "lcd_dpsk.h"
#include "libpic30.h"
#include "load_config.h"
#include "boost_dcdt.h"
#include "buck_dcdt.h"
#include "pushButton.h"

#ifndef MAIN_H
#define	MAIN_H

typedef union{

    struct{
        uint16_t inputVoltage   : 1;
        uint16_t buckSoftStart  : 1;
        uint16_t boostSoftStart : 1;
        uint16_t tempWarning    : 1;
        uint16_t overTemp       : 1;
        uint16_t                : 10;
       };

       uint16_t systemFaults;

} DPSK_FAULTS;


 typedef union{

    struct{
        uint16_t buckSSActive   : 1;
        uint16_t boostSSActive  : 1;
        uint16_t buckDynLoad    : 1;
        uint16_t boostDynLoad   : 1;
        uint16_t                : 1;
        uint16_t                :10;
    };

    uint16_t systemFlags;

} DPSK_FLAGS;

//declare variables 
extern uint16_t LCD_BuckLoad, LCD_BoostLoad;
extern int16_t  boostControlReference;
extern DPSK_FLAGS  dpskFlags;
extern DPSK_FAULTS dpskFaultFlags;

#endif	/* MAIN_H */
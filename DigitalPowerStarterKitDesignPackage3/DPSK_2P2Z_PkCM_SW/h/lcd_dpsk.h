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
#include "define.h"
#include "libpic30.h"
#include "lcd.h"
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_DPSK_H
#define	LCD_DPSK_H



// Coefficients used to calculate LCD Measurements
// Converts ADC reading back to voltage and scaled by 100 for 3 digits for LCD (Q15)
#define VBUCK_LCD_FACTOR (int) ((100/(ADCRESOLUTION * VBUCKFBGAIN)) * 32767)

#define VBOOST_LCD_FACTOR (unsigned int) ((102/(ADCRESOLUTION * VBOOSTFBGAIN)) * 32767)

//Will need to post multiply by two as number exceeds uint range
#define VIN_FACTOR (unsigned int) ((102/(ADCRESOLUTION * VINFBGAIN)) * 32767)

//#define SW1 PORTBbits.RB8		// Push Button status

//Function definitions related to LCD write and push button status 

void LCD_DPSK_ADCShortToString(int16_t Value, int16_t DotPos, char *Buffer);
void LCD_DPSK_Write(void);
void LCD_DPSK_Refresh(void);
void LCD_DPSK_DisplayFault(void);
void LCD_DPSK_SwitchDisplay(void);

extern uint16_t tempSense;
extern uint16_t buckVoltage,boostVoltage,inputVoltage;

#endif	/* LCD_DPSK_H */


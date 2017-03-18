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

#ifndef __LCD_H
#define __LCD_H


//******************************************************/
//		LCD DEFINES
//******************************************************/
// Registers and Register Bits
// LCD port pins
#define LCD_CS		    LATBbits.LATB11
#define LCD_SCL		    LATBbits.LATB10
#define LCD_SDI		    LATBbits.LATB1
#define LCD_RS		    LATBbits.LATB5
#define LCD_RST		    LATBbits.LATB15

#define TRIS_LCD_CS         TRISBbits.TRISB11
#define TRIS_LCD_SCL        TRISBbits.TRISB10
#define TRIS_LCD_SDI        TRISBbits.TRISB1
#define TRIS_LCD_RS         TRISBbits.TRISB5
#define TRIS_LCD_RST        TRISBbits.TRISB15

// Number Assignment, Misc.
#define LCD_RS_COMMAND      0
#define LCD_RS_DATA         1
#define LCD_LOW             0
#define LCD_HIGH            1
#define LCD_SELECTED        0
#define LCD_nSELECTED       1




//******************************************************/
//		LCD Prototypes
//******************************************************/

extern void LCD_Init(void);
extern void lcd_clear(void);
extern void lcd_goto(uint8_t x, uint8_t y);
extern void lcd_putchar(const char c);
extern void lcd_putstr(const char *s);
extern void lcd_putcmd(uint8_t Command);
extern void lcd_putline(uint8_t l, const char *s);
extern void lcd_backlight_on(void);
extern void lcd_backlight_off(void);


//----------------------------------------------------------------------------

#endif // __LCD_H

//******************************************************/
//		LCD_cmds Defines
//******************************************************/
// Command set for the LCD LCD driver used by the Newhaven NHD-C0216CZ-FSW-FBW

#ifndef __LCD_CMDS_H
#define __LCD_CMDS_H

#define LCD_CLEAR       0x01
#define LCD_HOME        0x02

#define CURSOR_nSHIFT   0x00
#define CURSOR_SHIFT    0x01
#define DATA_DECREMENT  0x00
#define DATA_INCREMENT  0x02
#define LCD_ENTRY_MODE  0x04

#define CURSOR_OFF      0x00
#define CURSOR_ON       0x02
#define BLINK_OFF       0x00
#define BLINK_ON        0x01
#define LCD_DISPLAY_OFF 0x08
#define LCD_DISPLAY_ON  0x0C


#define FUNCTION_nIS    0x00
#define FUNCTION_IS     0x01
#define FUNCTION_1_HIGH 0x00
#define FUNCTION_2_HIGH 0x04
#define FUNCTION_1_LINE 0x00
#define FUNCTION_2_LINE 0x08
#define FUNCTION_4BITS  0x00
#define FUNCTION_8BITS  0x10

#define LCD_FUNCTION    0x20

#define LCD_CGRAM_ADDRESS(adr) (0x40 | (adr & 0x3F))
#define LCD_DDRAM_ADDRESS(adr) (0x80 | (adr & 0x7F))

//** Second Instruction Page (IS)
#define BIAS_1_5      0x00
#define BIAS_1_4      0x08
#define FREQ_CNTRL(f) (f&0x07)
#define LCD_OSC_FREQ  0x10


#define LCD_ICON_ADDRESS(adr) (0x40 | (adr & 0x0F))

#define nICON           0x00
#define ICON            0x08
#define nBOOST          0x00
#define BOOSTLCD        0x04
#define CONTRAST(c)    (c&0x03)
#define LCD_PWR_CONTROL 0x50

#define FOLLOWER_GAIN(g) (g&0x07)
#define LCD_FOLLOWER_OFF   0x60
#define LCD_FOLLOWER_ON    0x68

#define LCD_CONTRAST(c) (0x70 | (c & 0x0F))

#define LCD_BUSY_FLAG_MASK 0x80
#define LCD_ADDRESS_MASK   0x7F

#define LCD_ADDRESS_LINE_1 0x00
#define LCD_ADDRESS_LINE_2 0x40

#endif //__LCD_CMDS_H
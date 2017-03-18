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

#include "lcd.h"




const int8_t line_address[] = {LCD_ADDRESS_LINE_1,LCD_ADDRESS_LINE_2};

///////////////////////////////////////////////////////////////////////////////
// Function:             SPI_TX
//
// PreCondition: 	LCD must be setup.
//
// Side Effects: 	Writes to screen
//
///////////////////////////////////////////////////////////////////////////////
// @ingroup  		LCD
//
// @brief    		This function writes to the LCD screen.
//
// @note    			Send byte via spi to the lcd
//
///////////////////////////////////////////////////////////////////////////////
void SPI_TX(uint8_t Command)
{
  uint8_t mask;

   for(mask = 0x80; mask != 0; mask >>= 1)
   {
     LCD_SCL = LCD_LOW;
     Nop();
     __delay_us(1);
     if(Command & mask) LCD_SDI = LCD_HIGH; else LCD_SDI = LCD_LOW;
     LCD_SCL = LCD_HIGH;
     Nop();
     __delay_us(1);
    }
    LCD_CS  = LCD_nSELECTED;
    __delay_us(50);
}



//////////////////////////////////////////////////////////////////////////////
// Function:             lcd_goto
//
// PreCondition: 	None
//
// Side Effects: 	Moves cursor.
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// @ingroup  		LCD
//
// @brief    		This function points to an LCD position.
//
// @note    		None
//
//////////////////////////////////////////////////////////////////////////////
void lcd_goto(uint8_t x,uint8_t y)
{
    lcd_putcmd(LCD_DDRAM_ADDRESS((line_address[y] + x)));
}

//////////////////////////////////////////////////////////////////////////////
// Function:             lcd_clear
//
// PreCondition: 	None
//
// Side Effects: 	Clears LCD
//
//
// @ingroup  		LCD
//
// @brief    		This function clears the LCD screen.
//
// @note    		None
//
//////////////////////////////////////////////////////////////////////////////
void lcd_clear(void)
{
    lcd_putcmd(LCD_CLEAR);   //clear
    __delay_us(20);
}

//////////////////////////////////////////////////////////////////////////////
// Function:             lcd_putline
//
// PreCondition: 	None
//
// Side Effects: 	None
///
///
// @ingroup  		LCD
//
// @brief    		This function sends an LCD message.
//
// @note    		Sends LCD message and line location
//
//////////////////////////////////////////////////////////////////////////////
void lcd_putline(uint8_t l, const char *buffer)
{
    lcd_putcmd(line_address[l]);
    lcd_putstr(buffer);
}

//////////////////////////////////////////////////////////////////////////////
// Function:             lcd_putstr
//
// PreCondition: 	None
//
// Side Effects: 	Writes message to LCD
//
//
// @ingroup  		LCD
//
// @brief    		This function writes a string to the LCD.
//
// @note    		Write data to LCD up to null
//
//////////////////////////////////////////////////////////////////////////////
void lcd_putstr(const char *s)
{
    while(*s)              
    {
	lcd_putchar(*s++); 
    }
}

/////////////////////////////////////////////////////////////////////////////
// Function:         LCD_Init
//
// PreCondition: 	None
//
// Side Effects: 	Sets up LCD
//
//
// @ingroup  		LCD
//
// @brief    		This function initialises the LCD.
//
// @note    		None
//
//////////////////////////////////////////////////////////////////////////////
void LCD_Init(void)
{
   TRIS_LCD_RST   = 0;
   TRIS_LCD_CS    = 0;
   TRIS_LCD_RS    = 0;

   TRIS_LCD_SDI   = 0;
   TRIS_LCD_SCL   = 0;
   
   LCD_RST        = 0;  // RESET
   __delay_ms(25);

   LCD_RST        = 1;  // end reset
  
   lcd_putcmd(LCD_FUNCTION | FUNCTION_8BITS | FUNCTION_1_HIGH | FUNCTION_1_LINE | FUNCTION_nIS);   //function set
 
   __delay_ms(25);

   lcd_putcmd(LCD_FUNCTION | FUNCTION_8BITS | FUNCTION_1_HIGH | FUNCTION_1_LINE | FUNCTION_nIS);   //function set
   lcd_putcmd(LCD_FUNCTION | FUNCTION_8BITS | FUNCTION_1_HIGH | FUNCTION_1_LINE | FUNCTION_nIS);   //function set

   // Enter the second page of instructions
   lcd_putcmd(LCD_FUNCTION | FUNCTION_8BITS | FUNCTION_1_HIGH | FUNCTION_2_LINE | FUNCTION_IS);   //function set
   lcd_putcmd(LCD_OSC_FREQ | BIAS_1_5 | FREQ_CNTRL(4));   //internal osc frequency
   lcd_putcmd(LCD_PWR_CONTROL | nICON | BOOSTLCD | CONTRAST(2));   //power control
   lcd_putcmd(LCD_FOLLOWER_ON | FOLLOWER_GAIN(5));   //follower control
   lcd_putcmd(LCD_CONTRAST(0));   //contrast
   // leave second instruction page
   
   //lcd_putcmd(LCD_FUNCTION | FUNCTION_8BITS | FUNCTION_1_HIGH | FUNCTION_2_LINE | FUNCTION_nIS);   //function set
   lcd_putcmd(LCD_DISPLAY_ON | CURSOR_OFF | BLINK_OFF);           //display on
   lcd_putcmd(LCD_ENTRY_MODE | CURSOR_nSHIFT | DATA_INCREMENT);   //entry mode
   lcd_putcmd(LCD_CLEAR);   //clear

   __delay_ms(150);

   // Load LCD Startup Display
   lcd_goto(0,0);
   lcd_putstr(" Digital Power  ");
   lcd_goto(0,1);
   lcd_putstr("  Starter Kit   ");
   __delay_ms(1500);
   lcd_goto(0,0);
   lcd_putstr("   MICROCHIP    ");
   lcd_goto(0,1);
   lcd_putstr("dsPIC33EP64GS502");
   __delay_ms(1000);
 
}


/////////////////////////////////////////////////////////////////////////////
// Function:             lcd_putcmd
//
// PreCondition: 	None
//
// Side Effects: 	Sends command to the LCD.
//
//
// @ingroup  		LCD
//
// @brief    		This function sends a command to the LCD.
//
// @note    		Send comand byte to the lcd
//
//////////////////////////////////////////////////////////////////////////////
void lcd_putcmd(uint8_t Command)
{		
   LCD_CS = LCD_SELECTED;
   LCD_RS = LCD_RS_COMMAND;
   SPI_TX(Command);
}

//////////////////////////////////////////////////////////////////////////////
// Function:             lcd_putchar
//
// PreCondition: 	None
//
// Side Effects: 	Puts character on LCD
//
//
// @ingroup  		LCD
//
// @brief    		This function puts a character onto the screen.
//
// @note    		Write data to the lcd
//
//////////////////////////////////////////////////////////////////////////////
void lcd_putchar(const char c)
{
   LCD_CS = LCD_SELECTED;
   LCD_RS = LCD_RS_DATA;
   SPI_TX(c);
}
//----------------------------------------------------------------------------



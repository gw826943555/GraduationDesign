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

#include "lcd_dpsk.h"
#include "main.h"


uint8_t  LCDselect    = 0, faultDisplayCnt = 0;
uint16_t LCD_BuckLoad = 0, LCD_BoostLoad   = 0;
uint16_t refreshLCD   = 0;

#if(BUCKLOAD1 != EXTERNALLOAD)
char LCD_buckStr1[17]  = "Buck 0.00V 0.00W";  // LCD text templates
#else
char LCD_buckStr1[17]  = "Buck 0.00V EXTRN";
#endif

#if(BOOSTLOAD1 != EXTERNALLOAD)
char LCD_boostStr1[17]  = "Bst 00.00V 0.00W";
#else
char LCD_boostStr1[17]  = "Bst 00.00V EXTRN";
#endif

char Vin_str[17]  = "V_Input:       V";
// Temp Display Templates when converters enabled
char BuckTemp_str[17]    = "Buck Temp:     C";
char BoostTemp_str[17]   = "Boost Temp:    C";
char ambientTemp_str[17] = "Amb Temp:      C";

char* Temp_str;



///////////////////////////////////////////////////////////////////////////////
 // Function: LCD_DPSK_write()
 //
 // Preconditions : LCD_init()
 //
 // Overview: The function checks for push button and faults and writes the updated information to LCD accordingly
 //
 // Input: None.
 // Output: None.
 //////////////////////////////////////////////////////////////////////////////

void LCD_DPSK_Write(void)
{
       if(refreshLCD >= LCD_REFRESHCOUNT)
       {
         refreshLCD = 0;

         faultDisplayCnt++;

         if((dpskFaultFlags.systemFaults != 0) && (faultDisplayCnt == 4))
         {
           LCD_DPSK_DisplayFault();
         }
         else
         {
            if(dpskFaultFlags.inputVoltage == 1)
            {
              LCDselect = 1;          // During input voltage fault, force LCD to show fault & Vin/temp screen
              LCD_DPSK_Refresh();
            }
            
            else
            {
              LCD_DPSK_Refresh();          // Normal operation
            }
         }

          if(faultDisplayCnt > 4)
          {
            faultDisplayCnt = 0;
          }
        }
}
///////////////////////////////////////////////////////////////////////////////
 // Function: LCD_DPSK_SwitchDisplay(void)
 //
 // Preconditions : None
 //
 // Overview:       Update LCDselect if the push button SW1 is pressed
 //
 // Input:          checkButton_SW1(void).
 //
 // Output:         LCDselect.
 //
 //////////////////////////////////////////////////////////////////////////////

void LCD_DPSK_SwitchDisplay(void)
{
    LCDselect++;

    if(LCDselect > 1)
    {
        LCDselect = 0;            // Reset Push-button count
    }
}
///////////////////////////////////////////////////////////////////////////////
 // Function: LCD_DPSK_Refresh()
 //
 // Preconditions : LCD_init()
 //
 // Overview: The function measures and updates LCD displayed information
 //
 // Input: None.
 // Output: None.
 //////////////////////////////////////////////////////////////////////////////

void LCD_DPSK_Refresh(void)
{
    uint16_t LCDBuckVo      = 0, LCDBoostVo = 0;
    uint16_t LCDVinMeasured = 0, LCDTempC   = 0;

    lcd_goto(0,0);

    if(LCDselect == 0)	// Default LCD Display
    {
      // Write to strings template and update with measurements
      // LCD_str1 "Buck 0.00V 0.00W";
      // LCD_str2 "BST 00.00V 0.00W";

      // Only minimum loads are enabled if over temperature fault is set
      if(dpskFaultFlags.overTemp == 1)
      {
        #if(BOOSTLOAD1 != EXTERNALLOAD)
        LCD_BoostLoad = BOOSTMINLOAD;
        #endif

        #if(BUCKLOAD1 != EXTERNALLOAD)
        LCD_BuckLoad  = BUCKMINLOAD;
        #endif
      }
      
      else
      {
        #if(BUCKLOAD1 != EXTERNALLOAD)
        if(BUCKDYNAMICLOAD == DISABLED)
        LCD_BuckLoad  = BUCKLOAD1LCD;
        #endif

        #if(BOOSTLOAD1 != EXTERNALLOAD)
        if(BOOSTDYNAMICLOAD == DISABLED)
        LCD_BoostLoad = BOOSTLOAD1LCD;
        #endif
      }

      // Factor to display Buck/Boost Voltage on LCD
      LCDBuckVo = (__builtin_mulss(buckVoltage, VBUCK_LCD_FACTOR)>>15);
      LCD_DPSK_ADCShortToString((int)LCDBuckVo, 2, LCD_buckStr1+5);

      #if(BUCKLOAD1 != EXTERNALLOAD)
      LCD_DPSK_ADCShortToString(LCD_BuckLoad, 2, LCD_buckStr1+11);
      #endif

      LCDBoostVo = (__builtin_mulss(boostVoltage, VBOOST_LCD_FACTOR)>>15);
      LCD_DPSK_ADCShortToString((int)LCDBoostVo, 2, LCD_boostStr1+4);

      #if(BOOSTLOAD1 != EXTERNALLOAD)

      LCD_DPSK_ADCShortToString(LCD_BoostLoad, 2, LCD_boostStr1+11);

      #endif


      #if((BOOST == DISABLED) && (BUCK == ENABLED))
    
      if(dpskFaultFlags.buckSoftStart == 1)
      lcd_putstr("Bck Output Fault");

      else
      lcd_putstr(LCD_buckStr1);

      lcd_goto(0,1);
      lcd_putstr("Boost: Disabled ");

      #elif((BOOST == ENABLED) && (BUCK == DISABLED))
  
      lcd_putstr("Buck:  Disabled ");

      lcd_goto(0,1);

      if(dpskFaultFlags.boostSoftStart == 1)
      lcd_putstr("Bst Output Fault");

      else
      lcd_putstr(LCD_boostStr1);

      #elif((BOOST == ENABLED) && (BUCK == ENABLED))
   
      if(dpskFaultFlags.buckSoftStart == 1)
      lcd_putstr("Bck Output Fault");

      else
      lcd_putstr(LCD_buckStr1);

      lcd_goto(0,1);

      if(dpskFaultFlags.boostSoftStart == 1)
      lcd_putstr("Bst Output Fault");

      else
      lcd_putstr(LCD_boostStr1);

      #else
      // Write to LCD
      lcd_putstr("Buck:  Disabled ");
      lcd_goto(0,1);
      lcd_putstr("Boost: Disabled ");
      #endif

    }

    // Display Input Voltage and Board Temperature
    else
    {
      // Calculate Input Voltage & Temperature Conversion
      LCDVinMeasured = (__builtin_mulsu(inputVoltage, VIN_FACTOR)>>15);
      LCDTempC = (__builtin_mulss(tempSense - V_0C, TEMPCOEFFICIENT )>>15);

      // Modify String Template and update with Voltage measurements
      LCD_DPSK_ADCShortToString((int)LCDVinMeasured, 2, Vin_str+11);


      if((BUCK == ENABLED) && (LATBbits.LATB13 == 0))
      { Temp_str = BuckTemp_str;}

      else if((BOOST == ENABLED) && (LATBbits.LATB13 == 1))
      { Temp_str = BoostTemp_str;}

      else if((BUCK == DISABLED) && (BOOST == DISABLED))
      { Temp_str = ambientTemp_str;}

      // Modify String Template and update with Temp measurements
      LCD_DPSK_ADCShortToString((int)LCDTempC, 4, Temp_str+12);

      // Write to LCD
      lcd_putstr(Vin_str);
      lcd_goto(0,1);
      lcd_putstr(Temp_str);

      // Change MUX input to monitor both temp sensors
      if((BUCK == ENABLED) && (BOOST == ENABLED))
      {
        LATBbits.LATB13 ^= 1;
      }

    }
}


//----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
 // Function: LCD_DPSK_ADCShortToString
 //
 // Preconditions : None.
 //
 // Overview: The function converts integer into string.
 //
 // Input: Value - value to be converted; DotPos - dot position ( can be
 // between 0 and 3, DOTPOS_NONE = 4, if equals DOTPOS_TRAIL_ZEROS = -1 will not
 // put a dot and insert leading zeros); Buffer - receives the result string
 //
 // Output: None.
 //
 //////////////////////////////////////////////////////////////////////////////

void LCD_DPSK_ADCShortToString(int16_t Value, int16_t DotPos, char* Buffer)
{
    int8_t  Result = 0;
    int16_t Pos    = 0;

    // Clean Buffer (4 digits + Dot)
    for(Pos = 0; Pos < 3; Pos++) Buffer[Pos] = ' ';

    Pos = 0;  // Reset to initial buffer position
    if(Pos == DotPos){ *Buffer++ = '0';*Buffer++ = '.';}
    Pos++;
    Result = Value/1000;
    Value -= 1000*Result;
    if(Result) *Buffer++ = Result + '0';
    else if(Pos >= DotPos) *Buffer++ = '0';

    if(Pos == DotPos) *Buffer++ = '.'; Pos++;
    Result = Value/100;
    Value -= 100*Result;
    if(Result) *Buffer++ = Result + '0';
    else if(Pos >= DotPos) *Buffer++ = '0';

    if(Pos == DotPos) *Buffer++ = '.'; Pos++;
    Result = Value/10;
    Value -= 10*Result;
    if(Result) *Buffer++ = Result + '0';
    else if(Pos >= DotPos) *Buffer++ = '0';

    if(Pos == DotPos) *Buffer++ = '.'; Pos++;
    if(Value) *Buffer++ = Value + '0';
    else if(Pos >= DotPos) *Buffer++ = '0';

}

////////////////////////////////////////////////////////////////////////////////
 // Function: LCD_DPSK_DisplayFault()
 //
 // Preconditions : None.
 //
 // Overview: Display fault condition or warnings on LCD screen when fault
 //           occurs.
 //
 // Input: None.
 //
 // Output: None.
 //
 ///////////////////////////////////////////////////////////////////////////////

void LCD_DPSK_DisplayFault(void)
{
  
  lcd_goto(0,0); // Starting at position (0,0)

  // If both input voltage and Temp faults occur, LCD will only display fault
  // for input voltage as this is the more critical fault.

    if(dpskFaultFlags.inputVoltage == 1)
    {
      lcd_putstr(" INPUT VOLTAGE  ");
      lcd_goto(0,1);
      lcd_putstr("     FAULT      ");
    }

    else if(dpskFaultFlags.overTemp == 1)
    {
      lcd_putstr(" OVER TEMP FAULT ");
      lcd_goto(0,1);
      lcd_putstr(" MIN LOAD ENABLE ");

    }
  
    else if(dpskFaultFlags.tempWarning == 1)
    {
      lcd_putstr("HIGH TEMPERATURE ");
      lcd_goto(0,1);
      lcd_putstr("     WARNING     ");
    }
}

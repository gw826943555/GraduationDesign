/**
  Summary:
  This header file was created using Microchip Digital Compensator Design Tool (DCDT)
  and includes system summary and digital compensator coefficients. This file
  should be included in the MPLAB X project directory.

  File Name:     buck_dcdt.h
  Project Name:  buck
  Date:          9/3/2015
  Time:          13:46.58

  Software License Agreement

  Copyright © 2015 Microchip Technology Inc.  All rights reserved.
  Microchip licenses to you the right to use, modify, copy and distribute
  Software only when embedded on a Microchip microcontroller or digital
  signal controller, which is integrated into your product or third party
  product (pursuant to the sublicense terms in the accompanying license
  agreement).

  You should refer to the license agreement accompanying this Software
  for additional information regarding your rights and obligations.

  SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
  OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
  PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
  OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
  BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
  DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
  INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
  COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
  CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
  OR OTHER SIMILAR COSTS.
 **/
#ifndef _BUCK_DCDT_DEFINES_H
#define _BUCK_DCDT_DEFINES_H

/**
  Compensator Type:  2P2Z
      Entry                Value  
    ---------            ---------
  Pole 0                 6.0420e+03 Hz
  Pole 2                 2.0854e+04 Hz
  Zero 1                 2.0000e+02 Hz
  Gain(Kdc)              1.000
  Warp                   false
  PWM Frequency          3.5000e+05
  PWM Sampling Ratio     2
  Sampling Frequency     1.7500e+05
  PWM Max Resolution     1.0600e-09
  Computational Delay    3.0000e-07
  Control Output Min.    0
  Control Output Max.    4095


  PWM Calculations
      Name                Value  
    ---------           ---------
  Bits of Resolution    12.396
  Gain                  1.855e-04


  s-domain transfer function

               Wp0   Wp2(Wz1 + s)
  H(s) = Kdc X --- X ------------
                s    Wz1(Wp2 + s)

                  3.80e+04   1.31e+05(1.26e+03 + s)
  H(s) = 1.000 X -------- X ----------------------
                     s       1.26e+03(1.31e+05 + s)



  Digital Compensator Coefficients

  Name    Value     Normalized    Q15      Hex
  ----    -----     ----------    ---      ---
  a1      1.455     0.176         5773     0x168D
  a2      -0.455    -0.055        -1805    0xF8F3
  b0      8.259     1.000         32764    0x7FFC
  b1      0.059     0.007         234      0x00EA
  b2      -8.199    -0.993        -32530   0x80EE


  z-domain transfer function

         u(z)  B0 + B1z^(-1) + B2z^(-2)
  H(z) = --- = ------------------------
         e(z)  A0 - A1z^(-1) - A2z^(-2)

          (8.259) + (0.059)z^(-1) + (-8.199)z^(-2)
  H(z) = ---------------------------------------------
          1 - (1.455)z^(-1) - (-0.455)z^(-2)

**/


// Compensator Coefficient Defines
#define BUCK_COMP_2P2Z_COEFF_A1      0x168D
#define BUCK_COMP_2P2Z_COEFF_A2      0xF8F3
#define BUCK_COMP_2P2Z_COEFF_B0      0x7FFC
#define BUCK_COMP_2P2Z_COEFF_B1      0x00EA
#define BUCK_COMP_2P2Z_COEFF_B2      0x80EE
#define BUCK_COMP_2P2Z_POSTSCALER    0x4213
#define BUCK_COMP_2P2Z_POSTSHIFT     0xFFFC
#define BUCK_COMP_2P2Z_PRESHIFT      0x0000


// Compensator Clamp Limits
#define BUCK_COMP_2P2Z_MIN_CLAMP    0x0000
#define BUCK_COMP_2P2Z_MAX_CLAMP    0x0FFF


#endif

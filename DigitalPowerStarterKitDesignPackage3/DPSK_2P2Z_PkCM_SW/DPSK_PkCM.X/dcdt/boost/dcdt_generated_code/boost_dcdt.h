/**
  Summary:
  This header file was created using Microchip Digital Compensator Design Tool (DCDT)
  and includes system summary and digital compensator coefficients. This file
  should be included in the MPLAB X project directory.

  File Name:     boost_dcdt.h
  Project Name:  boost
  Date:          9/3/2015
  Time:          13:43.42

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
#ifndef _BOOST_DCDT_DEFINES_H
#define _BOOST_DCDT_DEFINES_H

/**
  Compensator Type:  2P2Z
      Entry                Value  
    ---------            ---------
  Pole 0                 3.0000e+04 Hz
  Pole 2                 1.4403e+04 Hz
  Zero 1                 6.0000e+02 Hz
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

                  1.88e+05   9.05e+04(3.77e+03 + s)
  H(s) = 1.000 X -------- X ----------------------
                     s       3.77e+03(9.05e+04 + s)



  Digital Compensator Coefficients

  Name    Value      Normalized    Q15      Hex
  ----    -----      ----------    ---      ---
  a1      1.589      0.153         5014     0x1396
  a2      -0.589     -0.057        -1859    0xF8BD
  b0      10.383     1.000         32764    0x7FFC
  b1      0.221      0.021         698      0x02BA
  b2      -10.161    -0.979        -32066   0x82BE


  z-domain transfer function

         u(z)  B0 + B1z^(-1) + B2z^(-2)
  H(z) = --- = ------------------------
         e(z)  A0 - A1z^(-1) - A2z^(-2)

          (10.383) + (0.221)z^(-1) + (-10.161)z^(-2)
  H(z) = ---------------------------------------------
          1 - (1.589)z^(-1) - (-0.589)z^(-2)

**/


// Compensator Coefficient Defines
#define BOOST_COMP_2P2Z_COEFF_A1      0x1396
#define BOOST_COMP_2P2Z_COEFF_A2      0xF8BD
#define BOOST_COMP_2P2Z_COEFF_B0      0x7FFC
#define BOOST_COMP_2P2Z_COEFF_B1      0x02BA
#define BOOST_COMP_2P2Z_COEFF_B2      0x82BE
#define BOOST_COMP_2P2Z_POSTSCALER    0x5312
#define BOOST_COMP_2P2Z_POSTSHIFT     0xFFFC
#define BOOST_COMP_2P2Z_PRESHIFT      0x0000


// Compensator Clamp Limits
#define BOOST_COMP_2P2Z_MIN_CLAMP    0x0000
#define BOOST_COMP_2P2Z_MAX_CLAMP    0x0FFF


#endif

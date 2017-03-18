;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; © 2015 Microchip Technology Inc.
;;
;; MICROCHIP SOFTWARE NOTICE AND DISCLAIMER:  You may use this software, and any 
;;derivatives, exclusively with Microchip?s products. This software and any 
;;accompanying information is for suggestion only.  It does not modify Microchip?s 
;;standard warranty for its products.  You agree that you are solely responsible 
;;for testing the software and determining its suitability.  Microchip has no 
;;obligation to modify, test, certify, or support the software.
;;
;; THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER EXPRESS,
;;IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF
;;NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE, OR ITS 
;;INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE 
;;IN ANY APPLICATION.
 
;;IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL 
;;OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE 
;;SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR 
;;THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S 
;;TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED 
;;THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

;;MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE TERMS. 

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


.include "p33Exxxx.inc"
#include "boost_dcdt.h"
#include "buck_dcdt.h"
#include "define.h"

.data   ; Tell assembler to add subsequent data to the data section

.text   ; Begin program instructions


.if(BUCK == ENABLED)

     .global _InitAltRegContext1Setup

  _InitAltRegContext1Setup:

  CTXTSWP #0x1   ;Swap to Alternate W-Reg context #1

  ; Note: w0 register will be used for compensator control reference parameter
  ; Initialize Alternate Working Registers context #1
  mov #ADCBUF1,                   w1    ; Address of the ADCBUF1 register  (Input)
  mov #CMP1DAC,                   w2    ; Address of the CMP1DAC target register (Output)

  ; w3, w4, w5 used for ACCAx registers and for MAC/MPY instructions
  ; Initialize registers to '0'

  mov #BUCK_COMP_2P2Z_POSTSCALER, w6
  mov #BUCK_COMP_2P2Z_POSTSHIFT,  w7
  mov #_buckOptions,              w8    ; Points to user options structure
  mov #_buckABCoefficients,       w9
  mov #_buckErrorControlHistory,  w10
  mov #BUCK_COMP_2P2Z_MIN_CLAMP,  w11
  mov #BUCK_COMP_2P2Z_MAX_CLAMP,  w12

  CTXTSWP #0x0  ; Swap back to main register set

  return        ; Exit Alt-WREG1 set-up function

.endif        ; End of buck Alt-W register set-up


.if(BOOST == ENABLED)

     .global _InitAltRegContext2Setup

  _InitAltRegContext2Setup:

  CTXTSWP #0x2   ; Swap to Alternate W-Reg #2

  ; Note: w0 register will be used for compensator control reference parameter

  ; Initialize Alternate Working Registers context #2

  mov #ADCBUF3,                    w1   ; Address of the ADCBUF3 register  (Input)
  mov #CMP2DAC,                    w2   ; Address of the CMP2DAC target register (Output)

  ; w3, w4, w5 used for ACCAx registers and for MAC/MPY instructions
  ; Initialize registers to '0'

  mov #BOOST_COMP_2P2Z_POSTSCALER, w6
  mov #BOOST_COMP_2P2Z_POSTSHIFT,  w7
  mov #_boostOptions,              w8    ; Points to user options structure
  mov #_boostABCoefficients,       w9
  mov #_boostErrorControlHistory,  w10
  mov #BOOST_COMP_2P2Z_MIN_CLAMP,  w11
  mov #BOOST_COMP_2P2Z_MAX_CLAMP,  w12
  
  CTXTSWP #0x0  ; Swap back to main register set

  return        ; Exit Alt-WREG2 set-up function

.endif        ; End of boost Alt-W register set-up

.end

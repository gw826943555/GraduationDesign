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
#include "define.h"

.data

.text


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; ISR:          ADCAN1Interrupt

; Description:	Makes 2P2Z compensator control function call.

; Working Reg:  Only uses Alt W-Reg Context #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

   .global __ADCAN1Interrupt

__ADCAN1Interrupt:

    .if(OPENLOOP == DISABLED)
      mov _buckControlReference, w0
      call _SMPS_Controller2P2ZUpdate_HW_Accel
    .endif

;    mov ADCBUF0, w0
;    mov w0, _buckCurrent
    mov ADCBUF1, w0
    mov w0, _buckVoltage

    bclr  IFS6, #15	  ; Clear ADCAN1 interrupt flag.

	retfie            ; Return from interrupt service routine


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   End of Buck ADCAN1Interrupt ISR
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; ISR:          ADCAN3Interrupt

; Description:	Makes 2P2Z compensator control function call. 

; Working Reg:  Only uses Alt W-Reg Context #2
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



   .global __ADCAN3Interrupt

__ADCAN3Interrupt:

    .if(OPENLOOP == DISABLED)
      mov _boostControlReference, w0
      call _SMPS_Controller2P2ZUpdate_HW_Accel
    .endif

;    mov ADCBUF2, w0
;    mov w0, _boostCurrent
    mov ADCBUF3, w0
    mov w0, _boostVoltage

    bclr  IFS7, #1	  ; Clear ADCAN3 interrupt flag.

    retfie            ; Return from interrupt service routine


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   End of Boost ADCAN3Interrupt ISR
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.end ;; EOF


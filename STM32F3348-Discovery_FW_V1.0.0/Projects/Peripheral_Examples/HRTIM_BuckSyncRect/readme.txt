/**
  @page HRTIM_BuckSyncRect HRTIM BUCK with Synchronous rectification
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    HRTIM_BuckSyncRect/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    8-April-2014
  * @brief   HRTIM BUCK with Synchronous rectification
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
   @endverbatim

@par Example Description

This example shows how to configure the HRTIM to have a buck converter
controlled by a timer unit (Timer A), with the TA1 and TA2 outputs (resp. 
PA8 and PA9).
The duty cycle on TA1 is continuously varied in an interrupt service routine 
generated on repetition event, to mimic a real converter management. .
The converter duty cycle is varied at low frequency from 33% to 66% duty cycle.
The ADC is configured to have conversions triggered in the middle of the ON time 
of converter, on PA1 and PA3 inputs (resp. Vin / Vout inputs of the buck/boost 
converter). The voltages can be monitored in real-time when the debugger is connected.
The FAULT1 input is enabled on PA12 (active low) to demonstrate PWM shut down 
(low level sensitive). When the fault is triggered (causing only TD1 signal to 
stop), the system can be re-armed by pressing the user button.
LEDs are indicating the following:
Blue LED: blinks during normal operation
Red LED: blinks when FAULT is triggered
Orange LED: indicates the occurrence and duration of the PWM refresh ISR



@par Directory contents

  - HRTIM_BuckSyncRect/stm32f30x_conf.h    Library Configuration file
  - HRTIM_BuckSyncRect/stm32f30xx_it.c     Interrupt handlers
  - HRTIM_BuckSyncRect/stm32f30xx_it.h     Interrupt handlers header file
  - HRTIM_BuckSyncRect/main.c              Main program
  - HRTIM_BuckSyncRect/system_stm32f30x.c  STM32f30x system source file


@par Hardware and Software environment

  - This example has been tested with STMicroelectronics STM32F3348-DISCO board 
    and can be easily tailored to any other supported device and development board.
    
  - Connect PA12 to GND to trig a fault on FAULT1 input aiming to shut down PWM.
  
@par How to use it? 

In order to make the program work, you must do the following :
 + EWARM
    - Open the HRTIM_BuckSyncRect.eww workspace 
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)
  
 + MDK-ARM
    - Open the Project.uvproj project
    - Rebuild all files: Project->Rebuild all target files
    - Load project image: Debug->Start/Stop Debug Session
    - Run program: Debug->Run (F5)  

 + TrueSTUDIO
    - Open the TrueSTUDIO toolchain.
    - Click on File->Switch Workspace->Other and browse to TrueSTUDIO workspace 
      directory.
    - Click on File->Import, select General->'Existing Projects into Workspace' 
      and then click "Next". 
    - Browse to the TrueSTUDIO workspace directory and select the project "HRTIM_BuckSyncRect" 
    - Rebuild all project files: Select the project in the "Project explorer" 
      window then click on Project->build project menu.
    - Run program: Select the project in the "Project explorer" window then click 
      Run->Debug (F11) 
          
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

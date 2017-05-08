/**
  @page HRTIM_DualBuck  HRTIM Dual Buck converter example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    HRTIM_DualBuck/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-June-2014
  * @brief   Description of the HRTIM_DualBuck example
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

This example shows how to configure the HRTIM to have 2 buck converters 
controlled by a single timer unit (Timer D), with the TD1 and TD2 outputs (resp. 
PB14 and PB15).
The duty cycle on TD1 is continuously varied in an interrupt service routine 
generated on repetition event, to mimic a real converter management. A low-pass 
filtered signal reflecting the PWM duty cycle can be monitored on TP3.
The ADC is configured to have conversions triggered in the middle of the ON time 
of each converter (non-overlapping PWM signals), on PA4 input.
The FAULT1 input is enabled on PA12 (active low) to demonstrate PWM shut down 
(low level sensitive). When the fault is triggered (causing only TD1 signal to 
stop), the system can be re-armed by pressing the user button.
LEDs are indicating the following:
Blue LED: blinks during normal operation
Red LED: blinks when FAULT is triggered
Orange LED: indicates the occurrence and duration of the PWM refresh ISR



@par Directory contents

  - HRTIM_DualBuck/stm32f30x_conf.h    Library Configuration file
  - HRTIM_DualBuck/stm32f30xx_it.c     Interrupt handlers
  - HRTIM_DualBuck/stm32f30xx_it.h     Interrupt handlers header file
  - HRTIM_DualBuck/main.c              Main program
  - HRTIM_DualBuck/system_stm32f30x.c  STM32f30x system source file


@par Hardware and Software environment

  - This example has been tested with STMicroelectronics STM32F3348-DISCO board 
    and can be easily tailored to any other supported device and development board.
  
  - Connect PA12 to GND to trig a fault on FAULT1 input aiming to shut down PWM.  

@par How to use it? 

In order to make the program work, you must do the following :
 + EWARM
    - Open the HRTIM_DualBuck.eww workspace 
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
    - Browse to the TrueSTUDIO workspace directory and select the project "HRTIM_DualBuck" 
    - Rebuild all project files: Select the project in the "Project explorer" 
      window then click on Project->build project menu.
    - Run program: Select the project in the "Project explorer" window then click 
      Run->Debug (F11) 
          
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

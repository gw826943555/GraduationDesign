/**
  @page EXTI_Example  EXTI example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    EXTI_Example/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-June-2014
  * @brief   Description of the EXTI example
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

This example shows how to configure external interrupt lines.
In this example, 1 EXTI line (EXTI0) when using the STM32F3348-DISCO is configured 
to generate an interrupt on each rising edge. In the interrupt routine leds
connected to a specific GPIO pins is toggled.
In this example :
    - EXTI0 is mapped to PA0. 
    - when rising edge is detected on EXTI0 by pressing User button, LED3, LED4, LED5
      and LED6 toggle.

@par Directory contents 

  - EXTI_Example/stm32f30x_conf.h     Library Configuration file
  - EXTI_Example/stm32f3xx_it.c       Interrupt handlers
  - EXTI_Example/stm32f3xx_it.h       Header for stm32f3xx_it.c
  - EXTI_Example/main.c               Main program
  - EXTI_Example/main.h               Header for main.c
  - EXTI_Example/system_stm32f30x.c   STM32F30x system source file


@par Hardware and Software environment

  - This example runs on STM32F334xx Devices.
  
  - This example has been tested with STMicroelectronics STM32F3348-DISCO (MB1142A) 
    and can be easily tailored to any other supported device and development board.
      
@par How to use it ? 

In order to make the program work, you must do the following :

 + EWARM
    - Open the EXTI_Example.eww workspace 
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
    - Browse to the TrueSTUDIO workspace directory and select the project "EXTI_Example" 
    - Rebuild all project files: Select the project in the "Project explorer" 
      window then click on Project->build project menu.
    - Run program: Select the project in the "Project explorer" window then click 
      Run->Debug (F11) 
          
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

/**
  @page GPIO_IOToggle  GPIO IOToggle example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    GPIO_IOToggle/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-June-2014
  * @brief   Description of the GPIO IOToggle example
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

This example describes how to toggle IO with three different frequencies.
This is done using Delay() function which is implemented based on the SysTick 
end-of-count event. 

When starting program, LED3, LED4, LED5 and LED6 remain toggling with a first
frequency equal to ~10Hz (a delay of 50ms is put). Press the User button, mounted   
on STM32F3348-DISCO, so LEDs toggle with a second frequency equal to ~2.5Hz
(a delay of 200ms is put). Then press again the User button, and LEDs toggle with
~1Hz frequency(a delay of 500ms is put). This is done in an infinite loop."

@par Directory contents

  - GPIO_IOToggle/stm32f30x_conf.h    Library Configuration file
  - GPIO_IOToggle/stm32f3xx_it.c      Interrupt handlers
  - GPIO_IOToggle/stm32f3xx_it.h      Interrupt handlers header file
  - GPIO_IOToggle/main.c              Main program
  - GPIO_IOToggle/system_stm32f30x.c  STM32F33xx system source file


@par Hardware and Software environment

  - This example has been tested with STMicroelectronics STM32F3348-DISCO board (MB1142A) 
    and can be easily tailored to any other supported device and development board.
 - This example runs on STM32F334xx Devices.
    

@par How to use it? 

In order to make the program work, you must do the following :
 + EWARM
    - Open the GPIO_IOToggle.eww workspace 
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
    - Browse to the TrueSTUDIO workspace directory and select the project "GPIO_IOToggle" 
    - Rebuild all project files: Select the project in the "Project explorer" 
      window then click on Project->build project menu.
    - Run program: Select the project in the "Project explorer" window then click 
      Run->Debug (F11) 
          
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

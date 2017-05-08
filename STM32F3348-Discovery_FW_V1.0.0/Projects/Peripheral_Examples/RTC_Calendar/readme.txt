/**
  @page RTC_Calendar RTC Hardware RTC Calendar Description
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    RTC_Calendar/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-June-2014
  * @brief   Description of the RTC Hardware RTC Calendar example.
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

This example demonstrates how to setup the RTC peripheral, in terms of prescaler 
and interrupts, to be used to keep date, time and to generate alarm interrupt. 

When an RTC Alarm A event occurs the RTC Alarm interrupt is generated each 1s.
At each Alarm interrupt, one LED is toggled.

To show time and date, put variables showtime and showdate in Watch window.

@par Directory contents 

  - RTC_Calendar/stm32f30x_conf.h     Library Configuration file
  - RTC_Calendar/stm32f3xx_it.c       Interrupt handlers
  - RTC_Calendar/stm32f3xx_it.h       Header for stm32f3xx_it.c
  - RTC_Calendar/main.c               Main program
  - RTC_Calendar/main.h               Header for main.c
  - RTC_Calendar/system_stm32f30x.c   STM32F30x system source file


@par Hardware and Software environment

  - This example has been tested with STMicroelectronics STM32F3348-DISCO board (MB1142A) 
    and can be easily tailored to any other supported device and development board.
  - This example runs on STM32F334xx Devices.
    

@par How to use it? 

In order to make the program work, you must do the following :
 + EWARM
    - Open the RTC_Calendar.eww workspace 
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
    - Browse to the TrueSTUDIO workspace directory and select the project "RTC_Calendar" 
    - Rebuild all project files: Select the project in the "Project explorer" 
      window then click on Project->build project menu.
    - Run program: Select the project in the "Project explorer" window then click 
      Run->Debug (F11) 
          
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

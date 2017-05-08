/**
  @page PWR_Stop PWR STOP example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    PWR_Stop/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-June-2014
  * @brief   Description of the PWR STOP example.
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

This example shows how to enter the system to STOP mode and wake-up using EXTI
Line interrupts. The EXTI Line sources are PA0 and RTC WakeUp.

The EXTI line0 is configured to generate interrupt on falling edge.
The EXTI line20(RTC WakeUp) is configured to generate interrupt on rising edge.

The system enters and exits STOP mode as follow:
After system start-up, the RTC is configured to generate a WakeUp event then the 
system enters STOP mode. To wake-up from STOP mode you have to apply a falling
edge on EXTI line0, otherwise the  RTC WakeUp will wake-up the system within 5 
seconds. After exit from STOP, the system clock is reconfigured to its previous 
state (as HSI and PLL are disabled in STOP mode).
Then, after a delay the system will enter again in STOP mode and exit in the way
described above. This behavior is repeated in an infinite loop.

Three leds are used to monitor the system state as follow:
 - LED3 ON: system in RUN mode
 - LED3, LED4 and LED5 OFF: system in STOP mode
 - LED5 ON if EXTI Line0 is used to exit from STOP
 - LED4 ON if EXTI line17(RTC Alarm) is used to exit from STOP 
 
@note To measure the current consumption in STOP mode, please refer to 
      @subpage PWR_CurrentConsumption example.
      
@note When using the small packages (48 and 64 pin packages), the GPIO pins which 
      are not present on these packages, must not be configured in analog mode.

@par Directory contents 

  - PWR_Stop/stm32f30x_conf.h     Library Configuration file
  - PWR_Stop/stm32f30x_it.c       Interrupt handlers
  - PWR_Stop/stm32f30x_it.h       Header for stm32f30x_it.c
  - PWR_Stop/main.c               Main program
  - PWR_Stop/main.h               Header for main.c
  - PWR_Stop/system_stm32f30x.c   STM32F30x system source file


@par Hardware and Software environment

  - This example has been tested with STMicroelectronics STM32F3348-DISCO board (MB1142A) 
    and can be easily tailored to any other supported device and development board.
 - This example runs on STM32F334xx Devices.
    

@par How to use it? 

In order to make the program work, you must do the following :
 + EWARM
    - Open the PWR_Stop.eww workspace 
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
    - Browse to the TrueSTUDIO workspace directory and select the project "PWR_Stop" 
    - Rebuild all project files: Select the project in the "Project explorer" 
      window then click on Project->build project menu.
    - Run program: Select the project in the "Project explorer" window then click 
      Run->Debug (F11) 
          
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

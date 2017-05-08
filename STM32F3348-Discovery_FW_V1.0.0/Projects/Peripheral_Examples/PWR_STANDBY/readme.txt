/**
  @page PWR_Standby PWR Standby example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    PWR_Standby/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-June-2014
  * @brief   Description of the PWR Standby example.
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

This example shows how to enter the system to STANDBY mode and wake-up from this
mode using RTC WakeUp.

In the associated software, the system clock is set to 72 MHz, the SysTick is programmed
to generate an interrupt each 250 ms. In the SysTick interrupt handler, the LED3 is
toggled, this is used to indicate whether the MCU is in STANDBY or RUN mode.

When a falling edge is detected on the PA0(pressing on USER button), the RTC is 
configured to generate a WakeUp event in 3 seconds then the system enters STANDBY 
mode causing the LED3 to stop toggling. 
An external RESET will wake-up the system from STANDBY. If within 3 seconds an 
external RESET is not generated, the RTC will wake-up the system. 

After wake-up from STANDBY mode, program execution restarts in the same way as after
a RESET, the LED3 is toggling again,the RTC configuration(clock source, enable, prescaler,...) 
is kept.
As result there is no need to configure the RTC.

Led LED3 is used to monitor the system state as following:
 - LED3 toggling: system in RUN mode
 - LED3 off : system in STANDBY mode

To cope with the LSI clock inaccuracy, routine of LSI measurement is implemented as follow:
 - Configure the TIM16 to remap internally the TIM16 Channel 1 Input Capture to 
   the LSI clock output.
 - Enable the TIM16 Input Capture interrupt: after one cycle of LSI clock, the
   period value is stored in a variable and compared to the HCLK clock to get
   its real value.
 - The RTC prescaler is adjusted with this LSI frequency value so that the RTC
   CK_SPRE value become more accurate.
   
@note To measure the current consumption in STANDBY mode, please refer to 
      @subpage PWR_CurrentConsumption example.

@par Directory contents 

  - PWR_Standby/stm32f30x_conf.h     Library Configuration file
  - PWR_Standby/stm32f3xx_it.c       Interrupt handlers
  - PWR_Standby/stm32f3xx_it.h       Header for stm32f3xx_it.c
  - PWR_Standby/main.c               Main program
  - PWR_Standby/main.h               Header for main.c
  - PWR_Standby/system_stm32f30x.c   STM32F30x system source file


@par Hardware and Software environment

  - This example has been tested with STMicroelectronics STM32F3348-DISCO board (MB1142A) 
    and can be easily tailored to any other supported device and development board.
 - This example runs on STM32F334xx Devices.
    

@par How to use it? 

In order to make the program work, you must do the following :
 + EWARM
    - Open the PWR_Standby.eww workspace 
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
    - Browse to the TrueSTUDIO workspace directory and select the project "PWR_Standby" 
    - Rebuild all project files: Select the project in the "Project explorer" 
      window then click on Project->build project menu.
    - Run program: Select the project in the "Project explorer" window then click 
      Run->Debug (F11) 
          
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

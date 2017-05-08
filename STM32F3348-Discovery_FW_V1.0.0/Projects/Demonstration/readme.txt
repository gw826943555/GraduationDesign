/**
  @page STM32F3348-Discovery_Demo  Demonstration 
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    Demonstration/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-June-2014
  * @brief   Description of the STM32F3348-Discovery Demonstration
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

@par Demo Description

The provided demonstration firmware helps you to discover the high brightness
LED dimming feature embedded within the STM32F3348-DISCO board.

There are several modes available driving the high brightness LED:
 - Automatic dimmer: This mode scans the entire brightness range.
 - Flash mode: The high brightness LED is turned ON with a 10Hz frequency
 - Manual dimmer: The brightness can be adjusted manually by maintaining B1 pushed.
 - Mode OFF : the high brightness LED is not controlled.


As soon as the STM32F3348-DISCO board is power supplied, all signals LEDs (LD3 to LD6) are
lit one by one and the high brightness LED is not controlled (Mode OFF).
As soon as the user button B1 is pressed, the application enters automatic
dimmer mode that consists to scan the entire brightness range, The red LED LD3 
is ON when the brightness increases whereas the blue LED LD6 is ON when the
brightness decreases.
If the user button B1 is pressed again, then the application enters flash mode.
Leds LD4 and LD5 (orange and green) are toggling at the flash rate. The high
brightness LED is switched ON and OFF at the frequency of 10Hz and the brightness
is set at its maximum.
By pressing again B1, the application comes back to the OFF state with the high
brightness LED OFF and LD3 to LD6 periodically lit.

At any time, the user can switch the application into manual dimmer where the
LED brightness can be set manually by maintaining the user button pressed for more
than one second. The LED brightness first starts to increase from zero to maximum
when LD3 (red) is turned ON. When the brightness reaches the maximum value then
LD3 toggles to show maximum brightness achieved. If a second and long push onto the
user button is performed, then the manual dimmer is active for decreasing the LED
brightness and LD6 (blue) is turned ON. When the brightness reaches the minimum
value then LD6 toggles to show minimum brightness achieved. To exit the manual
dimmer, shortly press the user button and the application returns to high brightness LED
OFF Mode.
for more details on High brightness LED dimming using the STM32F3348-Discovery 
please refer to AN4885. 

@par Directory contents

  - Demonstration/stm32f30x_conf.h    Library Configuration file
  - Demonstration/stm32f3xx_it.c      Interrupt handlers
  - Demonstration/stm32f3xx_it.h      Interrupt handlers header file
  - Demonstration/main.c              Main program
  - Demonstration/system_stm32f30x.c  STM32f30x system source file


@par Hardware and Software environment

  - This Demonstration has been tested with STMicroelectronics STM32F3348-DISCO board 
    and can be easily tailored to any other supported device and development board.
  - This Demonstration runs on STM32F334x8 Devices.  

@par How to use it? 

In order to make the program work, you must do the following :
 + EWARM
    - Open the STM32F3348-Discovery_Demo.eww workspace 
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
    - Browse to the TrueSTUDIO workspace directory and select the project "Template" 
    - Rebuild all project files: Select the project in the "Project explorer" 
      window then click on Project->build project menu.
    - Run program: Select the project in the "Project explorer" window then click 
      Run->Debug (F11) 
          
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

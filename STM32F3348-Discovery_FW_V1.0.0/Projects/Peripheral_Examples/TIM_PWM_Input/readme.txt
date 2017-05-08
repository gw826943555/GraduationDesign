/**
  @page TIM_PWM_Input TIM PWM Input Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    TIM_PWM_Input/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-June-2014
  * @brief   Description of the TIM PWM_Input example.
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

This example shows how to use the TIM peripheral to measure the frequency and 
duty cycle of an external signal.

The TIMxCLK frequency is set to SystemCoreClock(Hz), SystemCoreClock is set to 
72 MHz for STM32F33xx Devices.

TIM2 is configured in PWM Input Mode: the external signal is connected to 
TIM2 Channel2 used as input pin.
To measure the frequency and the duty cycle we use the TIM2 CC2 interrupt request,
so In the TIM2_IRQHandler routine, the frequency and the duty cycle of the external 
signal are computed. 
The "Frequency" variable contains the external signal frequency:
TIM2 counter clock = SystemCoreClock,
Frequency = TIM2 counter clock / TIM2_CCR2 in Hz, 
The "DutyCycle" variable contains the external signal duty cycle:
DutyCycle = (TIM2_CCR1*100)/(TIM2_CCR2) in %.

The minimum frequency value to measure is 915 Hz (TIM2 counter clock / CCR MAX).
  
@par Directory contents 

  - TIM_PWM_Input/stm32f30x_conf.h     Library Configuration file
  - TIM_PWM_Input/stm32f3xx_it.c       Interrupt handlers
  - TIM_PWM_Input/stm32f3xx_it.h       Header for stm32f3xx_it.c
  - TIM_PWM_Input/main.c               Main program
  - TIM_PWM_Input/main.h               Header for main.c
  - TIM_PWM_Input/system_stm32f30x.c   STM32F30x system source file


@par Hardware and Software environment

  - This example has been tested with STMicroelectronics STM32F3348-DISCO board (MB1142A) 
    and can be easily tailored to any other supported device and development board.
 - This example runs on STM32F334xx Devices.
    
  - STM32F3348-DISCO Set-up
    - Connect the external signal to measure to the TIM2 CH2 pin (PA.01).
       
@par How to use it? 

In order to make the program work, you must do the following :
 + EWARM
    - Open the TIM_PWM_Input.eww workspace 
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
    - Browse to the TrueSTUDIO workspace directory and select the project "TIM_PWM_Input" 
    - Rebuild all project files: Select the project in the "Project explorer" 
      window then click on Project->build project menu.
    - Run program: Select the project in the "Project explorer" window then click 
      Run->Debug (F11) 
          
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

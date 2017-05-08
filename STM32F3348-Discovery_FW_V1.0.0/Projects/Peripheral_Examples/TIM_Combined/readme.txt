/**
  @page TIM_Combined TIM Combined Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    TIM_Combined/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-June-2014
  * @brief   TIM Combined Example Description.
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

This example shows how to configure the TIM1 peripheral to generate 3 PWM combined 
signals with TIM1 Channel5.

TIM1 input clock (TIM1CLK) is set to APB2 clock (PCLK2)=> TIM1CLK = PCLK2 = SystemCoreClock
TIM1CLK = SystemCoreClock, Prescaler = 0, TIM1 counter clock = SystemCoreClock
SystemCoreClock is set to 72 MHz for STM32F30x devices.

The objective is to generate 3 combined PWM signal at 8.78 KHz (in center aligned mode):
    - TIM1_Period = (SystemCoreClock / (8.78*2)) - 1
 The channel 1  duty cycle is set to 50%
 The channel 2  duty cycle is set to 37.5%
 The channel 3  duty cycle is set to 25%
   
The Timer pulse is calculated as follows:
  - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100
  
The channel 5  is used in PWM2 mode with duty cycle set to 6.22%

The 3 resulting signals are made of an AND logical combination of two reference PWMs:
  - Channel 1 and Channel 5
	- Channel 2 and Channel 5
	- Channel 3 and Channel 5

The TIM1 waveform can be displayed using an oscilloscope.
  
@par Directory contents 

  - TIM_Combined/stm32f30x_conf.h     Library Configuration file
  - TIM_Combined/stm32f3xx_it.c       Interrupt handlers
  - TIM_Combined/stm32f3xx_it.h       Header for stm32f3xx_it.c
  - TIM_Combined/main.c               Main program
  - TIM_Combined/main.h               Header for main.c
  - TIM_Combined/system_stm32f30x.c   STM32F30x system source file


@par Hardware and Software environment

  - This example has been tested with STMicroelectronics STM32F3348-DISCO board (MB1142A) 
    and can be easily tailored to any other supported device and development board.
 - This example runs on STM32F334xx Devices.
    
  - STM32F3348-DISCO Set-up
    - Connect the following pins to an oscilloscope to monitor the different 
      waveforms:
       - PA.08 (TIM1_CH1)
       - PA.09 (TIM2_CH2)
       - PA.10 (TIM2_CH3)
       
@par How to use it? 

In order to make the program work, you must do the following :
 + EWARM
    - Open the TIM_Combined.eww workspace 
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
    - Browse to the TrueSTUDIO workspace directory and select the project "TIM_Combined" 
    - Rebuild all project files: Select the project in the "Project explorer" 
      window then click on Project->build project menu.
    - Run program: Select the project in the "Project explorer" window then click 
      Run->Debug (F11) 
          
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

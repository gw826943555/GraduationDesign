/**
  @page DMA_RAM_DAC DMA RAM to DAC example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    DMA_RAM_DAC/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-June-2014
  * @brief   Description of the DMA RAM to DAC example.
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

This example provides a description of how to use a DMA channel to transfer 
data buffer from RAM memory to DAC.

DMA1 channel3 is configured to transfer continuously, word by word, a 32-word buffer 
to the dual DAC register DAC_DHR12RD. Both DAC channels conversions are configured 
to be triggered by TIM2 TRGO triggers and without noise/triangle wave generation.
12bit right data alignment is selected since we choose to access DAC_DHR12RD register.

@par Directory contents 

  - DMA_RAM_DAC/stm32f30x_conf.h     Library Configuration file
  - DMA_RAM_DAC/stm32f3xx_it.c       Interrupt handlers
  - DMA_RAM_DAC/stm32f3xx_it.h       Header for stm32f3xx_it.c
  - DMA_RAM_DAC/main.c               Main program
  - DMA_RAM_DAC/main.h               Header for main.c
  - DMA_RAM_DAC/system_stm32f30x.c   STM32F33xx system source file
 
@par Hardware and Software environment

  - This example has been tested with STMicroelectronics STM32F3348-DISCO board (MB1142A) 
    and can be easily tailored to any other supported device and development board.
 - This example runs on STM32F334xx Devices.
    
  - STM32F3348-DISCO Set-up
    - Connect the oscilloscope to PA.04 and PA.05.
            
@par How to use it? 

In order to make the program work, you must do the following :
 + EWARM
    - Open the DMA_RAM_DAC.eww workspace 
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
    - Browse to the TrueSTUDIO workspace directory and select the project "DMA_RAM_DAC" 
    - Rebuild all project files: Select the project in the "Project explorer" 
      window then click on Project->build project menu.
    - Run program: Select the project in the "Project explorer" window then click 
      Run->Debug (F11) 
          
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

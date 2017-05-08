/**
  @page FLASH_RAM DMA FLASH to RAM example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    DMA_FLASH_RAM/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-June-2014
  * @brief   Description of the DMA FLASH to RAM example.
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

This example provides a description on how to use a DMA channel to transfer 
a word data buffer from FLASH memory to embedded SRAM memory.

DMA1 Channel1 is configured to transfer the contents of a 32-word data buffer
stored in Flash memory to the reception buffer declared in RAM.

The start of transfer is triggered by software. DMA1 Channel1 memory-to-memory
transfer is enabled. Source and destination addresses incrementing is also enabled.
The transfer is started by setting the Channel enable bit for DMA1 Channel1.
At the end of the transfer, a Transfer Complete interrupt is generated since it
is enabled. Once interrupt is generated, the remaining data to be transferred is
read which must be equal to 0. The Transfer Complete Interrupt pending bit is
then cleared. A comparison between the source and destination buffers is done to
check that all data have been correctly transferred.
If destination and source buffers are the same, LED5 (green) is On. Otherwise,
LED3(red) is On.

@par Directory contents 

  - DMA_FLASH_RAM/stm32f30x_conf.h     Library Configuration file
  - DMA_FLASH_RAM/stm32f30x_it.c       Interrupt handlers
  - DMA_FLASH_RAM/stm32f30x_it.h       Header for stm32f30x_it.c
  - DMA_FLASH_RAM/main.c               Main program
  - DMA_FLASH_RAM/main.h               Header for main.c
  - DMA_FLASH_RAM/system_stm32f30x.c   STM32F30x system source file
 

@par Hardware and Software environment

  - This example has been tested with STMicroelectronics STM32F3348-DISCO board (MB1142A) 
    and can be easily tailored to any other supported device and development board.
 - This example runs on STM32F334xx Devices.
        
@par How to use it? 

In order to make the program work, you must do the following :
 + EWARM
    - Open the DMA_FLASH_RAM.eww workspace 
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
    - Browse to the TrueSTUDIO workspace directory and select the project "DMA_FLASH_RAM" 
    - Rebuild all project files: Select the project in the "Project explorer" 
      window then click on Project->build project menu.
    - Run program: Select the project in the "Project explorer" window then click 
      Run->Debug (F11) 
          
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

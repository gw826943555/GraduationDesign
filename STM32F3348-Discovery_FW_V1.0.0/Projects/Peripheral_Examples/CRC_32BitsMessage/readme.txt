/**
  @page CRC_32BitsCRCMessage Compute the 32-bit CRC value of a message
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    CRC_32BitsCRCMessage/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-June-2014
  * @brief   Description of the 32-bit CRC value of a message example.
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

This example aims to show how to use the CRC peripheral in order to compute
32-bit CRC checksum of a message.
The CRC peripheral is configured to use the 32-bit CRC polynomial
X32 + X26 + X23 + X22 + X16 + X12 + X11 + X10 +X8 + X7 + X5 + X4 + X2+ X +1 
with the initialization value is set to 0.
The message is declared as an array and labeled "CRCBuffer".
Once the CRC value is computed, the computed CRC value is compared to the expected
one. In case of match the green led LED5 is turned on. Otherwise the led LED3 is turned on.


@par Directory contents 

  - CRC_32BitsCRCMessage/stm32f30x_conf.h    Library Configuration file
  - CRC_32BitsCRCMessage/stm32f3xx_it.c      Interrupt handlers
  - CRC_32BitsCRCMessage/stm32f3xx_it.h      Interrupt handlers header file
  - CRC_32BitsCRCMessage/main.c              Main program
  - CRC_32BitsCRCMessage/system_stm32f30x.c  STM32F30x system source file


@par Hardware and Software environment

  - This example has been tested with STMicroelectronics STM32F3348-DISCO board (MB1142A) 
    and can be easily tailored to any other supported device and development board.
  - This example runs on STM32F334xx Devices.
    

@par How to use it? 

In order to make the program work, you must do the following :
 + EWARM
    - Open the CRC_32BitsCRCMessage.eww workspace 
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
    - Browse to the TrueSTUDIO workspace directory and select the project "CRC_32BitsCRCMessage" 
    - Rebuild all project files: Select the project in the "Project explorer" 
      window then click on Project->build project menu.
    - Run program: Select the project in the "Project explorer" window then click 
      Run->Debug (F11) 
          
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

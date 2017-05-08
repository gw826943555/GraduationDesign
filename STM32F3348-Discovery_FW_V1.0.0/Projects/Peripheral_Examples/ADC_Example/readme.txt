/**
  @page ADC_Example ADC Basic Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    ADC_Example/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-June-2014
  * @brief   Description of ADC Basic Example
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

This example describes how to use the ADC1 to convert continuously voltage applied
to a given analog input channel.
Detailed steps of ADC configuration are provided starting from GPIO configuration
to the analog channel configuration without forgetting the ADC calibration procedure.  
In this example the ADC1 Channel2(PA1) is used as directly connected to the power supply.
The converted voltage is stored in the ADC1ConvertedVoltage variable.

@par Directory contents 

  - ADC_Example/stm32f30x_conf.h     Library Configuration file
  - ADC_Example/stm32f30x_it.c       Interrupt handlers
  - ADC_Example/stm32f30x_it.h       Header for stm32f30x_it.c
  - ADC_Example/main.c               Main program
  - ADC_Example/main.h               Header for main.c
  - ADC_Example/system_stm32f30x.c   STM32F30x system source file


@par Hardware and Software environment

  - This example has been tested with STMicroelectronics STM32F3348-DISCO board (MB1142A) 
    and can be easily tailored to any other supported device and development board.
 - This example runs on STM32F334xx Devices.
    
  - STM32F3348-DISCO Set-up
    - Connect the external signal(ranges from 0 to 3.3V) to the ADC1 pin (PA.01) 
      to be converted.
    
@par How to use it? 

In order to make the program work, you must do the following :
 + EWARM
    - Open the ADC_Example.eww workspace 
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
    - Browse to the TrueSTUDIO workspace directory and select the project "ADC_Example" 
    - Rebuild all project files: Select the project in the "Project explorer" 
      window then click on Project->build project menu.
    - Run program: Select the project in the "Project explorer" window then click 
      Run->Debug (F11) 
          
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

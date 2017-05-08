/**
  @page OPAMP_PGA OPMAP2 in Programmable Gain Amplifier example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    OPAMP_PGA/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-June-2014
  * @brief   Description of OPMAP2 in Programmable Gain Amplifier example.
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

This example shows how to configure OPAMP2 peripheral to amplify external sine
wave signal applied on OPAMP2 non inverting input using the built-in PGA.
OPAMP2 is configured as following:
   - PGA mode enabled with gain set to 2
   - Non Inverting input is connected to PA7
   - Output is available on PA6
The amplified signal on OPAMP2 OUT is continuously converted by ADC2 (Channel3)
directly connected to the OPAMP2 output.
The converted voltage is stored in the ADC2ConvertedVoltage variable.
ADC2ConvertedVoltage = OPAMP2 gain x Voltage applied on PA7. The value of this
variable can be viewed in live watch window.
 
@par Directory contents 

  - OPAMP_PGA/stm32f30x_conf.h     Library Configuration file
  - OPAMP_PGA/stm32f3xx_it.c       Interrupt handlers
  - OPAMP_PGA/stm32f3xx_it.h       Header for stm32f3xx_it.c
  - OPAMP_PGA/main.c               Main program
  - OPAMP_PGA/main.h               Header for main.c
  - OPAMP_PGA/system_stm32f30x.c   STM32F30x system source file


@par Hardware and Software environment

  - This example has been tested with STMicroelectronics STM32F3348-DISCO board 
    and can be easily tailored to any other supported device and development board.
    
  - STM32F3348-DISCO Set-up : Connect an external sine wave signal(ranges from 0 to 1.65V)
    to the OPAMP2 non inverting pin (PA.07) to be converted.
    
@par How to use it? 

In order to make the program work, you must do the following :
 + EWARM
    - Open the OPAMP_PGA.eww workspace 
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
    - Browse to the TrueSTUDIO workspace directory and select the project "OPAMP_PGA" 
    - Rebuild all project files: Select the project in the "Project explorer" 
      window then click on Project->build project menu.
    - Run program: Select the project in the "Project explorer" window then click 
      Run->Debug (F11) 
          
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

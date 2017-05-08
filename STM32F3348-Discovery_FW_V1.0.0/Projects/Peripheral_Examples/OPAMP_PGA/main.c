/**
  ******************************************************************************
  * @file    OPAMP_PGA/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-June-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
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
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F3348_DISCOVERY_Examples
  * @{
  */

/** @addtogroup OPAMP_PGA
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay = 0;
__IO uint16_t  ADC2ConvertedValue = 0, ADC2ConvertedVoltage = 0;
uint16_t  calibration_value = 0;
/* Private function prototypes -----------------------------------------------*/
static void ADC_Config(void);
static void OPAMP_Config(void);

/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
 
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       files (startup_stm32f334x8.s) before to branch to application main. 
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f30x.c file
     */ 
 
  /* SysTick end of count event each 1µs */
  SysTick_Config( SystemCoreClock / 1000000);
  
  /* Configure OPAMP2 */
  OPAMP_Config();
  
  /* ADC2 configuration *******************************************************/
  /*  - Enable peripheral clocks                                              */
  /*  - Configure ADC2 Channel3 pin as analog input                           */
  /*  - Configure ADC2 Channel3                                               */ 
  ADC_Config();
  
  /* Start ADC2 Software Conversion */ 
  ADC_StartConversion(ADC2);
  
  /* Infinite loop */
  while (1)
  {
    /* Test EOC flag */
    while(ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC) == RESET);
    
    /* Get ADC2 converted data */
    ADC2ConvertedValue = ADC_GetConversionValue(ADC2);
    
    /* Compute the voltage */
    ADC2ConvertedVoltage = (ADC2ConvertedValue *3300)/0xFFF;    
  }
}

/**
  * @brief  ADC2 channel3 configuration
  * @param  None
  * @retval None
  */
static void ADC_Config(void)
{
  ADC_InitTypeDef       ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  GPIO_InitTypeDef      GPIO_InitStructure;
  
  /* ADC Channel configuration */
  /* Configure the ADC clock */
  RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div2);
  
  /* Enable ADC2 clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);
  
  /* GPIOC Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  
  /* Configure ADC2 Channel3 as analog input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  ADC_StructInit(&ADC_InitStructure);
  
  /* Calibration procedure */  
  ADC_VoltageRegulatorCmd(ADC2, ENABLE);
  
  /* Insert delay equal to 10 µs */
  Delay(10);
  
  ADC_SelectCalibrationMode(ADC2, ADC_CalibrationMode_Single);
  ADC_StartCalibration(ADC2);
  
  while(ADC_GetCalibrationStatus(ADC2) != RESET )
  {
  }
  calibration_value = ADC_GetCalibrationValue(ADC2);
  
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;                                                                    
  ADC_CommonInitStructure.ADC_Clock = ADC_Clock_AsynClkMode;                    
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;             
  ADC_CommonInitStructure.ADC_DMAMode = ADC_DMAMode_OneShot;                  
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = 0;          
  ADC_CommonInit(ADC2, &ADC_CommonInitStructure);
  
  ADC_InitStructure.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Enable;
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b; 
  ADC_InitStructure.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_0;         
  ADC_InitStructure.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_OverrunMode = ADC_OverrunMode_Disable;   
  ADC_InitStructure.ADC_AutoInjMode = ADC_AutoInjec_Disable;  
  ADC_InitStructure.ADC_NbrOfRegChannel = 1;
  ADC_Init(ADC2, &ADC_InitStructure);
  
  /* ADC2 regular channel3 configuration */ 
  ADC_RegularChannelConfig(ADC2, ADC_Channel_3, 1, ADC_SampleTime_7Cycles5);
  
  /* Enable ADC2 */
  ADC_Cmd(ADC2, ENABLE);
  
  /* wait for ADRDY */
  while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_RDY))
  {
  }
}

/**
  * @brief  Configures OPAMP2 in PGA mode
  * @param  None
  * @retval None
  */
static void OPAMP_Config(void)
{
  OPAMP_InitTypeDef       OPAMP_InitStructure;
  GPIO_InitTypeDef        GPIO_InitStructure;
  
  /* Configure PA7 analog mode: It is used as OPAMP2 non inverting input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* OPAMP2 Peripheral clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* OPAMP2 config: Select PA7 as non inverting input */
  OPAMP_InitStructure.OPAMP_NonInvertingInput = OPAMP_NonInvertingInput_IO4;
  OPAMP_InitStructure.OPAMP_InvertingInput =  OPAMP_InvertingInput_PGA;
  OPAMP_Init(OPAMP_Selection_OPAMP2, &OPAMP_InitStructure);
  
  /* Configure OPAMP2 in PGA mode with gain set to 2 */
  OPAMP_PGAConfig(OPAMP_Selection_OPAMP2, OPAMP_OPAMP_PGAGain_2, OPAMP_PGAConnect_No);
  
  /* Enable OPAMP2 */
  OPAMP_Cmd(OPAMP_Selection_OPAMP2, ENABLE);
}

/**
* @brief  Inserts a delay time.
* @param  nTime: specifies the delay time length, in 1 ms.
* @retval None
*/
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;
  
  while(TimingDelay != 0);
}

/**
* @brief  Decrements the TimingDelay variable.
* @param  None
* @retval None
*/
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    main.c 
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
#include "stm32f3348_discovery.h"

/** @addtogroup HRTIM_DualBuck
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;
RCC_ClocksTypeDef RCC_Clocks;

/* Private function prototypes -----------------------------------------------*/
static void GPIO_HRTIM_inputs_Config(void);
static void GPIO_HRTIM_outputs_Config(void);
static void HRTIM_Config(void);
static void ADC_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
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
  
  /* SysTick end of count event each 1ms */
  SysTick_Config(SystemCoreClock / 1000);
  
  /* Initialize STM32F3348-DISCO LEDs */
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED6);
  
  /* Initialize User_Button on STM32F3348-DISCO */
  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);   
  
  /* Initialize ADC to be triggered by the HRTIM */
  ADC_Config();
  
  /* Initialize HRTIM and related I/Os */
  GPIO_HRTIM_inputs_Config();
  HRTIM_Config();
  GPIO_HRTIM_outputs_Config();
  
  
  /* Infinite loop */
  while (1)
  {
    /* ---------------- */
    /* Fault management */
    /* ---------------- */
    while (HRTIM_GetCommonFlagStatus(HRTIM1, HRTIM_IT_FLT1) == SET)
    {
      /* LED3 is flashing in case of fault */
      STM_EVAL_LEDOn(LED3);
      Delay(20);
      STM_EVAL_LEDOff(LED3);
      Delay(80);
      
      /* Re-arm HRTIM TD1 output if "User" push button is pressed*/
      if((STM_EVAL_PBGetState(BUTTON_USER) == SET))
      {
        HRTIM_ClearCommonITPendingBit(HRTIM1, HRTIM_IT_FLT1);
        HRTIM_WaveformOutputStart(HRTIM1, HRTIM_OUTPUT_TD1);
      }
    }
    
    /* ---------------- */
    /* Normal operation */
    /* ---------------- */
    /* LED6 toggling to show MCU activity */
    STM_EVAL_LEDToggle(LED6);
    Delay(400);
  }      
  
}


/**
  * @brief  Configure GPIO outputs for the HRTIM
  * @param  None
  * @retval None
  */
static void GPIO_HRTIM_outputs_Config(void)
{
  static GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE);
  
  /* Configure HRTIM output: TD1 (PB14) */
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  /* Alternate function configuration : HRTIM_TD1 / PB14 */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_13);
  
  /* Configure HRTIM output: TD2 (PB15) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  /* Alternate function configuration : HRTIM_TD2 / PB15 */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_13);
}


/**
  * @brief  Configure GPIO inputs for the HRTIM
  * @param  None
  * @retval None
  */
static void GPIO_HRTIM_inputs_Config(void)
{
  static GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  
  /* Configure HRTIM input: FAULT1 (PA12) */
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Alternate function configuration : FAULT1 / PA12 */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_13);
}

/**
  * @brief  Configure ADC for being used with HRTIM
  * @param  None
  * @retval None
  */
static void ADC_Config(void)
{
  ADC_InitTypeDef       ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  GPIO_InitTypeDef      GPIO_InitStructure;
  ADC_InjectedInitTypeDef ADC_InjectedInitStruct;
  
  
  /* ADC Channel configuration */
  /* Configure the ADC clock */
  RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div1);
  
  /* Enable ADC1 clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);
  
  /* GPIOA Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  
  /* Configure PA4 (ADC2 Channel1) as analog input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Calibration procedure */  
  ADC_VoltageRegulatorCmd(ADC2, ENABLE);
  
  /* Insert delay equal to 1ms (can be reduced down to 10µs) */
  Delay(1);
  
  ADC_SelectCalibrationMode(ADC2, ADC_CalibrationMode_Single);
  ADC_StartCalibration(ADC2);
  
  while(ADC_GetCalibrationStatus(ADC2) != RESET );
  
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;                                                                    
  ADC_CommonInitStructure.ADC_Clock = ADC_Clock_AsynClkMode;                    
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;             
  ADC_CommonInitStructure.ADC_DMAMode = ADC_DMAMode_OneShot;                  
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = 0;          
  ADC_CommonInit(ADC2, &ADC_CommonInitStructure);
  
  ADC_InitStructure.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Disable;
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b; 
  ADC_InitStructure.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_0;         
  ADC_InitStructure.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_OverrunMode = ADC_OverrunMode_Disable;   
  ADC_InitStructure.ADC_AutoInjMode = ADC_AutoInjec_Disable;  
  ADC_InitStructure.ADC_NbrOfRegChannel = 1;
  ADC_Init(ADC2, &ADC_InitStructure);
  
  ADC_InjectedInitStruct.ADC_ExternalTrigInjecConvEvent = ADC_ExternalTrigInjecConvEvent_9;
  ADC_InjectedInitStruct.ADC_ExternalTrigInjecEventEdge = ADC_ExternalTrigInjecEventEdge_RisingEdge;
  ADC_InjectedInitStruct.ADC_InjecSequence1 = ADC_InjectedChannel_1; /* corresponds to PA4 */
  ADC_InjectedInitStruct.ADC_InjecSequence2 = ADC_InjectedChannel_1; /* corresponds to PA4 */
  ADC_InjectedInitStruct.ADC_NbrOfInjecChannel = 2;
  ADC_InjectedInit(ADC2, &ADC_InjectedInitStruct);
  
  ADC_InjectedDiscModeCmd(ADC2, ENABLE);
  
  /* ADC2 channel1 configuration */ 
  ADC_InjectedChannelSampleTimeConfig(ADC2, ADC_Channel_1, ADC_SampleTime_1Cycles5);
  
  /* Enable ADC2 */
  ADC_Cmd(ADC2, ENABLE);
  
  /* wait for ADRDY */
  while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_RDY));   
  
  /* Start ADC2 Injected Conversions */ 
  ADC_StartInjectedConversion(ADC2);
  
}

/**
  * @brief  HRTIM configuration
  * @param  None
  * @retval None
  */
static void HRTIM_Config(void)
{
  HRTIM_OutputCfgTypeDef HRTIM_TIM_OutputStructure;
  HRTIM_BaseInitTypeDef HRTIM_BaseInitStructure;
  HRTIM_TimerInitTypeDef HRTIM_TimerInitStructure;  
  HRTIM_TimerCfgTypeDef HRTIM_TimerWaveStructure;
  HRTIM_CompareCfgTypeDef HRTIM_CompareStructure;
  HRTIM_FaultCfgTypeDef HRTIM_FaultCfgStructure;
  HRTIM_ADCTriggerCfgTypeDef HRTIM_ADCTrigStructure;
  
  NVIC_InitTypeDef    NVIC_InitStructure;
  
  
  /* ----------------------------*/
  /* HRTIM Global initialization */
  /* ----------------------------*/
  /* Use the PLLx2 clock for HRTIM */
  RCC_HRTIM1CLKConfig(RCC_HRTIM1CLK_PLLCLK);
  /* Enable HRTIM clock*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_HRTIM1, ENABLE);
  
  /* HRTIM DLL calibration: periodic calibration, set period to 14µs */
  HRTIM_DLLCalibrationStart(HRTIM1, HRTIM_CALIBRATIONRATE_14);
  
  /* Wait calibration completion*/
  while(HRTIM_GetCommonFlagStatus(HRTIM1, HRTIM_ISR_DLLRDY) == RESET);
  
  
  /* --------------------------------------------------- */
  /* TIMERD initialization: timer mode and PWM frequency */
  /* --------------------------------------------------- */
  HRTIM_TimerInitStructure.HalfModeEnable = HRTIM_HALFMODE_DISABLED;
  HRTIM_TimerInitStructure.StartOnSync = HRTIM_SYNCSTART_DISABLED;
  HRTIM_TimerInitStructure.ResetOnSync = HRTIM_SYNCRESET_DISABLED;
  HRTIM_TimerInitStructure.DACSynchro = HRTIM_DACSYNC_NONE;
  HRTIM_TimerInitStructure.PreloadEnable = HRTIM_PRELOAD_ENABLED;
  HRTIM_TimerInitStructure.UpdateGating = HRTIM_UPDATEGATING_INDEPENDENT;
  HRTIM_TimerInitStructure.BurstMode = HRTIM_TIMERBURSTMODE_MAINTAINCLOCK;
  HRTIM_TimerInitStructure.RepetitionUpdate = HRTIM_UPDATEONREPETITION_ENABLED;
  
  HRTIM_BaseInitStructure.Period = BUCK_PWM_PERIOD;// 100kHz switching frequency
  HRTIM_BaseInitStructure.RepetitionCounter = 3;   // 1 ISR every 4 PWM periods
  HRTIM_BaseInitStructure.PrescalerRatio = HRTIM_PRESCALERRATIO_MUL32;
  HRTIM_BaseInitStructure.Mode = HRTIM_MODE_CONTINOUS;          
  
  HRTIM_Waveform_Init(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, &HRTIM_BaseInitStructure, &HRTIM_TimerInitStructure);
  
  
  /* ------------------------------------------------ */
  /* TIMERD output and registers update configuration */
  /* ------------------------------------------------ */
  HRTIM_TimerWaveStructure.DeadTimeInsertion = HRTIM_TIMDEADTIMEINSERTION_DISABLED;
  HRTIM_TimerWaveStructure.DelayedProtectionMode = HRTIM_TIMDELAYEDPROTECTION_DISABLED;
  HRTIM_TimerWaveStructure.FaultEnable = HRTIM_TIMFAULTENABLE_FAULT1;
  HRTIM_TimerWaveStructure.FaultLock = HRTIM_TIMFAULTLOCK_READWRITE;
  HRTIM_TimerWaveStructure.PushPull = HRTIM_TIMPUSHPULLMODE_DISABLED;
  HRTIM_TimerWaveStructure.ResetTrigger = HRTIM_TIMRESETTRIGGER_NONE;
  HRTIM_TimerWaveStructure.ResetUpdate = HRTIM_TIMUPDATEONRESET_DISABLED;
  HRTIM_TimerWaveStructure.UpdateTrigger = HRTIM_TIMUPDATETRIGGER_NONE;
  HRTIM_WaveformTimerConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, &HRTIM_TimerWaveStructure);
  
  
  /* -------------------------------- */
  /* TD1 and TD2 waveform description */
  /* -------------------------------- */
  /* PWM on TD1, protected by Fault input */
  HRTIM_TIM_OutputStructure.Polarity = HRTIM_OUTPUTPOLARITY_HIGH; 
  HRTIM_TIM_OutputStructure.SetSource = HRTIM_OUTPUTSET_TIMPER;  
  HRTIM_TIM_OutputStructure.ResetSource = HRTIM_OUTPUTRESET_TIMCMP1; 
  HRTIM_TIM_OutputStructure.IdleMode = HRTIM_OUTPUTIDLEMODE_NONE;  
  HRTIM_TIM_OutputStructure.IdleState = HRTIM_OUTPUTIDLESTATE_INACTIVE;          
  HRTIM_TIM_OutputStructure.FaultState = HRTIM_OUTPUTFAULTSTATE_INACTIVE;          
  HRTIM_TIM_OutputStructure.ChopperModeEnable = HRTIM_OUTPUTCHOPPERMODE_DISABLED;        
  HRTIM_TIM_OutputStructure.BurstModeEntryDelayed = HRTIM_OUTPUTBURSTMODEENTRY_REGULAR;
  HRTIM_WaveformOutputConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_OUTPUT_TD1, &HRTIM_TIM_OutputStructure);
  
  /* PWM on TD2, not affected by Fault input */
  HRTIM_TIM_OutputStructure.FaultState = HRTIM_OUTPUTFAULTSTATE_NONE;
  HRTIM_TIM_OutputStructure.SetSource = HRTIM_OUTPUTSET_TIMCMP2;
  HRTIM_TIM_OutputStructure.ResetSource = HRTIM_OUTPUTRESET_TIMPER;
  HRTIM_WaveformOutputConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_OUTPUT_TD2, &HRTIM_TIM_OutputStructure);
  
  /* Set compare registers for duty cycle on TD1 */
  HRTIM_CompareStructure.AutoDelayedMode = HRTIM_AUTODELAYEDMODE_REGULAR;
  HRTIM_CompareStructure.AutoDelayedTimeout = 0;
  HRTIM_CompareStructure.CompareValue = BUCK_PWM_PERIOD/20;     // 5% duty cycle
  HRTIM_WaveformCompareConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_COMPAREUNIT_1, &HRTIM_CompareStructure);
  
  /* Set compare registers for duty cycle on TD2 */
  HRTIM_CompareStructure.AutoDelayedMode = HRTIM_AUTODELAYEDMODE_REGULAR;
  HRTIM_CompareStructure.AutoDelayedTimeout = 0;
  HRTIM_CompareStructure.CompareValue = BUCK_PWM_PERIOD - (BUCK_PWM_PERIOD/3); // 33% duty cycle (NB: from CMP2 to period)
  HRTIM_WaveformCompareConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_COMPAREUNIT_2, &HRTIM_CompareStructure);
  
  
  /* --------------------------*/
  /* ADC trigger initialization */
  /* --------------------------*/
  /* Set compare 3 registers for 1st ADC trigger */
  HRTIM_CompareStructure.AutoDelayedMode = HRTIM_AUTODELAYEDMODE_REGULAR;
  HRTIM_CompareStructure.AutoDelayedTimeout = 0;
  HRTIM_CompareStructure.CompareValue = BUCK_PWM_PERIOD/10; // samples in middle of duty cycle
  HRTIM_WaveformCompareConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_COMPAREUNIT_3, &HRTIM_CompareStructure);
  
  /* Set compare 4 registers for 2nd ADC trigger */
  HRTIM_CompareStructure.AutoDelayedMode = HRTIM_AUTODELAYEDMODE_REGULAR;
  HRTIM_CompareStructure.AutoDelayedTimeout = 0;
  HRTIM_CompareStructure.CompareValue = (BUCK_PWM_PERIOD - ((BUCK_PWM_PERIOD/3)/2)); // samples in middle of duty cycle
  HRTIM_WaveformCompareConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_COMPAREUNIT_4, &HRTIM_CompareStructure);
  
  HRTIM_ADCTrigStructure.Trigger = HRTIM_ADCTRIGGEREVENT24_TIMERD_CMP3 + HRTIM_ADCTRIGGEREVENT24_TIMERD_CMP4;
  HRTIM_ADCTrigStructure.UpdateSource = HRTIM_ADCTRIGGERUPDATE_TIMER_D;
  HRTIM_ADCTriggerConfig(HRTIM1, HRTIM_ADCTRIGGER_2, &HRTIM_ADCTrigStructure);
  
  
  /* --------------------*/
  /* FAULT initialization */
  /* --------------------*/
  HRTIM_FaultCfgStructure.Filter = HRTIM_FAULTFILTER_NONE;
  HRTIM_FaultCfgStructure.Lock = HRTIM_FAULTLOCK_READWRITE;
  HRTIM_FaultCfgStructure.Polarity = HRTIM_FAULTPOLARITY_LOW;
  HRTIM_FaultCfgStructure.Source = HRTIM_FAULTSOURCE_DIGITALINPUT;
  HRTIM_FaultConfig(HRTIM1, &HRTIM_FaultCfgStructure, HRTIM_FAULT_1);
  
  HRTIM_FaultModeCtl(HRTIM1, HRTIM_FAULT_1, HRTIM_FAULT_ENABLED);
  
  
  /* -------------------------*/
  /* Interrupt initialization */
  /* -------------------------*/
  /* Configure and enable HRTIM TIMERD interrupt channel in NVIC */
  NVIC_InitStructure.NVIC_IRQChannel = HRTIM1_TIMD_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* TIMER D issues an interrupt on each repetition event */
  HRTIM_ITConfig(HRTIM1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_TIM_IT_REP, ENABLE);
  
  
  /* ---------------*/
  /* HRTIM start-up */
  /* ---------------*/
  /* Enable HRTIM's outputs TD1 and TD2 */
  /* Note: it is necessary to enable also GPIOs to have outputs functional */
  HRTIM_WaveformOutputStart(HRTIM1, HRTIM_OUTPUT_TD1 | HRTIM_OUTPUT_TD2); 
  
  /* Start HRTIM's TIMER D*/
  HRTIM_WaveformCounterStart(HRTIM1, HRTIM_TIMERID_TIMER_D); 
  
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


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

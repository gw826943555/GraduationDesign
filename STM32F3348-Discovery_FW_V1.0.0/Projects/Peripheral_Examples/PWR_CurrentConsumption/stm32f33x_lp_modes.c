/**
  ******************************************************************************
  * @file    PWR_CurrentConsumption/stm32f33x_lp_modes.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-June-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the STM32F33xx Low Power Modes:
  *           - Sleep Mode
  *           - STOP mode with RTC
  *           - STANDBY mode without RTC
  *           - STANDBY mode with RTC
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
#include "stm32f33x_lp_modes.h"

/** @addtogroup STM32F3348-DISCOVERY_Examples
  * @{
  */

/** @addtogroup PWR_CurrentConsumption
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function configures the system to enter Sleep mode for
  *         current consumption measurement purpose.
  *         Sleep Mode
  *         ==========  
*            - System Running at PLL (72MHz)
  *            - Flash 2 wait states
  *            - Prefetch enabled
  *            - Code running from Internal FLASH
  *            - All peripherals disabled.
  *            - Wakeup using EXTI Line (User Button PA.00)
  * @param  None
  * @retval None
  */
void SleepMode_Measure(void)
{
  __IO uint32_t index = 0;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure all GPIO as analog to reduce current consumption on non used IOs */
  /* Enable GPIOs clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                        RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOF , ENABLE);
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
  
  /* Disable GPIOs clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                         RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOF, DISABLE);

  /* Configure User Button */
  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);

  /* Request to enter SLEEP mode */
  __WFI();

  /* Initialize LED4 on STM32F3348-DISCO board */
  STM_EVAL_LEDInit(LED4);

  /* Infinite loop */
  while (1)
  {
    /* Toggle The LED4 */
    STM_EVAL_LEDToggle(LED4);

    /* Inserted Delay */
    for(index = 0; index < 0x7FFFF; index++);
  }
}

/**
  * @brief  This function configures the system to enter Stop mode with RTC 
  *         clocked by LSI for current consumption measurement purpose.
  *         STOP Mode with RTC clocked by LSI
  *         =====================================   
  *           - RTC Clocked by LSI
  *           - Regulator in LP mode
  *           - HSI, HSE OFF and LSI OFF if not used as RTC Clock source
  *           - No IWDG
  *           - FLASH in deep power down mode
  *           - Automatic Wakeup using RTC clocked by LSI (~5s)
  * @param  None
  * @retval None
  */
void StopMode_Measure(void)
{
  __IO uint32_t index = 0;
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef  NVIC_InitStructure;
  EXTI_InitTypeDef  EXTI_InitStructure;

  /* Allow access to RTC */
  PWR_BackupAccessCmd(ENABLE);

/* The RTC Clock may varies due to LSI frequency dispersion. */   
  /* Enable the LSI OSC */ 
  RCC_LSICmd(ENABLE);

  /* Wait till LSI is ready */  
  while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
  {
  }

  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

  /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();

  /* Configure all GPIO as analog to reduce current consumption on non used IOs */
  /* Enable GPIOs clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                        RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOF , ENABLE);
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
  
  /* Disable GPIOs clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                         RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOF, DISABLE);
     
  /* EXTI configuration */
  EXTI_ClearITPendingBit(EXTI_Line20);
  EXTI_InitStructure.EXTI_Line = EXTI_Line20;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  /* NVIC configuration */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_WKUP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);


  /* RTC Wakeup Interrupt Generation: Clock Source: RTCCLK_Div16, Wakeup Time Base: ~5s
     RTC Clock Source LSI ~40KHz 

     Wakeup Time Base = (16 / (LSI)) * WakeUpCounter
  */
  RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);
  RTC_SetWakeUpCounter(0x30D5-1);
  
  /* Enable the Wakeup Interrupt */
  RTC_ITConfig(RTC_IT_WUT, ENABLE); 

  /* Enable Wakeup Counter */
  RTC_WakeUpCmd(ENABLE);
  
  /* Enter Stop Mode */
  PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);

  /* Initialize LED4 on STM32F3348-DISCO board */
  STM_EVAL_LEDInit(LED4);

  /* Infinite loop */
  while (1)
  {
    /* Toggle The LED4 */
    STM_EVAL_LEDToggle(LED4);

    /* Inserted Delay */
    for(index = 0; index < 0x7FFFF; index++);
  }
}

/**
  * @brief  This function configures the system to enter Standby mode for
  *         current consumption measurement purpose.
  *         STANDBY Mode
  *         ============
  *           - RTC OFF
  *           - IWDG and LSI OFF
  *           - Wakeup using WakeUp Pin1 (PA.00)
  * @param  None
  * @retval None
  */
void StandbyMode_Measure(void)
{
  /* Enable WKUP pin 1 */
  PWR_WakeUpPinCmd(PWR_WakeUpPin_1,ENABLE);

  /* Request to enter STANDBY mode (Wake Up flag is cleared in PWR_EnterSTANDBYMode function) */
  PWR_EnterSTANDBYMode();
  
  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  This function configures the system to enter Standby mode with RTC 
  *         clocked by LSI for current consumption measurement purpose.
  *         STANDBY Mode with RTC clocked by LSI
  *         ========================================
  *           - RTC Clocked by LSI
  *           - IWDG OFF
  *           - Automatic Wakeup using RTC 
  * @param  None
  * @retval None
  */
void StandbyRTCMode_Measure(void)
{
  /* Allow access to RTC */
  PWR_BackupAccessCmd(ENABLE);
  
  /* The RTC Clock may varies due to LSI frequency dispersion. */   
  /* Enable the LSI OSC */ 
  RCC_LSICmd(ENABLE);
  
  /* Wait till LSI is ready */  
  while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
  {
  }
  
  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
  
  /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);
  
  /* Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();

  /* RTC Wakeup Interrupt Generation: Clock Source: RTCCLK_Div16, Wakeup Time Base: ~5s
     RTC Clock Source LSI ~40KHz 

     Wakeup Time Base = (16 / (LSI)) * WakeUpCounter
  */
  RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);
  RTC_SetWakeUpCounter(0x30D5-1);
  
  /* Enable the Wakeup Interrupt */
  RTC_ITConfig(RTC_IT_WUT, ENABLE); 

  /* Enable Wakeup Counter */
  RTC_WakeUpCmd(ENABLE);
  
  /* Clear Wakeup flag */
  PWR_ClearFlag(PWR_FLAG_WU);
  
  /* Request to enter STANDBY mode (Wake Up flag is cleared in PWR_EnterSTANDBYMode function) */
  PWR_EnterSTANDBYMode();
  
  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

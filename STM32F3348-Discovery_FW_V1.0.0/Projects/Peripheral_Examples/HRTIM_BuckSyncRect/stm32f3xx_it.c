/**
  ******************************************************************************
  * @file    stm32f3xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-June-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
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
#include "stm32f3xx_it.h"
    
/** @addtogroup HRTIM_BuckSyncRect
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/   
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                          */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  TimingDelay_Decrement();
}

/******************************************************************************/
/*                 STM32F3xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f334x8.s).                                             */
/******************************************************************************/
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


/**
  * @brief  This function handles HRTIM1_TIMA_IRQHandler interrupt request.
  * The duty cycle on TA1 and TA2 are modified in real time (from 33% to 66%)
  * @param  None
  * @retval None
  */
void HRTIM1_TIMA_IRQHandler(void)
{
  uint32_t CurrentDuty;

  STM_EVAL_LEDToggle(LED4);

  HRTIM_ClearITPendingBit(HRTIM1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_TIM_FLAG_REP);
  
  CurrentDuty = HRTIM1->HRTIM_TIMERx[HRTIM_TIMERINDEX_TIMER_A].CMP1xR;

  /* Increase the compare value up to 66% duty cycle and re-start from 33% */
  if (CurrentDuty < 2*(BUCK_PWM_PERIOD/3))
  {
    CurrentDuty++;
    HRTIM_SlaveSetCompare(HRTIM1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_1,  CurrentDuty); /* Duty cycle update */
    HRTIM_SlaveSetCompare(HRTIM1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_2,  CurrentDuty/2); /* ADC trigger update */
  }
  else
  {
    HRTIM_SlaveSetCompare(HRTIM1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_1,  BUCK_PWM_PERIOD/3); /* Duty cycle update */
    HRTIM_SlaveSetCompare(HRTIM1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_2,  BUCK_PWM_PERIOD/6); /* ADC trigger update */   
  }
    
  STM_EVAL_LEDToggle(LED4);
}


/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

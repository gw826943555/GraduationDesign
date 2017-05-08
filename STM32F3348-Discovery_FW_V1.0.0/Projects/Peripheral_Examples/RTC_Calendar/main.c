/**
  ******************************************************************************
  * @file    RTC_Calendar/main.c 
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

/** @addtogroup RTC_Calendar
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
RTC_DateTypeDef RTC_DateStructure;
RTC_TimeTypeDef RTC_TimeStructure;    
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint8_t showtime[50] = {0};
__IO uint8_t showdate[50] = {0};
/* Private function prototypes -----------------------------------------------*/
static void RTC_Config(void);
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

  /* Initialize LEDs available on STM32F3348-DISCO */
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);
  
  /* Configure RTC Alarm */
  RTC_Config();
  
  /* Infinite loop */
  while (1)
  {
    /* Get the RTC current Time */
    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
    /* Get the RTC current Date */
    RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
    /* Display time Format : hh:mm:ss */
    sprintf((char*)showtime,"%.2d:%.2d:%.2d",RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes, RTC_TimeStructure.RTC_Seconds);
    /* Display date Format : mm-dd-yy */
    sprintf((char*)showdate,"%.2d-%.2d-%.2d",RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Date, 2000 + RTC_DateStructure.RTC_Year); 
 
  }
}

/**
  * @brief   Configure RTC Alarm A to generate alarm each 1s
  * @param  None
  * @retval None
  */
static void RTC_Config(void)
{
  RTC_InitTypeDef RTC_InitStructure;
  RTC_AlarmTypeDef RTC_AlarmStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  
  /* Enable PWR APB1 Clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  
  /* Allow access to Backup */
  PWR_BackupAccessCmd(ENABLE);
  
  /* Reset RTC Domain */
  RCC_BackupResetCmd(ENABLE);
  RCC_BackupResetCmd(DISABLE);
  
  /* Allow access to RTC */
  PWR_BackupAccessCmd(ENABLE);
  
  /* The RTC Clock may varies due to LSI frequency dispersion */   
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
  
  /* RTC prescaler configuration */
  RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
  RTC_InitStructure.RTC_AsynchPrediv = 88;
  RTC_InitStructure.RTC_SynchPrediv = 470;
  RTC_Init(&RTC_InitStructure);
  
  /* Set the alarm 01h:00min:04s */
  RTC_AlarmStructure.RTC_AlarmTime.RTC_H12     = RTC_H12_AM;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours   = 0x01;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = 0x00;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = 0x04;
  RTC_AlarmStructure.RTC_AlarmDateWeekDay = 0x31;
  RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
  /* Alarm mask hour, min and second:default Alarm generation each 1s */
  RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_All; 
  RTC_SetAlarm(RTC_Format_BCD, RTC_Alarm_A, &RTC_AlarmStructure);
  
  /* Enable RTC Alarm A Interrupt */
  RTC_ITConfig(RTC_IT_ALRA, ENABLE);
  
  /* Enable the alarm */
  RTC_AlarmCmd(RTC_Alarm_A, ENABLE);
  
  /* Set the date: Wednesday February 5th 2014 */
  RTC_DateStructure.RTC_Year = 14;
  RTC_DateStructure.RTC_Month = RTC_Month_February;
  RTC_DateStructure.RTC_Date = 05;
  RTC_DateStructure.RTC_WeekDay = RTC_Weekday_Tuesday;
  RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure);
  
  /* Set the time to 01h 00mn 00s AM */
  RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
  RTC_TimeStructure.RTC_Hours   = 0x01;
  RTC_TimeStructure.RTC_Minutes = 0x00;
  RTC_TimeStructure.RTC_Seconds = 0x00; 
  RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);    
  
  RTC_ClearFlag(RTC_FLAG_ALRAF);
  
  /* RTC Alarm A Interrupt Configuration */
  /* EXTI configuration */
  EXTI_ClearITPendingBit(EXTI_Line17);
  EXTI_InitStructure.EXTI_Line = EXTI_Line17;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  /* Enable the RTC Alarm Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  
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

/**
  ******************************************************************************
  * @file    GPIO_IOToggle/main.c 
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

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay =0;
__IO uint8_t BlinkSpeed = 0;
/* Private function prototypes -----------------------------------------------*/
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
  
  /* Initialize LEDs available on STM32F3348-DISCO */
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);
  
  /* Initialize User_Button on STM32F3348-DISCO */
  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);   
  
  /* Initiate Blink Speed variable */ 
  BlinkSpeed = 0;
  
  /* Infinite loop */
  while (1)
  {
    /* Test on blink speed */
    if(BlinkSpeed == 0)
    {
      /*LED3, LED4, LED5 and LED6 Toggle each 50ms*/
      STM_EVAL_LEDToggle(LED3);           
      STM_EVAL_LEDToggle(LED5);           
      STM_EVAL_LEDToggle(LED6);           
      STM_EVAL_LEDToggle(LED4);     
      Delay(50);            
    }      
    else if(BlinkSpeed == 1)
    {
      /*LED3, LED4, LED5 and LED6 Toggle each 200ms*/
      STM_EVAL_LEDToggle(LED3);           
      STM_EVAL_LEDToggle(LED5);           
      STM_EVAL_LEDToggle(LED6);          
      STM_EVAL_LEDToggle(LED4);     
      Delay(200);
    }
    else if(BlinkSpeed == 2)
    {
      /*LED3, LED4, LED5 and LED6 Toggle each 500ms*/
      STM_EVAL_LEDToggle(LED3);          
      STM_EVAL_LEDToggle(LED5);          
      STM_EVAL_LEDToggle(LED6);          
      STM_EVAL_LEDToggle(LED4);     
      Delay(500);
    }    
  }
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

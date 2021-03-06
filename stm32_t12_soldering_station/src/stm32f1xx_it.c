/**
  ******************************************************************************
  * @file    stm32f1xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-February-2014
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
#include "stm32f1xx_it.h"
#include "station.h"
#include "station_UI.h"
#include "m_snprintf.h"

/** @addtogroup IO_Toggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M Processor Exceptions Handlers                          */
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
	station_controll_callback();
	station_ui_input_handler();
	station_ui_callback();
}

/******************************************************************************/
/*                 STM32F1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_md.s).                                            */
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
  * @}
  */ 

/**
  * @brief  This function handles TIM2 interrupt request.
  * @param  None
  * @retval None
  */

void TIM3_IRQHandler()
{

	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET) {
		if (TIM2->CCR2 < 100) {
			TIM2->CCR2 = 100;
		}

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}

	if (TIM_GetITStatus(TIM3, TIM_IT_CC1) == SET) {
		station_iron_heat_clbk();
		TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
	}

	if (TIM_GetITStatus(TIM3, TIM_IT_CC2) == SET) {
		station_iron_recalc_clbk();
		TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);
	}
}

/**
  * @brief  This function handles EXTI9_5 interrupt request.
  * @param  None
  * @retval None
  */

void EXTI9_5_IRQHandler()
{
	if (EXTI_GetITStatus(EXTI_Line9) != RESET) {
		EXTI_ClearITPendingBit(EXTI_Line9);

	}

}

/**
  * @brief  This function handles EXTI15_10 interrupt request.
  * @param  None
  * @retval None
  */

void EXTI15_10_IRQHandler()
{

	if (EXTI_GetITStatus(EXTI_Line13) != RESET) {
		EXTI_ClearITPendingBit(EXTI_Line13);

		station_button_callback();
	}

	if (EXTI_GetITStatus(EXTI_Line12) != RESET) {
		EXTI_ClearITPendingBit(EXTI_Line12);
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

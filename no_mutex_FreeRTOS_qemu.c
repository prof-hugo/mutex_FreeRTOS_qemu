/*==================================================================================================

  no_mutex_FreeRTOS_qemu.c

  Used hardware: STM32F4-Discovery evaluation board (QEMU)

  Example of using the FreeRTOS Real-Time Operating System on the STM32F4-Discovery board.

  ==================================================================================================
*/

#include "diag/Trace.h"
#include "stm32f4_discovery.h"
#include "FreeRTOS.h"
#include "task.h"


void vBlinkLED4(void *pvParam){
  const TickType_t xPeriod = 500 / portTICK_PERIOD_MS;
  TickType_t xLastWakeTime = xTaskGetTickCount();

  while(1){
	trace_puts("Entrando na seção crítica de vBlinkLED4 (green)");
	BSP_LED_Toggle(LED4);
	trace_puts("Saindo da seção crítica de vBlinkLED4 (green)");
	vTaskDelayUntil(&xLastWakeTime, xPeriod); // atraso por bloqueio (RTOS)
  } // while
} // vBlinkLED4


void vBlinkLED5(void *pvParam){
  const TickType_t xPeriod = 500 / portTICK_PERIOD_MS;
  TickType_t xLastWakeTime = xTaskGetTickCount();

  while(1){
	trace_puts("Entrando na seção crítica de vBlinkLED5 (red)");
	BSP_LED_Toggle(LED5);
	trace_puts("Saindo da seção crítica de vBlinkLED5 (red)");
	vTaskDelayUntil(&xLastWakeTime, xPeriod); // atraso por bloqueio (RTOS)
  } // while
} // vBlinkLED5


void main(void){
  __HAL_RCC_GPIOD_CLK_ENABLE();
  BSP_LED_Init(LED4);
  BSP_LED_Init(LED5);

  xTaskCreate(vBlinkLED4, "vBlinkLED4", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
  xTaskCreate(vBlinkLED5, "vBlinkLED5", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

  vTaskStartScheduler();
  while(1);
} // main

/*
	FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
	All rights reserved

	VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

	This file is part of the FreeRTOS distribution.

	FreeRTOS is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License (version 2) as published by the
	Free Software Foundation >>!AND MODIFIED BY!<< the FreeRTOS exception.

	***************************************************************************
	>>!   NOTE: The modification to the GPL is included to allow you to     !<<
	>>!   distribute a combined work that includes FreeRTOS without being   !<<
	>>!   obliged to provide the source code for proprietary components     !<<
	>>!   outside of the FreeRTOS kernel.                                   !<<
	***************************************************************************

	FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
	WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
	FOR A PARTICULAR PURPOSE.  Full license text is available on the following
	link: http://www.freertos.org/a00114.html

	http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
	the FAQ page "My application does not run, what could be wrong?".  Have you
	defined configASSERT()?

	http://www.FreeRTOS.org/support - In return for receiving this top quality
	embedded software for free we request you assist our global community by
	participating in the support forum.

	http://www.FreeRTOS.org/training - Investing in training allows your team to
	be as productive as possible as early as possible.  Now you can receive
	FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
	Ltd, and the world's leading authority on the world's leading RTOS.

	http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
	including FreeRTOS+Trace - an indispensable productivity tool, a DOS
	compatible FAT file system, and our tiny thread aware UDP/IP stack.

	http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
	Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

	http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
	Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
	licenses offer ticketed support, indemnification and commercial middleware.

	http://www.SafeRTOS.com - High Integrity Systems also provide a safety
	engineered and independently SIL3 certified version for use in safety and
	mission critical applications that require provable dependability.

	1 tab == 4 spaces!
*/

/*
	Tarefas do Sistema:

	Tarefa 1: Irrigação do jardim
	Tarefa 2: Iluminação da área externa
	Tarefa 3: Alimentação do pet automatizada
	Tarefa 4: Portão do pet
	Tarefa 5: Ligar o ar-condicionado
	Tarefa 6: Checagem de portas e janelas

*/


#include "Stdio.h"
/* FreeRTOS.org includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
//#include "config.h"
#include <conio.h>
/* Demo includes. */
#include "supporting_functions.h"

/* Seis funções de tarefas. */
void vTask_1(void* pvParameters);
void vTask_2(void* pvParameters);
void vTask_3(void* pvParameters);
void vTask_4(void* pvParameters);
void vTask_5(void* pvParameters);
void vTask_6(void* pvParameters);

/* Used to hold the handle of Task2. */
TaskHandle_t xTask2Handle;

/*-----------------------------------------------------------*/

void HelloTask(){
	while (1) {
		printf("Hello STR\n");
		vTaskDelay(1000);
}
}


/* MAIN */ 
int main(void)
{
	/* Ponteiro tarefa */
	xTaskHandle HT;

	/* Timer para gerenciamento do tempo*/
	//xTimer = xTimerCreate("Timer", Main_TIMER_PERIODO, pdFALSE, 0, NULL);
	
	
	
	/* Tarefa de prioridade 1 (menor) */
	xTaskCreate(HelloTask, "HelloTask", 1000, NULL, 1, &HT);
	
	/* Tarefa com prioridade 3 (maior) */
	xTaskCreate(vTask_1, "Task 1", 1000, NULL, 3, NULL);

	/* Tarefa de prioridade 2 */
	xTaskCreate(vTask_2, "Task 2", 1000, NULL, 2, &xTask2Handle);
	
	
	
	
	//xTimerStart(xTimer, 0);
	
	/* Agendador para iniciar tarefas a serem executadas. */
	vTaskStartScheduler();
	/*Loop Infinito */
	for (;; );
	return 0;
}
/*-----------------------------------------------------------*/




/*Função para  ... */

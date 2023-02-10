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

/*-------------------------------------------------------------------------------------------
				Projeto RTOS utilizando FreeRTOS
	
	-----------------------------------------------------------------------------------
	|		Tarefas do Sistema         |Prioridade|T.Execução|Deadline|Período|
	|Tarefa 1: Ligar o ar-condicionado	   |	1     |	    3    |   4    |  24h  |
	|Tarefa 2: Irrigação do jardim		   |	2     |	    3    |   4    |  12h  |
	|Tarefa 3: Portão do pet		   |	3     |     5    |   6    |  8h   |
	|Tarefa 4: Iluminação da área externa	   |	4     |	    3    |   4    |  24h  |
	|Tarefa 5: Alimentação do pet automatizada |	5     |	    3    |   4    |  8h   |
	|Tarefa 6: Checagem de portas e janelas	   |	6     |     5    |   6    |  12h  |
	-----------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------*/


/* Bibliotecas FreeRTOS */
#include "FreeRTOS.h"
#include "task.h"
//#include "timers.h"
#include "queue.h"
//#include <conio.h>
/* Demo includes. */
#include "supporting_functions.h"

/* Seis funções de tarefas. */
void vTaskFunction(void* pvParameters);
void HelloTask(void* pvParameters);

/* String definidas pra cada tarefa */
const char* pcTextForTask1 = "Tarefa 1: Ar condicionado ligado\r\n";
const char* pcTextForTask2 = "Tarefa 2: Irrigacao do jardim Ligada\r\n";
const char* pcTextForTask3 = "Tarefa 3: Portao do pet aberto\r\n";

/* Função que converte Ticks para Milisegundos de cada tarefa*/
//#define vTask_1 pdMS_TO_TICKS(250);

/* Used to hold the handle of Task2. */
TaskHandle_t xTask2Handle;



/*------------------------------------------------------------------------------------------*/



/* MAIN */
int main(void)
{
	/* Ponteiro tarefa */
	xTaskHandle HT;

	/* Timer para gerenciamento do tempo*/
	//xTimer = xTimerCreate("Timer", Main_TIMER_PERIODO, pdFALSE, 0, NULL);


	/* Tarefa de prioridade 7  */
	xTaskCreate(HelloTask, "HelloTask", 1000, NULL, 7, &HT);




	/* Task1 */
	xTaskCreate(vTaskFunction, "Task 1", 1000, (void*)pcTextForTask1, 1, NULL);

	/* Task2 */
	xTaskCreate(vTaskFunction, "Task 2", 1000, (void*)pcTextForTask2, 2, NULL);

	/* Task3 */
	xTaskCreate(vTaskFunction, "Task 3", 1000, (void*)pcTextForTask3, 3, NULL);







	//xTimerStart(xTimer, 0);

	/* Agendador para iniciar tarefas a serem executadas. */
	vTaskStartScheduler();
	/*Loop Infinito */
	for (;; );
	return 0;
}
/*------------------------------------------------------------------------------------------*/

/*Função para mensagem de iniciar */
void HelloTask(void* pvParameters) {
	while (1) {
		printf("Iniciando Sistema de Casa Inteligente...\n");
		vTaskDelay(1000);
	}
}


/*------------------------------------------------------------------------------------------*/

/*Função para  ... */
void vTaskFunction(void* pvParameters)
{
	char* pcTaskName;
	TickType_t xLastWakeTime;
	const TickType_t xDelay10000ms = pdMS_TO_TICKS(1000UL);

	/* The string to print out is passed in via the parameter.  Cast this to a
	character pointer. */
	pcTaskName = (char*)pvParameters;

	/* The xLastWakeTime variable needs to be initialized with the current tick
	count.  Note that this is the only time we access this variable.  From this
	point on xLastWakeTime is managed automatically by the vTaskDelayUntil()
	API function. */
	xLastWakeTime = xTaskGetTickCount();

	/* As per most tasks, this task is implemented in an infinite loop. */
	for (;; )
	{
		/* Print out the name of this task. */
		vPrintString(pcTaskName);

		/* We want this task to execute exactly every 250 milliseconds.  As per
		the vTaskDelay() function, time is measured in ticks, and the
		pdMS_TO_TICKS() macro is used to convert this to milliseconds.
		xLastWakeTime is automatically updated within vTaskDelayUntil() so does not
		have to be updated by this task code. */
		vTaskDelayUntil(&xLastWakeTime, xDelay10000ms);
	}
}


/*------------------------------------------------------------------------------------------*/

/*Função para  ... */




/*---------------------

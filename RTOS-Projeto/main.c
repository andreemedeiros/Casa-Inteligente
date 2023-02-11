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
	|		Tarefas do Sistema	    |Prioridade|T.Execução|Deadline|Período|
	|Tarefa 1: Ligar o ar-condicionado	    |	1     |	    3    |   4    |  24h  |
	|Tarefa 2: Irrigação do jardim		    |	2     |	    3    |   4    |  12h  |
	|Tarefa 3: Portão do pet	            |	3     |     5    |   6    |  8h   |
	|Tarefa 4: Iluminação da área externa       |	4     |	    3    |   4    |  24h  |
	|Tarefa 5: Alimentação do pet automatizada  |	5     |	    3    |   4    |  8h   |
	|Tarefa 6: Checagem de portas e janelas	    |	6     |     5    |   6    |  12h  |
	-----------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------*/



/* Bibliotecas FreeRTOS */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* Demo includes. */
#include "supporting_functions.h"

/* Funções de tarefas. */
void HelloTask(void* pvParameters);

/* Tarefa para receptor. */
void vSenderTask1(void* pvParameters);
void vSenderTask2(void* pvParameters);
void vSenderTask3(void* pvParameters);
void vSenderTask4(void* pvParameters);
void vSenderTask5(void* pvParameters);
void vSenderTask6(void* pvParameters);

/* Tarefa para receptor da fila */
void vReceiverTask(void* pvParameters);

/* Declaração das variaveis Handle para conjunto de fila */
static QueueHandle_t xQueue1 = NULL, xQueue2 = NULL, xQueue3 = NULL, xQueue4 = NULL, xQueue5 = NULL, xQueue6 = NULL;
static QueueSetHandle_t xQueueSet = NULL;

/*------------------------------------------------------------------------------------------*/


/* MAIN */
int main(void)
{
	/* Ponteiro tarefa */
	xTaskHandle HT;
	/* Tarefa de prioridade 7  */
	xTaskCreate(HelloTask, "HelloTask", 1000, NULL, 8, &HT);


	/* Cria duas Queues com um item por cada fila */
	xQueue1 = xQueueCreate(1, sizeof(char*));
	xQueue2 = xQueueCreate(1, sizeof(char*));
	xQueue3 = xQueueCreate(1, sizeof(char*));
	xQueue4 = xQueueCreate(1, sizeof(char*));
	xQueue5 = xQueueCreate(1, sizeof(char*));
	xQueue6 = xQueueCreate(1, sizeof(char*));

	/* Cria queue com conjunto com numero maximo de manipuladores 6 */
	xQueueSet = xQueueCreateSet(1 * 6);

	/* Adiciona duas queues ao conjunto */
	xQueueAddToSet(xQueue1, xQueueSet);
	xQueueAddToSet(xQueue2, xQueueSet);
	xQueueAddToSet(xQueue3, xQueueSet);
	xQueueAddToSet(xQueue4, xQueueSet);
	xQueueAddToSet(xQueue5, xQueueSet);
	xQueueAddToSet(xQueue6, xQueueSet);

	/* Cria as tarefas enviadas para a fila */
	xTaskCreate(vSenderTask1, "Tarefa 1: ", 100, NULL, 1, NULL);
	xTaskCreate(vSenderTask2, "Tarefa 2: ", 100, NULL, 2, NULL);
	xTaskCreate(vSenderTask3, "Tarefa 3: ", 100, NULL, 3, NULL);
	xTaskCreate(vSenderTask4, "Tarefa 4: ", 100, NULL, 4, NULL);
	xTaskCreate(vSenderTask5, "Tarefa 5: ", 100, NULL, 5, NULL);
	xTaskCreate(vSenderTask6, "Tarefa 6: ", 100, NULL, 6, NULL);

	/* Cria a tarefa de receptor. */
	xTaskCreate(vReceiverTask, "Receptor: ", 100, NULL, 7, NULL);


	/* Agendador para iniciar tarefas a serem executadas. */
	vTaskStartScheduler();
	/* Loop Infinito */
	for (;; );
	return 0;
}
/*------------------------------------------------------------------------------------------*/



/* Função para mensagem de iniciar */
void HelloTask(void* pvParameters) {
	/* Loop infinito */
	while (1) {
		printf("Iniciando Sistema de Casa Inteligente em Tempo Real...\n");
		vTaskDelay(1000);
	}
}
/*------------------------------------------------------------------------------------------*/



/* Função para Queue1 */
static void vSenderTask1(void* pvParameters)
{
	const TickType_t xBlockTime = pdMS_TO_TICKS(300);
	const char* const pcMessage = "Tarefa 1: Ligar Ar condicionado\r\n";

	/* Loop infinito */
	for (;; )
	{
		/* Bloqueia por 100ms. */
		vTaskDelay(xBlockTime);

		/* Envie a string desta tarefa para xQueue1. */
		xQueueSend(xQueue1, &pcMessage, 0);
	}
}
/*------------------------------------------------------------------------------------------*/



/* Função para Queue2 */
static void vSenderTask2(void* pvParameters)
{
	const TickType_t xBlockTime = pdMS_TO_TICKS(300);
	const char* const pcMessage = "Tarefa 2: Ligar Irrigacao do Jardim\r\n";

	/* Loop infinito */
	for (;; )
	{
		/* Bloqueia por 200ms. */
		vTaskDelay(xBlockTime);

		/* Envie a string desta tarefa para xQueue2. */
		xQueueSend(xQueue2, &pcMessage, 0);
	}
}
/*------------------------------------------------------------------------------------------*/



/* Função para Queue3 */
static void vSenderTask3(void* pvParameters)
{
	const TickType_t xBlockTime = pdMS_TO_TICKS(500);
	const char* const pcMessage = "Tarefa 3: Ligar portao pet\r\n";

	/* Loop infinito */
	for (;; )
	{
		/* Bloqueia por 200ms. */
		vTaskDelay(xBlockTime);

		/* Envie a string desta tarefa para xQueue3. */
		xQueueSend(xQueue3, &pcMessage, 0);
	}
}
/*------------------------------------------------------------------------------------------*/



/* Função para Queue4 */
static void vSenderTask4(void* pvParameters)
{
	const TickType_t xBlockTime = pdMS_TO_TICKS(300);
	const char* const pcMessage = "Tarefa 4: Ligar Iluminacao da area externa\r\n";

	/* Loop infinito */
	for (;; )
	{
		/* Bloqueia por 200ms. */
		vTaskDelay(xBlockTime);

		/* Envie a string desta tarefa para xQueue4. */
		xQueueSend(xQueue4, &pcMessage, 0);
	}
}
/*------------------------------------------------------------------------------------------*/



/* Função para Queue5 */
static void vSenderTask5(void* pvParameters)
{
	const TickType_t xBlockTime = pdMS_TO_TICKS(300);
	const char* const pcMessage = "Tarefa 5: Ligar Alimentacao do Pet\r\n";

	/* Loop infinito */
	for (;; )
	{
		/* Bloqueia por 200ms. */
		vTaskDelay(xBlockTime);

		/* Envie a string desta tarefa para xQueue5. */
		xQueueSend(xQueue5, &pcMessage, 0);
	}
}
/*------------------------------------------------------------------------------------------*/



/* Função para Queue6 */
static void vSenderTask6(void* pvParameters)
{
	const TickType_t xBlockTime = pdMS_TO_TICKS(500);
	const char* const pcMessage = "Tarefa 6: Ligar Checagem das Portas/Janelas\r\n";

	/* Loop infinito */
	for (;; )
	{
		/* Bloqueia por 200ms. */
		vTaskDelay(xBlockTime);

		/* Envie a string desta tarefa para xQueue6. */
		xQueueSend(xQueue6, &pcMessage, 0);
	}
}
/*------------------------------------------------------------------------------------------*/



/* Função para receber, verificar e imprimir dados */
static void vReceiverTask(void* pvParameters)
{
	QueueHandle_t xQueueThatContainsData;
	char* pcReceivedString;

	/* Loop infinito */
	for (;; )
	{
		/* Queue para armazenar os dados recebidos */
		xQueueThatContainsData = (QueueHandle_t)xQueueSelectFromSet(xQueueSet, portMAX_DELAY);

		/* Retorna os dados quando ao menos uma das filas contenham dados. tempo de bloqueio definido como zero */
		xQueueReceive(xQueueThatContainsData, &pcReceivedString, 0);

		/* Imprime a string recebida da fila */
		vPrintString(pcReceivedString);
	}
}

/*------------------------------------------------------------------------------------------*/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"

const size_t BUFFER_SIZE = 32;

void vReceiverTask(void *pvParameters) {
	MessageBufferHandle_t buffer = (MessageBufferHandle_t) pvParameters;
	size_t messageSize = BUFFER_SIZE - 4;
	char *message = malloc(messageSize);
	memset(message, '\0', messageSize);
	size_t lengthReceived;
	for (;;) {
		lengthReceived = xMessageBufferReceive(buffer, (void *)message, BUFFER_SIZE, 0);
		if (lengthReceived > 0) {
			printf("length: %d, message: %s\n", lengthReceived, message);
			memset(message, '\0', messageSize);
		}
	}
}

void vSenderTask(void *pvParameters) {
	MessageBufferHandle_t buffer = (MessageBufferHandle_t) pvParameters;
	char message[] = "FreeRTOS + Pi Pico";
	for (;;) {		
		xMessageBufferSend(buffer, (void *)message, strlen(message), 0);
		vTaskDelay(1000);
	}
}

void main() {
	stdio_init_all();
	busy_wait_ms(1000);
	MessageBufferHandle_t buffer = xMessageBufferCreate(BUFFER_SIZE);
	xTaskCreate(vSenderTask, "Sender", 128, (void *)buffer, 1, NULL);
	xTaskCreate(vReceiverTask, "Receiver", 128, (void *)buffer, 1, NULL);
	vTaskStartScheduler();
}

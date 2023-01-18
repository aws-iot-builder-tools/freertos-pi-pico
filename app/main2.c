#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

QueueHandle_t blinkQueue;

void vBlinkReceiverTask() {
	for (;;) {
		int blinks = 0;
		if (xQueueReceive(blinkQueue, &blinks, 0) == pdPASS) {
			for (int i = 0; i < blinks; i++) {
				gpio_put(PICO_DEFAULT_LED_PIN, 1);
				vTaskDelay(200);
				gpio_put(PICO_DEFAULT_LED_PIN, 0);
				vTaskDelay(200);
			}
		}
	}
}

void vBlinkSenderTask() {
	int loops = 4;
	for (;;) {
		for (int i = 1; i <= loops; i++) {
			xQueueSend(blinkQueue, &i, 0);
			vTaskDelay(500 + (i * 500));
		}
	}
}

void main() {
	gpio_init(PICO_DEFAULT_LED_PIN);
	gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
	blinkQueue = xQueueCreate(1, sizeof(int));
	xTaskCreate(vBlinkSenderTask, "Blink Sender", 128, NULL, 1, NULL);
	xTaskCreate(vBlinkReceiverTask, "Blink Receiver", 128, NULL, 1, NULL);
	vTaskStartScheduler();
}

#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

void vBlinkTask() {
	for (;;) {
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        vTaskDelay(250);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        vTaskDelay(250);
    }
}

void main() {
	gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
	xTaskCreate(vBlinkTask, "Blink Task", 128, NULL, 1, NULL);
	vTaskStartScheduler();
}

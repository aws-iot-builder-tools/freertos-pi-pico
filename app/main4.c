#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

SemaphoreHandle_t mutex;

void vSafePrint(char *out) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    puts(out);
    xSemaphoreGive(mutex);
}

void vPrintTime(int task, uint32_t time) {
    char out[32];
    sprintf(out, "Task: %d, Timestamp: %d", task, time);
    vSafePrint(out);
}

bool vTimerCallback(struct repeating_timer *timer) {
    uint32_t time = time_us_32();
    TaskHandle_t handle = timer->user_data;
    xTaskNotifyFromISR(handle, time, eSetValueWithOverwrite, NULL);
    return true;
}

void vNotifyTask(void *pvParameters) {
    int task = (int)pvParameters;
    TaskHandle_t handle = xTaskGetCurrentTaskHandle();
    struct repeating_timer timer;
    add_repeating_timer_ms(1000, vTimerCallback, (void *)handle, &timer);
    uint32_t time;
    for (;;) {
        xTaskNotifyWait(0, 0, &time, portMAX_DELAY);
        vPrintTime(task, time);
    }
}

void main() {
    stdio_init_all();
    mutex = xSemaphoreCreateMutex();
    xTaskCreate(vNotifyTask, "Notify Task 1", 256, (void *)1, 1, NULL);
    xTaskCreate(vNotifyTask, "Notify Task 2", 256, (void *)2, 1, NULL);
    xTaskCreate(vNotifyTask, "Notify Task 3", 256, (void *)3, 1, NULL);
    vTaskStartScheduler();
}

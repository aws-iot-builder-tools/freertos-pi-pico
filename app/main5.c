#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

const int taskDelay = 100;
const int taskSize = 128;

SemaphoreHandle_t mutex;

void vSafePrint(char *out) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    puts(out);
    xSemaphoreGive(mutex);
}

void vTaskSMP(void *pvParameters) {
    TaskHandle_t handle = xTaskGetCurrentTaskHandle();
    UBaseType_t mask = vTaskCoreAffinityGet(handle);
    char *name = pcTaskGetName(handle);
    char out[32];
    for (;;) {
        sprintf(out,"%s  %d  %d  %d", name, 
            get_core_num(), xTaskGetTickCount(), mask);
        vSafePrint(out);
        vTaskDelay(taskDelay);
    }
}

void main() {
    stdio_init_all();    
    mutex = xSemaphoreCreateMutex();
    TaskHandle_t handleA;
    TaskHandle_t handleB;
    xTaskCreate(vTaskSMP, "A", taskSize, NULL, 1, &handleA);
    xTaskCreate(vTaskSMP, "B", taskSize, NULL, 1, &handleB);
    xTaskCreate(vTaskSMP, "C", taskSize, NULL, 1, NULL);
    xTaskCreate(vTaskSMP, "D", taskSize, NULL, 1, NULL);
    vTaskCoreAffinitySet(handleA, (1 << 0));
    vTaskCoreAffinitySet(handleB, (1 << 1));
    vTaskStartScheduler();
}

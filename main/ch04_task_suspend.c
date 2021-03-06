#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "ch04_task_suspend.c";

void myTask(void *pvParam)
{
    char *pcText = (char *)pvParam;

    for (;;)
    {
        ESP_LOGI(TAG, "myTask --> pcText = %s", pcText);

        vTaskDelay(3000 / portTICK_PERIOD_MS);

        // vTaskSuspend(NULL);
    }

    vTaskDelete(NULL);
}

void app_main(void)
{
    // myTask1
    char *pcMyTaskName1 = "myTask1 running";
    TaskHandle_t pxMyTask1 = NULL;
    xTaskCreate(myTask, "myTask1", 2048, (void *)pcMyTaskName1, NULL, &pxMyTask1);

    // myTask2
    char *pcMyTaskName2 = "myTask2 running";
    TaskHandle_t pxMyTask2 = NULL;
    xTaskCreate(myTask, "myTask2", 2048, (void *)pcMyTaskName2, NULL, &pxMyTask2);

    // uxPriority, default 0
    UBaseType_t uxPriority = uxTaskPriorityGet(pxMyTask1);
    ESP_LOGI(TAG, "myTask1 --> uxPriority = %d", uxPriority);
    uxPriority = uxTaskPriorityGet(pxMyTask2);
    ESP_LOGI(TAG, "myTask2 --> uxPriority = %d", uxPriority);

    // sleep 5s
    vTaskDelay(5000 / portTICK_PERIOD_MS);

    // supspend
    // vTaskSuspendAll(); -- error
    vTaskSuspend(pxMyTask1);

    // sleep 15s
    vTaskDelay(15000 / portTICK_PERIOD_MS);

    // resume
    // xTaskResumeAll(); -- error
    vTaskResume(pxMyTask1);
}

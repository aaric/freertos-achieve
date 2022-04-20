#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "ch05_task_list.c";

void myTask(void *pvParam)
{
    char *pcText = (char *)pvParam;

    for (;;)
    {
        ESP_LOGI(TAG, "myTask --> pcText = %s", pcText);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}

void app_main(void)
{
    // myTask1
    char *pcMyTaskName1 = "myTask1 running";
    xTaskCreate(myTask, "myTask1", 2048, (void *)pcMyTaskName1, 1, NULL);

    // myTask2
    char *pcMyTaskName2 = "myTask2 running";
    xTaskCreate(myTask, "myTask2", 2048, (void *)pcMyTaskName2, 1, NULL);

    // vTaskList
    static char pcWriteBuffer[512] = {0};
    while (1)
    {
        vTaskList(pcWriteBuffer);
        // esp_get_free_heap_size()
        ESP_LOGI(TAG, "\nTask          State  Priority  Stack   Num\n%s\n", pcWriteBuffer);

        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}

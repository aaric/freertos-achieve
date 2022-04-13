#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "ch02_task_params";

void myTask(void *pvParam)
{
    int *piNum;
    piNum = (int *)pvParam;

    ESP_LOGI(TAG, "myTask piNum = %d", *piNum);

    vTaskDelay(3000 / portTICK_PERIOD_MS);

    vTaskDelete(NULL);
}

int iNum = 100;

void app_main(void)
{
    xTaskCreate(myTask, "myTask", 2048, (void *)&iNum, 1, NULL);
}

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "ch02_task_params";

int iNum = 100;

typedef struct ComplexNum
{
    int a;
    int b;
} ComplexNum_t;

void myTask(void *pvParam)
{
    // int *piNum;
    // piNum = (int *)pvParam;
    // ESP_LOGI(TAG, "myTask piNum = %d", *piNum);

    ComplexNum_t *psNum;
    psNum = (ComplexNum_t *)pvParam;
    ESP_LOGI(TAG, "myTask a = %d, b = %d", psNum->a, psNum->b);

    vTaskDelay(3000 / portTICK_PERIOD_MS);

    vTaskDelete(NULL);
}

ComplexNum_t sNum = {1, 2};

void app_main(void)
{
    // xTaskCreate(myTask, "myTask", 2048, (void *)&iNum, 1, NULL);
    xTaskCreate(myTask, "myTask", 2048, (void *)&sNum, 1, NULL);
}

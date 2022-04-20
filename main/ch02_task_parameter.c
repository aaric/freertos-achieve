#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "ch02_task_parameter.c";

typedef struct ComplexNum
{
    int a;
    int b;
} ComplexNum_t;

void myTask(void *pvParam)
{
    // int *piNum = (int *)pvParam;
    // ESP_LOGI(TAG, "myTask --> piNum = %d", *piNum);

    // char *pcText = (char *)pvParam;
    // ESP_LOGI(TAG, "myTask --> pcText = %s", pcText);

    ComplexNum_t *psNum = (ComplexNum_t *)pvParam;
    ESP_LOGI(TAG, "myTask --> psNum = { a = %d, b = %d }", psNum->a, psNum->b);

    vTaskDelay(3000 / portTICK_PERIOD_MS);

    vTaskDelete(NULL);
}

// int iNum = 100;

// char *pcTxt = "hello world";

ComplexNum_t sNum = {1, 2};

void app_main(void)
{
    // xTaskCreate(myTask, "myTask", 2048, (void *)&iNum, NULL, NULL);
    // xTaskCreate(myTask, "myTask", 2048, (void *)pcTxt, NULL, NULL);
    xTaskCreate(myTask, "myTask", 2048, (void *)&sNum, NULL, NULL);
}

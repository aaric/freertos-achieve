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

    ComplexNum_t *pxNum = (ComplexNum_t *)pvParam;
    ESP_LOGI(TAG, "myTask --> pxNum = { a = %d, b = %d }", pxNum->a, pxNum->b);

    vTaskDelay(3000 / portTICK_PERIOD_MS);

    vTaskDelete(NULL);
}

// int iNum = 100;

// char *pcTxt = "hello world";

ComplexNum_t xNum = {1, 2};

void app_main(void)
{
    // xTaskCreate(myTask, "myTask", 2048, (void *)&iNum, NULL, NULL);
    // xTaskCreate(myTask, "myTask", 2048, (void *)pcTxt, NULL, NULL);
    xTaskCreate(myTask, "myTask", 2048, (void *)&xNum, NULL, NULL);
}

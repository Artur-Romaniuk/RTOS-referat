#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#define QUEUE_SIZE 10
#define ITEM_SIZE sizeof(int)

QueueHandle_t queue;

void producerTask(void *pvParameters)
{
    int value = 0;
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));          // Czekaj 1 sekunde
        xQueueSend(queue, &value, portMAX_DELAY); // Dodaj wartosc do kolejki
        value++;
    }
}

void consumerTask(void *pvParameters)
{
    int value;
    while (1)
    {
        xQueueReceive(queue, &value, portMAX_DELAY); // Odbierz wartosc z kolejki
        printf("Received value: %d\n", value);
    }
}

void main()
{
    queue = xQueueCreate(QUEUE_SIZE, ITEM_SIZE);
    xTaskCreate(producerTask, "Producer", 1000, NULL, 2, NULL);
    xTaskCreate(consumerTask, "Consumer", 1000, NULL, 1, NULL);
}

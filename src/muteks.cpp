#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

SemaphoreHandle_t mutex;

void Task1(void *pvParameters)
{
    while (1)
    {
        // proba uzyskania dostepu do zasobu chronionego przez muteks
        xSemaphoreTake(mutex, portMAX_DELAY);
        // dostep do chronionego zasobu
        // ...
        // zwolnienie muteksu
        xSemaphoreGive(mutex);
        vTaskDelay(1000);
    }
}

void Task2(void *pvParameters)
{
    while (1)
    {
        // proba uzyskania dostepu do zasobu chronionego przez muteks
        xSemaphoreTake(mutex, portMAX_DELAY);
        // dostep do chronionego zasobu
        // ...
        // zwolnienie muteksu
        xSemaphoreGive(mutex);
        vTaskDelay(500);
    }
}

int main()
{
    // utworzenie muteksu
    mutex = xSemaphoreCreateMutex();

    // utworzenie watkow
    xTaskCreate(Task1, "Task 1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(Task2, "Task 2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    // wlaczenie planisty
    vTaskStartScheduler();

    // nie powinno sie nigdy zdarzyc
    return 0;
}
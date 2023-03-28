#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

SemaphoreHandle_t countSemaphore = NULL;

void criticalFunction(void *parameters)
{
    xSemaphoreTake(countSemaphore, portMAX_DELAY);
    // kod krytyczny
    xSemaphoreGive(countSemaphore);
}

int main()
{
    // utworzenie semafora binarnego
    countSemaphore = xSemaphoreCreateCounting(3, 3);

    // utworzenie watkow
    // stworz 5 watkow, kazdy wywolujacy criticalFunction
    for (int i = 0; i < 5; i++)
    {
        xTaskCreate(criticalFunction, "Critical Task", 1000, NULL, 1, NULL);
    }

    // wlaczenie planisty
    vTaskStartScheduler();

    // nie powinno sie nigdy zdarzyc
    return 0;
}
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

SemaphoreHandle_t xBinarySemaphore;

// przykladowa obsluga przerwania, ktora ma byc sygnalem dla pozostalych zadan
void ISRHandler()
{
    // zmienna sprawdzajaca czy wymagana jest zmiana zadania aktualnie wykonywanego przez procesor
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    // wybudzenie zadania oczekujacego na semafor
    xSemaphoreGiveFromISR(xBinarySemaphore, &xHigherPriorityTaskWoken);
    // ewentualna koniecznosc zmiany zadania aktualnie wykonywanego przez procesor
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void Task1(void *pvParameters)
{
    while (1)
    {
        // oczekiwanie na sygnal od semafora
        xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
        // dostep do chronionego zasobu
        // ...
        vTaskDelay(1000);
    }
}

int main()
{
    // utworzenie semafora binarnego
    xBinarySemaphore = xSemaphoreCreateBinary();

    // ustawienie wartosci poczatkowej semafora na "zajety"
    xSemaphoreTake(xBinarySemaphore, 0);

    // konfiguracja przerwan
    // ...

    // utworzenie watkow
    xTaskCreate(Task1, "Task 1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    // wlaczenie planisty
    vTaskStartScheduler();

    // nie powinno sie nigdy zdarzyc
    return 0;
}
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

// Ustawienie flagi
EventGroupHandle_t xEventGroup;
xEventGroup = xEventGroupCreate();

// Zadanie 1 ustawia flage nr 0 w grupie
void Task1(void *pvParameters)
{
    while (1)
    {
        // Dzialanie programu

        // Ustawienie flagi w przypadku zaistenia pewnej sytuacji
        if (system_state == 1)
        {
            xEventGroupSetBits(xEventGroup, (1 << 0));
        }
    }
}

// Zadanie 2 oczekuje na ustawienie flagi nr 0 w grupie
void Task2(void *pvParameters)
{
    while (1)
    {
        // Nieblokujace oczekiwanie na ustawienie flagi
        EventBits_t uxBits = xEventGroupWaitBits(xEventGroup, (1 << 0), pdTRUE, pdFALSE, 0);
        if ((uxBits & (1 << 0)) != 0)
        {
            // Zrob cos po ustawieniu flagi
        }
        else
        {
            // Sciezka wykonywania gdy flaga nie zostala ustawiona
        }
    }
}

int main(void)
{
    xTaskCreate(Task1, "Task 1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(Task2, "Task 2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}
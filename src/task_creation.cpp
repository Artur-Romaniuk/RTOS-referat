#include <FreeRTOS.h>
#include <task.h>

void task_function(void *parameters)
{
    while (true)
    {
        /*Super Loop*/
    }
}

void main_function(void)
{
    TaskHandle_t task_handle = nullptr;
    size_t stack_size = 100;
    uint16_t task_priority = 10;

    /* utworzenie watku */
    BaseType_t status = xTaskCreate(
        task_function,  /* Funkcja wykonywana przez watek. */
        "Example task", /* Nazwa watku. */
        stack_size,     /* Rozmiar stosu watku w slowach. */
        nullptr,        /* Argument do przekazania watkowi. */
        task_priority,  /* Priorytet watku. */
        &task_handle);  /* Wskaznik na strukture watku. */

    assert(status == pdPASS); /* Zakladamy, ze watek zostal utworzony poprawnie. */

    /* Usuniecie watku. */
    vTaskDelete(task_handle);
}

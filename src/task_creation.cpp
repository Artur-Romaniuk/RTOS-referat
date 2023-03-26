void task_function(void *parameters)
{
    while (true)
    {
        /* Task Super Loop*/
    }
}

void main_function(void)
{
    TaskHandle_t task_handle = nullptr;
    size_t stack_size = 100;
    uint16_t task_priority = 10;

    /* Task creation */
    BaseType_t status = xTaskCreate(
        task_function,  /* Function that implements the task. */
        "Example task", /* Text name for the task. */
        stack_size,     /* Stack size in words, not bytes. */
        nullptr,        /* Parameter passed into the task. */
        task_priority,  /* Priority at which the task is created. */
        &task_handle);  /* Used to pass out the created task's handle. */

    assert(status == pdPASS);

    /* Task deletion */
    vTaskDelete(task_handle);
}

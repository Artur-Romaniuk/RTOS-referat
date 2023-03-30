SemaphoreHandle_t xMutex = NULL;

void recursive_mutex_example(void *pvParameters)
{
    xSemaphoreTakeRecursive(xMutex, portMAX_DELAY);

    // Tutaj wykonujemy operacje, ktore korzystaja z zasobow chronionych przez muteks.

    recursive_mutex_example(pvParameters); // Wywolanie rekurencyjne.

    xSemaphoreGiveRecursive(xMutex);
}
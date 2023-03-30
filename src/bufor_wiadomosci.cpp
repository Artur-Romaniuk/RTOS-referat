#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <message_buffer.h>

// Definiowanie rozmiaru bufora wiadomosci
#define BUFFER_SIZE 100

// Definiowanie bufora wiadomosci
MessageBufferHandle_t xMessageBuffer;

// Watek producenta
void vProducerTask(void *pvParameters)
{
    int message = 0;
    while (1)
    {
        // Umieszczanie wiadomosci w buforze
        xMessageBufferSend(xMessageBuffer, &message, sizeof(int), portMAX_DELAY);
        message++;
        vTaskDelay(pdMS_TO_TICKS(1000)); // Oczekiwanie 1s przed wyslaniem kolejnej wiadomosci
    }
}

// Watek konsumenta
void vConsumerTask(void *pvParameters)
{
    int message = 0;
    while (1)
    {
        // Pobieranie wiadomosci z bufora
        xMessageBufferReceive(xMessageBuffer, &message, sizeof(int), portMAX_DELAY);
        printf("Received message: %d\n", message);
    }
}

void main()
{
    // Tworzenie bufora wiadomosci o rozmiarze BUFFER_SIZE
    xMessageBuffer = xMessageBufferCreate(BUFFER_SIZE);

    // Tworzenie watkow
    xTaskCreate(vProducerTask, "Producer", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(vConsumerTask, "Consumer", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

    // Uruchamianie planisty zadan
    vTaskStartScheduler();
}

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <stream_buffer.h>

// Definicja bufora strumieniowego o rozmiarze 64 bajtów
StreamBufferHandle_t xStreamBuffer;
#define STREAM_BUFFER_SIZE 64

// Watek konsumenta
void consumerTask(void *parameter)
{
    uint8_t data[10]; // Bufor na odbierane dane

    while (1)
    {
        size_t bytesRead = xStreamBufferReceive(xStreamBuffer, data, 10, portMAX_DELAY);
        if (bytesRead > 0)
        {
            // Odebrano dane - wykonaj operacje na nich
            // ...
        }
    }
}

// Obsluga przerwania - producent danych
void interruptHandler()
{
    uint8_t data[10]; // Bufor na dane przekazywane do bufora strumieniowego

    // Generowanie danych
    // ...

    // Wyslanie danych do bufora strumieniowego
    xStreamBufferSendFromISR(xStreamBuffer, data, 10, NULL);
}

int main()
{
    // Tworzenie bufora strumieniowego o zadanym rozmiarze
    xStreamBuffer = xStreamBufferCreate(STREAM_BUFFER_SIZE);

    // Tworzenie watku konsumenta
    xTaskCreate(consumerTask, "Consumer", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

    // Uruchomienie planisty zadan
    vTaskStartScheduler();

    return 0;
}
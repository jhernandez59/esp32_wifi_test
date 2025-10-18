#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Declaraciones externas explícitas
extern "C"
{
    void wifi_task(void *pvParameters);
    void mdns_task(void *pvParameters);
}
static const char *TAG = "Helpers";

extern "C" void create_all_tasks(void)
{
    ESP_LOGI(TAG, "Creando tareas...");

    // Tarea WiFi (alta prioridad)
    xTaskCreate(wifi_task, "WiFi_Task", 12288, NULL, 3, NULL);

    // ✅ AUMENTAR stack de mDNS
    xTaskCreate(mdns_task, "mDNS_Task", 12288, NULL, 1, NULL); // 12KB en lugar de 8KB

    ESP_LOGI(TAG, "✅ Todas las tareas creadas");
}
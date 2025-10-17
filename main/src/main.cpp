#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "task_manager.h"

static const char *TAG = "Main";

extern "C" void app_main(void)
{
    // Inicializar NVS
    ESP_LOGI(TAG, "Inicializando NVS...");
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_LOGI(TAG, "Formateando NVS...");
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    ESP_LOGI(TAG, "✅ NVS inicializado correctamente");

    ESP_LOGI(TAG, "🚀 ESP32 WiFi Test - Iniciando");
    ESP_LOGI(TAG, "==================================");
    ESP_LOGI(TAG, "Versión ESP-IDF: %s", esp_get_idf_version());
    ESP_LOGI(TAG, "Número de cores: %d", portNUM_PROCESSORS);
    ESP_LOGI(TAG, "Tamaño de stack mínimo: %d bytes", configMINIMAL_STACK_SIZE);

    // Mostrar información de memoria
    ESP_LOGI(TAG, "Memoria libre: %d bytes", esp_get_free_heap_size());

    ESP_LOGI(TAG, "----------------------------------");

    // Crear todas las tareas
    create_all_tasks();

    ESP_LOGI(TAG, "✅ Sistema inicializado correctamente");
    ESP_LOGI(TAG, "Las tareas están ejecutándose en segundo plano");
    ESP_LOGI(TAG, "==================================");

    // Loop principal - monitoreo del sistema
    int counter = 0;
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(30000)); // Esperar 30 segundos

        // Mostrar estado del sistema periódicamente
        counter++;
        ESP_LOGI(TAG, "Sistema activo - Ciclo: %d", counter);
        ESP_LOGI(TAG, "Memoria libre actual: %d bytes", esp_get_free_heap_size());

// Mostrar información de tareas (opcional)
#ifdef CONFIG_FREERTOS_USE_TRACE_FACILITY
        ESP_LOGI(TAG, "Número de tareas: %d", uxTaskGetNumberOfTasks());
#endif

        ESP_LOGI(TAG, "----------------------------------");
    }
}
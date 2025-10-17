#include "mdns.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_netif.h"

static const char *TAG = "mDNS";

extern "C" void mdns_task(void *pvParameters)
{
    ESP_LOGI(TAG, "Inicializando mDNS...");

    // Esperar un poco para asegurar que WiFi está estable
    vTaskDelay(pdMS_TO_TICKS(5000));

    // Inicializar mDNS
    esp_err_t err = mdns_init();
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Error iniciando mDNS: %s", esp_err_to_name(err));
        vTaskDelete(NULL);
        return;
    }

    // Configurar hostname
    mdns_hostname_set("esp32-test");
    mdns_instance_name_set("ESP32 Test Device");

    // Añadir servicios
    mdns_service_add(NULL, "_http", "_tcp", 80, NULL, 0);
    mdns_service_add(NULL, "_arduino", "_tcp", 3232, NULL, 0);

    // Añadir información adicional (TXT records)
    mdns_service_txt_item_set("_http", "_tcp", "board", "ESP32");
    mdns_service_txt_item_set("_http", "_tcp", "model", "Test Device");
    mdns_service_txt_item_set("_http", "_tcp", "service", "WiFi Test");

    ESP_LOGI(TAG, "✅ mDNS iniciado correctamente");
    ESP_LOGI(TAG, "🌐 Acceso por: http://esp32-test.local");
    ESP_LOGI(TAG, "📡 Servicios disponibles:");
    ESP_LOGI(TAG, "   - HTTP: esp32-test.local:80");
    ESP_LOGI(TAG, "   - Arduino: esp32-test.local:3232");

    // Verificación adicional después de un tiempo
    vTaskDelay(pdMS_TO_TICKS(2000));

    // ✅ CORREGIDO: Verificar que los servicios están registrados
    ESP_LOGI(TAG, "Verificando servicios mDNS...");

    // La función requiere 3 parámetros en ESP-IDF v5.x
    if (mdns_service_exists("esp32-test", "_http", "_tcp"))
    {
        ESP_LOGI(TAG, "✅ Servicio HTTP registrado correctamente");
    }
    else
    {
        ESP_LOGE(TAG, "❌ Servicio HTTP NO registrado");
    }

    if (mdns_service_exists("esp32-test", "_arduino", "_tcp"))
    {
        ESP_LOGI(TAG, "✅ Servicio Arduino registrado correctamente");
    }
    else
    {
        ESP_LOGE(TAG, "❌ Servicio Arduino NO registrado");
    }

    // mDNS se maneja automáticamente, solo mantener la tarea viva
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(10000));
        ESP_LOGI(TAG, "mDNS activo - Memoria libre: %d bytes", esp_get_free_heap_size());
    }
}
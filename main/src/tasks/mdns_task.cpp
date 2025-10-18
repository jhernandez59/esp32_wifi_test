#include "mdns.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_netif.h"

static const char *TAG = "mDNS";

extern "C" void mdns_task(void *pvParameters)
{
    ESP_LOGI(TAG, "🎯 Tarea mDNS INICIADA");

    // Esperar a que WiFi esté completamente conectado
    ESP_LOGI(TAG, "⏳ Esperando 10 segundos para WiFi...");
    vTaskDelay(pdMS_TO_TICKS(10000));

    ESP_LOGI(TAG, "🔧 Inicializando mDNS...");

    // Inicializar mDNS
    esp_err_t err = mdns_init();
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "❌ FALLA CRÍTICA en mdns_init(): %s", esp_err_to_name(err));
        ESP_LOGE(TAG, "❌ mDNS NO funcionará");
        vTaskDelete(NULL);
        return;
    }
    ESP_LOGI(TAG, "✅ mdns_init() exitoso");

    // Configurar hostname
    err = mdns_hostname_set("esp32-test");
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "❌ Error en mdns_hostname_set(): %s", esp_err_to_name(err));
    }
    else
    {
        ESP_LOGI(TAG, "✅ Hostname configurado: esp32-test");
    }

    // Servicio simple HTTP
    err = mdns_service_add(NULL, "_http", "_tcp", 80, NULL, 0);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "❌ Error en mdns_service_add(HTTP): %s", esp_err_to_name(err));
    }
    else
    {
        ESP_LOGI(TAG, "✅ Servicio HTTP registrado");
    }

    ESP_LOGI(TAG, "🎉 mDNS CONFIGURADO EXITOSAMENTE");
    ESP_LOGI(TAG, "🌐 Debería aparecer como: esp32-test.local");

    // Loop principal
    while (1)
    {
        ESP_LOGI(TAG, "💚 mDNS activo - IP debería ser anunciada");
        vTaskDelay(pdMS_TO_TICKS(30000)); // 30 segundos
    }
}
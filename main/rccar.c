#include <string.h>

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include <esp_http_server.h>

#include "nvs_flash.h"

#include "handlers.h"
#include "common.h"

static const char *TAG = "wifi softAP";

static void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
    ESP_LOGI(TAG, "wifi event handler");
}

void wifi_init_softap() {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL));
    wifi_config_t wifi_config = {
        .ap = {
            .ssid = WIFI_SSID,
            .ssid_len = strlen(WIFI_SSID),
            .password = WIFI_PASS,
            .max_connection = 4,
            .authmode = WIFI_AUTH_WPA3_PSK,
            .sae_pwe_h2e = WPA3_SAE_PWE_BOTH,
            .pmf_cfg = {
                .required = true,
            }
        }
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi started");
}

void start_webserver() {
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    config.lru_purge_enable = true;

    ESP_LOGI(TAG, "Starting server on port: %d", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) {
        ESP_LOGI(TAG, "Registering URI handlers");
        ESP_LOGI(TAG, "Registering root");
        httpd_register_uri_handler(server, &root);

        ESP_LOGI(TAG, "Registering maju");
        httpd_register_uri_handler(server, &maju);
        ESP_LOGI(TAG, "Registering mundur");
        httpd_register_uri_handler(server, &mundur);
        ESP_LOGI(TAG, "Registering stop");
        httpd_register_uri_handler(server, &stop);
    }
}

void app_main() {
    ESP_LOGI(TAG, "Initializing");
    gpio_reset_pin(RC_PIN_BAN_KANAN_MUNDUR);
    gpio_reset_pin(RC_PIN_BAN_KIRI_MUNDUR);
    gpio_reset_pin(RC_PIN_BAN_KANAN_MAJU);
    gpio_reset_pin(RC_PIN_BAN_KIRI_MAJU);
    gpio_set_direction(RC_PIN_BAN_KANAN_MAJU, GPIO_MODE_OUTPUT);
    gpio_set_direction(RC_PIN_BAN_KIRI_MAJU, GPIO_MODE_OUTPUT);
    gpio_set_direction(RC_PIN_BAN_KANAN_MUNDUR, GPIO_MODE_OUTPUT);
    gpio_set_direction(RC_PIN_BAN_KIRI_MUNDUR, GPIO_MODE_OUTPUT);

    mutex = xSemaphoreCreateMutex();

    ESP_LOGI(TAG, "Initializing NVS");
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "Initializing WiFi");
    wifi_init_softap();
    start_webserver();

    ESP_LOGI(TAG, "Main returning");
}

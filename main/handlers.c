#include <esp_http_server.h>
#include "page.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"

#include "common.h"
#include "handlers.h"

SemaphoreHandle_t mutex = NULL;

const httpd_uri_t root = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = root_handler,
    .user_ctx = NULL
};

const httpd_uri_t maju = {
    .uri = "/maju",
    .method = HTTP_GET,
    .handler = maju_handler,
    .user_ctx = NULL
};

const httpd_uri_t mundur = {
    .uri = "/mundur",
    .method = HTTP_GET,
    .handler = mundur_handler,
    .user_ctx = NULL
};

const httpd_uri_t stop = {
    .uri = "/stop",
    .method = HTTP_GET,
    .handler = stop_handler,
    .user_ctx = NULL
};

esp_err_t root_handler(httpd_req_t *req) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    httpd_resp_send(req, html_page, HTTPD_RESP_USE_STRLEN);
    httpd_resp_send_chunk(req, NULL, 0);
    xSemaphoreGive(mutex);
    return ESP_OK;
}

esp_err_t maju_handler(httpd_req_t *req) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    gpio_set_level(RC_PIN_BAN_KANAN_MUNDUR, 0);
    gpio_set_level(RC_PIN_BAN_KIRI_MUNDUR, 0);
    gpio_set_level(RC_PIN_BAN_KANAN_MAJU, 1);
    gpio_set_level(RC_PIN_BAN_KIRI_MAJU, 1);

    httpd_resp_send(req, "maju", HTTPD_RESP_USE_STRLEN);
    httpd_resp_send_chunk(req, NULL, 0);
    xSemaphoreGive(mutex);
    return ESP_OK;
}

esp_err_t mundur_handler(httpd_req_t *req) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    gpio_set_level(RC_PIN_BAN_KANAN_MAJU, 0);
    gpio_set_level(RC_PIN_BAN_KIRI_MAJU, 0);
    gpio_set_level(RC_PIN_BAN_KANAN_MUNDUR, 1);
    gpio_set_level(RC_PIN_BAN_KIRI_MUNDUR, 1);

    httpd_resp_send(req, "mundur", HTTPD_RESP_USE_STRLEN);
    httpd_resp_send_chunk(req, NULL, 0);
    xSemaphoreGive(mutex);
    return ESP_OK;
}

esp_err_t stop_handler(httpd_req_t *req) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    gpio_set_level(RC_PIN_BAN_KANAN_MAJU, 0);
    gpio_set_level(RC_PIN_BAN_KIRI_MAJU, 0);
    gpio_set_level(RC_PIN_BAN_KANAN_MUNDUR, 0);
    gpio_set_level(RC_PIN_BAN_KIRI_MUNDUR, 0);

    httpd_resp_send(req, "stop", HTTPD_RESP_USE_STRLEN);
    httpd_resp_send_chunk(req, NULL, 0);
    xSemaphoreGive(mutex);
    return ESP_OK;
}
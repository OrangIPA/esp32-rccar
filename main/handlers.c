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

const httpd_uri_t kanan_maju = {
    .uri = "/kanan-maju",
    .method = HTTP_GET,
    .handler = maju_handler,
    .user_ctx = NULL
};

const httpd_uri_t kanan_mundur = {
    .uri = "/kanan-mundur",
    .method = HTTP_GET,
    .handler = mundur_handler,
    .user_ctx = NULL
};

const httpd_uri_t kanan_stop = {
    .uri = "/kanan-stop",
    .method = HTTP_GET,
    .handler = stop_handler,
    .user_ctx = NULL
};

const httpd_uri_t kiri_maju = {
    .uri = "/kiri-maju",
    .method = HTTP_GET,
    .handler = maju_handler,
    .user_ctx = NULL
};

const httpd_uri_t kiri_mundur = {
    .uri = "/kiri-mundur",
    .method = HTTP_GET,
    .handler = mundur_handler,
    .user_ctx = NULL
};

const httpd_uri_t kiri_stop = {
    .uri = "/kiri-stop",
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

esp_err_t kanan_maju_handler(httpd_req_t *req) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    gpio_set_level(RC_PIN_BAN_KANAN_MUNDUR, 0);
    gpio_set_level(RC_PIN_BAN_KANAN_MAJU, 1);

    httpd_resp_send(req, "kanan maju", HTTPD_RESP_USE_STRLEN);
    httpd_resp_send_chunk(req, NULL, 0);
    xSemaphoreGive(mutex);
    return ESP_OK;
}

esp_err_t kanan_mundur_handler(httpd_req_t *req) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    gpio_set_level(RC_PIN_BAN_KANAN_MAJU, 0);
    gpio_set_level(RC_PIN_BAN_KANAN_MUNDUR, 1);

    httpd_resp_send(req, "kanan mundur", HTTPD_RESP_USE_STRLEN);
    httpd_resp_send_chunk(req, NULL, 0);
    xSemaphoreGive(mutex);
    return ESP_OK;
}

esp_err_t kanan_stop_handler(httpd_req_t *req) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    gpio_set_level(RC_PIN_BAN_KANAN_MAJU, 0);
    gpio_set_level(RC_PIN_BAN_KANAN_MUNDUR, 0);

    httpd_resp_send(req, "kanan stop", HTTPD_RESP_USE_STRLEN);
    httpd_resp_send_chunk(req, NULL, 0);
    xSemaphoreGive(mutex);
    return ESP_OK;
}

esp_err_t kiri_maju_handler(httpd_req_t *req) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    gpio_set_level(RC_PIN_BAN_KIRI_MUNDUR, 0);
    gpio_set_level(RC_PIN_BAN_KIRI_MAJU, 1);

    httpd_resp_send(req, "kiri maju", HTTPD_RESP_USE_STRLEN);
    httpd_resp_send_chunk(req, NULL, 0);
    xSemaphoreGive(mutex);
    return ESP_OK;
}

esp_err_t kiri_mundur_handler(httpd_req_t *req) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    gpio_set_level(RC_PIN_BAN_KIRI_MAJU, 0);
    gpio_set_level(RC_PIN_BAN_KIRI_MUNDUR, 1);

    httpd_resp_send(req, "kiri mundur", HTTPD_RESP_USE_STRLEN);
    httpd_resp_send_chunk(req, NULL, 0);
    xSemaphoreGive(mutex);
    return ESP_OK;
}

esp_err_t kiri_stop_handler(httpd_req_t *req) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    gpio_set_level(RC_PIN_BAN_KIRI_MAJU, 0);
    gpio_set_level(RC_PIN_BAN_KIRI_MUNDUR, 0);

    httpd_resp_send(req, "kiri stop", HTTPD_RESP_USE_STRLEN);
    httpd_resp_send_chunk(req, NULL, 0);
    xSemaphoreGive(mutex);
    return ESP_OK;
}
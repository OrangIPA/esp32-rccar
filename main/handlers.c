#include <esp_http_server.h>
#include "page.h"
#include "driver/gpio.h"
#include "common.h"

esp_err_t root_handler(httpd_req_t *req) {
    httpd_resp_send(req, html_page, HTTPD_RESP_USE_STRLEN);
    httpd_resp_send_chunk(req, NULL, 0);
    return ESP_OK;
}

esp_err_t maju_handler(httpd_req_t *req) {
    gpio_set_level(BLINK_LED, 1);

    httpd_resp_send(req, "maju", HTTPD_RESP_USE_STRLEN);
    httpd_resp_send_chunk(req, NULL, 0);
    return ESP_OK;
}

esp_err_t stop_handler(httpd_req_t *req) {
    gpio_set_level(BLINK_LED, 0);

    httpd_resp_send(req, "stop", HTTPD_RESP_USE_STRLEN);
    httpd_resp_send_chunk(req, NULL, 0);
    return ESP_OK;
}
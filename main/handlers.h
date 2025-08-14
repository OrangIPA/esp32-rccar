#pragma once

#include <esp_http_server.h>
#include "freertos/semphr.h"

extern SemaphoreHandle_t mutex;

esp_err_t root_handler(httpd_req_t *req);
extern const httpd_uri_t root;

esp_err_t kanan_maju_handler(httpd_req_t *req);
extern const httpd_uri_t kanan_maju;

esp_err_t kanan_mundur_handler(httpd_req_t *req);
extern const httpd_uri_t kanan_mundur;

esp_err_t kanan_stop_handler(httpd_req_t *req);
extern const httpd_uri_t kanan_stop;

esp_err_t kiri_maju_handler(httpd_req_t *req);
extern const httpd_uri_t kiri_maju;

esp_err_t kiri_mundur_handler(httpd_req_t *req);
extern const httpd_uri_t kiri_mundur;

esp_err_t kiri_stop_handler(httpd_req_t *req);
extern const httpd_uri_t kiri_stop;
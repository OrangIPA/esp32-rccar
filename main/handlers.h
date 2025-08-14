#pragma once

#include <esp_http_server.h>
#include "freertos/semphr.h"

extern SemaphoreHandle_t mutex;

esp_err_t root_handler(httpd_req_t *req);
extern const httpd_uri_t root;

esp_err_t maju_handler(httpd_req_t *req);
extern const httpd_uri_t maju;

esp_err_t mundur_handler(httpd_req_t *req);
extern const httpd_uri_t mundur;

esp_err_t stop_handler(httpd_req_t *req);
extern const httpd_uri_t stop;
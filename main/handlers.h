#pragma once

#include <esp_http_server.h>

esp_err_t root_handler(httpd_req_t *req);
const httpd_uri_t root = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = root_handler,
    .user_ctx = NULL
};

esp_err_t maju_handler(httpd_req_t *req);
const httpd_uri_t maju = {
    .uri = "/maju",
    .method = HTTP_GET,
    .handler = maju_handler,
    .user_ctx = NULL
};

esp_err_t stop_handler(httpd_req_t *req);
const httpd_uri_t stop = {
    .uri = "/stop",
    .method = HTTP_GET,
    .handler = stop_handler,
    .user_ctx = NULL
};
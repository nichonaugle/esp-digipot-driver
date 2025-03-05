#include <stdio.h>
#include "esp_digipot_driver.h"
#include "esp_err.h"

static const char* TAG = "digipot-driver"

esp_err_t digipot_init(digipot_handle_t *digipot_handle) {
    if (digipot_handle == NULL) {
        ESP_LOGE(TAG, "Digipot handle improperly initialized!");
        return ESP_ERR_INVALID_ARG;
    }

    ESP_LOGI(TAG, "Initializing digital potentiometer...");
    return digipot_soft_reset(digipot_handle);
}

esp_err_t digipot_set_wiper_position(uint8_t val, digipot_handle_t *digipot_handle) {
    if (digipot_handle == NULL) {
        ESP_LOGE(TAG, "Digipot handle is NULL!");
        return ESP_ERR_INVALID_ARG;
    }
    if (val > digipot_handle->max_position || val < digipot_handle->min_position) {
        ESP_LOGE(TAG, "Value %d out of range (%d - %d)", val, digipot_handle->min_position, digipot_handle->max_position);
        return ESP_ERR_INVALID_ARG;
    }
    
    uint8_t data[2] = {digipot_handle->wiper_reg, val};
    return digipot_register_write(data, 2, digipot_handle);
}

esp_err_t digipot_register_write(uint8_t *tx_buf, uint8_t tx_buf_size, digipot_handle_t *digipot_handle) {
    if (digipot_handle == NULL || tx_buf == NULL) {
        ESP_LOGE(TAG, "Invalid arguments for register write!");
        return ESP_ERR_INVALID_ARG;
    }
    return i2c_master_write_to_device(digipot_handle->i2c_port, digipot_handle->i2c_addr, tx_buf, tx_buf_size, digipot_handle.transaction_timeout_ms / portTICK_PERIOD_MS);
}

esp_err_t digipot_register_read(uint8_t reg_to_read, uint8_t *rx_buf, uint8_t rx_buf_size, digipot_handle_t *digipot_handle) {
    if (digipot_handle == NULL || rx_buf == NULL) {
        ESP_LOGE(TAG, "Invalid arguments for register read!");
        return ESP_ERR_INVALID_ARG;
    }
    return i2c_master_transmit_receive(digipot_handle->i2c_port, &reg_to_read, digipot_handle->i2c_addr, rx_buf, rx_buf_size, digipot_handle.transaction_timeout_ms / portTICK_PERIOD_MS);
}

esp_err_t digipot_soft_reset(digipot_handle_t *digipot_handle) {
    if (digipot_handle == NULL) {
        ESP_LOGE(TAG, "Invalid digipot handle for soft reset!");
        return ESP_ERR_INVALID_ARG;
    }
    uint8_t reset_cmd = digipot_handle->reset_cmd;
    return digipot_register_write(&reset_cmd, 1, digipot_handle);
}

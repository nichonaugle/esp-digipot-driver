#include <stdio.h>
#include "esp_digipot_driver.h"
#include "digipot_configs.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/i2c_master.h"

static const char* TAG = "digipot-driver";

esp_err_t digipot_init(digipot_handle_t *digipot_handle, i2c_master_bus_handle_t bus_handle, digipot_type_t digipot_type, gpio_num_t sda_gpio, gpio_num_t scl_gpio, size_t clock_speed) {
    if (sda_gpio == NULL || scl_gpio == NULL || clock_speed == NULL || digipot_handle == NULL) {
        ESP_LOGE(TAG, "Digipot improperly initialized!");
        return ESP_ERR_INVALID_ARG;
    }

    if (digipot_type >= DIGIPOT_COUNT) {
        ESP_LOGE(TAG, "Invalid digipot type selected!");
        return ESP_ERR_INVALID_ARG;
    }

    digipot_handle = digipot_config_table[digipot_type];

    digipot_handle->dev_cfg = {
        .address = digipot_handle.i2c_address,
        .clk_speed = clock_speed,
        .sda_io_num = sda_gpio,
        .scl_io_num = scl_gpio
    };

    esp_err_t err = i2c_master_bus_add_device(bus_handle, digipot_handle->dev_cfg, digipot_handle->dev_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to add digipot to bus!");
        return err;
    }
    ESP_LOGI(TAG, "Added digipot to bus. Initializing...");
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

esp_err_t digipot_register_read(uint8_t reg_to_read, uint8_t *rx_buf, uint8_t rx_buf_size, digipot_handle_t *digipot_handle) {
    if (digipot_handle == NULL || rx_buf == NULL) {
        ESP_LOGE(TAG, "Invalid arguments for register read!");
        return ESP_ERR_INVALID_ARG;
    }
    return i2c_master_transmit_receive(digipot_handle->dev_handle, &reg_to_read, sizeof(reg_to_read), rx_buf, rx_buf_size, digipot_handle->transaction_timeout_ms);
}

esp_err_t digipot_register_write(uint8_t *tx_buf, uint8_t tx_buf_size, digipot_handle_t *digipot_handle) {
    if (digipot_handle == NULL || tx_buf == NULL) {
        ESP_LOGE(TAG, "Invalid arguments for register write!");
        return ESP_ERR_INVALID_ARG;
    }
    return i2c_master_transmit(digipot_handle->dev_handle, tx_buf, tx_buf_size, digipot_handle->transaction_timeout_ms);
}

esp_err_t digipot_soft_reset(digipot_handle_t *digipot_handle) {
    if (digipot_handle == NULL) {
        ESP_LOGE(TAG, "Invalid digipot handle for soft reset!");
        return ESP_ERR_INVALID_ARG;
    }
    uint8_t soft_reset_cmd = digipot_handle->soft_reset_cmd;
    return digipot_register_write(&soft_reset_cmd, 1, digipot_handle);
}

esp_err_t digipot_deinit(digipot_handle_t *digipot_handle) {
    return i2c_master_bus_rm_device(digipot_handle->dev_handle);
}
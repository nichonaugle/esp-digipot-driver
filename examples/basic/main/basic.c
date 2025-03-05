#include <stdio.h>
#include "esp_err.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "esp_digipot_driver.h"  // Include your digipot driver

static const char* TAG = "basic-digipot-test"

// I2C configuration
#define I2C_MASTER_SCL_IO    22  // Change as needed
#define I2C_MASTER_SDA_IO    21  // Change as needed
#define I2C_MASTER_FREQ_HZ   400000  // 400kHz I2C speed
#define I2C_PORT_NUM         I2C_NUM_0 // Base port number

void i2c_master_init() {
    i2c_config_t config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ
    };

    ESP_ERROR_CHECK(i2c_param_config(I2C_PORT_NUM, &config));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_PORT_NUM, config.mode, 0, 0, 0));
}

void app_main(void) {
    ESP_LOGI(TAG, "Initializing I2C...");
    i2c_master_init();

    ESP_LOGI(TAG, "Initializing Digipot...");
    // Define digipot
    digipot_handle_t digipot = {
        .device_name = "AD5246",
        .i2c_port = I2C_PORT_NUM,
        .i2c_address = 0x2C,  // Update with correct I2C address
        .max_position = 255,  // 8-bit wiper
        .min_position = 0,
        .wiper_bit_count = 8,
        .soft_reset_cmd = 0x80,
        .transaction_timeout_ms = 100
    };

    if (digipot_init(&digipot) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize digipot!");
        return;
    }

    uint8_t wiper_value = digipot.min_position;
    uint8_t read_value;
    for (uint8_t wiper_value = digipot.min_position, wiper_value < digipot.max_position, wiper_value++) {
        ESP_LOGI(TAG, "Setting wiper to %d", wiper_value);
        if (digipot_set_wiper_position(wiper_value, &digipot) != ESP_OK) {
            ESP_LOGE(TAG, "Failed to set wiper position!");
            break;
        }

        if (digipot_register_read(&read_value, 1, &digipot) != ESP_OK) {
            ESP_LOGE(TAG, "Failed to read wiper position!");
            break;
        }

        if (read_value != wiper_value) {
            ESP_LOGE(TAG, "Wiper position read does not match set wiper position!");
            break;
        }
    }
}

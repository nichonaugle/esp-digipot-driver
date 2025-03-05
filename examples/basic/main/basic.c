#include <stdio.h>
#include "esp_err.h"
#include "esp_log.h"
#include "driver/i2c_master.h"
#include "esp_digipot_driver.h"  // Include your digipot driver

// I2C configuration
#define I2C_MASTER_SCL_IO    22  // Change as needed
#define I2C_MASTER_SDA_IO    21  // Change as needed
#define I2C_MASTER_FREQ_HZ   400000  // 400kHz I2C speed
#define I2C_PORT_NUM         I2C_NUM_0 // Base port number

// Selected digipot
#define SELECTED_DIGIPOT     AD5246
static const char* TAG = "basic-digipot-test";

void app_main(void) {
    ESP_LOGI(TAG, "Initializing I2C...");
    i2c_master_bus_config_t i2c_mst_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_PORT_NUM,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .glitch_ignore_cnt = 7,
    };
    i2c_master_bus_handle_t bus_handle;
    
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));

    ESP_LOGI(TAG, "Initializing Digipot...");
    digipot_handle_t digipot;
    if (digipot_init(&digipot, bus_handle, SELECTED_DIGIPOT, I2C_MASTER_SDA_IO, I2C_MASTER_SCL_IO, I2C_MASTER_FREQ_HZ) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize digipot!");
        return;
    }

    uint8_t wiper_value = digipot.min_position;
    for (uint8_t wiper_value = digipot.min_position; wiper_value < digipot.max_position; wiper_value++) {
        ESP_LOGI(TAG, "Setting wiper to %d", wiper_value);
        if (digipot_set_wiper_position(wiper_value, &digipot) != ESP_OK) {
            ESP_LOGE(TAG, "Failed to set wiper position!");
            break;
        }
    }
}

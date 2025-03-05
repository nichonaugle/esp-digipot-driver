#ifndef ESP_DIGIPOT_DRIVER_H
#define ESP_DIGIPOT_DRIVER_H

#include "esp_err.h"
#include "driver/i2c_master.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char device_name[32];  // Max of 16 characters, including null terminator
    i2c_port_t i2c_port;  // I2C port number
    i2c_device_config_t dev_cfg;
    i2c_master_dev_handle_t dev_handle;
    uint8_t i2c_address;  // I2C address of the digipot
    uint8_t wiper_reg;
    uint8_t max_position; // Max position of the digipot
    uint8_t min_position; // Min position of the digipot
    uint8_t wiper_bit_count; // Bit resolution of the wiper, typically 7 or 8 bits
    uint8_t soft_reset_cmd;
    uint32_t transaction_timeout_ms;
} digipot_handle_t;

typedef enum {
    AD5246,
    /* Add more variants here if needed */
    DIGIPOT_COUNT
} digipot_type_t;

esp_err_t digipot_init(digipot_handle_t *digipot_handle, i2c_master_bus_handle_t bus_handle, digipot_type_t digipot_type, gpio_num_t sda_gpio, gpio_num_t scl_gpio, size_t clock_speed);

esp_err_t digipot_set_wiper_position(uint8_t val, digipot_handle_t *digipot_handle);

esp_err_t digipot_register_read(uint8_t reg_to_read, uint8_t *rx_buf, uint8_t rx_buf_size, digipot_handle_t *digipot_handle);

esp_err_t digipot_register_write(uint8_t *tx_buf, uint8_t tx_buf_size, digipot_handle_t *digipot_handle);

esp_err_t digipot_soft_reset(digipot_handle_t *digipot_handle);

esp_err_t digipot_deinit(digipot_handle_t *digipot_handle);

#ifdef __cplusplus
}
#endif

#endif //ESP_DIGIPOT_DRIVER_H
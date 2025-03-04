#include "esp_err.h"

enum DIGIPOT_TYPE {
    /* Analog Devices */
    AD5246,
};

typedef digipot_handle {
    i2c_device_config
    max_resistance
    min_resistance
    wiper_bit_count
} digipot_handle_t

esp_err_t digipot_init();

esp_err_t digipot_register_write();

esp_err_t digipot_register_read();

esp_err_t digipot_soft_reset();
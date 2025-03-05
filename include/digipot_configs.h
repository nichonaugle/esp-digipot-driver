#include "esp_digipot_driver.h"

// Lookup table mapping digipot types to their configurations
const digipot_handle_t digipot_config_table[] = {
    [AD5246] = {
        .device_name = "AD5246 - Analog Devices",
        .i2c_port = NULL,        // Leave null, defined in init function
        .dev_cfg = NULL,         // Leave null, defined in init function
        .i2c_address = 0x2C,
        .wiper_reg = 0x00,
        .max_position = 255,
        .min_position = 0,
        .wiper_bit_count = 8,
        .soft_reset_cmd = 0x80,
        .transaction_timeout_ms = 100
    }
};

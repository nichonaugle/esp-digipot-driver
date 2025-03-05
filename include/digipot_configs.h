#include "esp_digipot_driver.h"

// Lookup table mapping digipot types to their configurations
const digipot_handle_t digipot_config_table[] = {
    [AD5246] = {
        .device_name = "AD5246 - Analog Devices",   // MUST not exceed 23 characters, as one is reserved for the null terminator
        .i2c_port = 0,                              // Leave 0, defined in init function
        .dev_cfg = {0},                             // Initialize to zero, will be set in init function
        .dev_handle = NULL,                         // Leave null, defined in init function
        .i2c_address = 0x2C,
        .wiper_reg = 0x00,
        .max_position = 255,                        // Inclusive of max
        .min_position = 0,                          // Inclusive of min
        .wiper_bit_count = 8,
        .soft_reset_cmd = 0x80,
        .transaction_timeout_ms = 100
    },
    [MCP4531] = {
        .device_name = "MCP4531 - Microchip",   // MUST not exceed 23 characters, as one is reserved for the null terminator
        .i2c_port = 0,                              // Leave 0, defined in init function
        .dev_cfg = {0},                             // Initialize to zero, will be set in init function
        .dev_handle = NULL,                         // Leave null, defined in init function
        .i2c_address = 0x2E,
        .wiper_reg = 0x00,
        .max_position = 127,                        // Inclusive of max
        .min_position = 0,                          // Inclusive of min
        .wiper_bit_count = 7,
        .soft_reset_cmd = -1,
        .transaction_timeout_ms = 100
    }
};

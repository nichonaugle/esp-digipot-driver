#include "esp_digipot_driver.h"

/**
 * @file esp_digipot_driver.h
 * @brief Digital Potentiometer (Digipot) Driver Configuration Table
 *
 * This file contains a lookup table (`digipot_config_table`) that maps digipot types
 * (defined in the `digipot_type_t` enum) to their respective configurations. Each entry
 * in the table is a `digipot_handle_t` structure that defines the properties of a specific
 * digipot model.
 *
 * To add a new digipot type to the table:
 * 1. Add a new entry to the `digipot_type_t` enum in `esp_digipot_driver.h`.
 * 2. Add a corresponding entry to the `digipot_config_table` array below, following the
 *    format of existing entries.
 *
 * Example:
 * ```
 * typedef enum {
 *     AD5246,      // Analog Devices AD5246
 *     MCP4531,     // Microchip MCP4531
 *     NEW_DIGIPOT, // Add new digipot type here
 *     DIGIPOT_COUNT
 * } digipot_type_t;
 *
 * const digipot_handle_t digipot_config_table[] = {
 *     [AD5246] = {
 *         .device_name = "AD5246 - Analog Devices",
 *         .i2c_port = 0,
 *         .dev_cfg = {0},
 *         .dev_handle = NULL,
 *         .i2c_address = 0x2C,
 *         .wiper_reg = 0x00,
 *         .max_position = 255,
 *         .min_position = 0,
 *         .wiper_bit_count = 8,
 *         .soft_reset_cmd = 0x80,
 *         .transaction_timeout_ms = 100
 *     },
 *     [MCP4531] = {
 *         .device_name = "MCP4531 - Microchip",
 *         .i2c_port = 0,
 *         .dev_cfg = {0},
 *         .dev_handle = NULL,
 *         .i2c_address = 0x2E,
 *         .wiper_reg = 0x00,
 *         .max_position = 127,
 *         .min_position = 0,
 *         .wiper_bit_count = 7,
 *         .soft_reset_cmd = -1,
 *         .transaction_timeout_ms = 100
 *     },
 *     [NEW_DIGIPOT] = {
 *         .device_name = "New Digipot Model", // Must not exceed 32 characters
 *         .i2c_port = 0,                     // Leave 0, defined in init function
 *         .dev_cfg = {0},                    // Initialize to zero, set in init function
 *         .dev_handle = NULL,                // Leave null, defined in init function
 *         .i2c_address = 0xXX,               // Set I2C address for the new digipot
 *         .wiper_reg = 0xXX,                 // Set wiper register address
 *         .max_position = XXX,               // Set maximum wiper position (inclusive)
 *         .min_position = 0,                 // Set minimum wiper position (inclusive)
 *         .wiper_bit_count = X,              // Set bit resolution (e.g., 7 or 8 bits)
 *         .soft_reset_cmd = 0xXX,            // Set soft reset command (or -1 if unsupported)
 *         .transaction_timeout_ms = 100       // Set I2C transaction timeout in milliseconds
 *     }
 * };
 * ```
 *
 * Notes:
 * - The `device_name` field must not exceed 23 characters (including the null terminator).
 * - The `i2c_port`, `dev_cfg`, and `dev_handle` fields will be set during
 *   the `digipot_init` function.
 * - The `soft_reset_cmd` field should be set to `-1` if the digipot does not support
 *   a soft reset command.
 * - Ensure the `digipot_type_t` enum and `digipot_config_table` array are kept in sync.
 */
const digipot_handle_t digipot_config_table[] = {
    [AD5246] = {
        .device_name = "AD5246 - Analog Devices",   // MUST not exceed 23 characters
        .i2c_port = 0,                              // Leave 0, defined in init function
        .dev_cfg = {0},                             // Initialize to zero, set in init function
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
        .device_name = "MCP4531 - Microchip",   // MUST not exceed 23 characters
        .i2c_port = 0,                              // Leave 0, defined in init function
        .dev_cfg = {0},                             // Initialize to zero, set in init function
        .dev_handle = NULL,                         // Leave null, defined in init function
        .i2c_address = 0x2E,
        .wiper_reg = 0x00,
        .max_position = 127,                        // Inclusive of max
        .min_position = 0,                          // Inclusive of min
        .wiper_bit_count = 7,
        .soft_reset_cmd = -1,                       // -1 indicates no soft reset support
        .transaction_timeout_ms = 100
    }
    // Add new digipot configurations here
};

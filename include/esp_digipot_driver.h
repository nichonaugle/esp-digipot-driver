#ifndef ESP_DIGIPOT_DRIVER_H
#define ESP_DIGIPOT_DRIVER_H

#include "esp_err.h"
#include "driver/i2c_master.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Structure representing a digital potentiometer (digipot) handle.
 */
typedef struct {
    char device_name[32];              // Max of 32 characters, including null terminator
    i2c_port_t i2c_port;               // I2C port number
    i2c_device_config_t dev_cfg;       // I2C device configuration
    i2c_master_dev_handle_t dev_handle; // I2C device handle
    uint8_t i2c_address;               // I2C address of the digipot
    uint8_t wiper_reg;                 // Register address for the wiper position
    uint8_t max_position;              // Maximum position of the digipot
    uint8_t min_position;              // Minimum position of the digipot
    uint8_t wiper_bit_count;           // Bit resolution of the wiper (typically 7 or 8 bits)
    int16_t soft_reset_cmd;            // Command for soft reset (use -1 if not supported)
    uint32_t transaction_timeout_ms;   // Timeout for I2C transactions in milliseconds
} digipot_handle_t;

/**
 * @brief Enumeration of supported digital potentiometer types.
 */
typedef enum {
    AD5246,    // Analog Devices AD5246 digipot
    MCP4531,   // Microchip MCP4531 digipot
    /* Add more variants here if needed */
    DIGIPOT_COUNT // Total number of supported digipot types
} digipot_type_t;

/**
 * @brief Initialize a digital potentiometer.
 *
 * @param digipot_handle Pointer to the digipot handle structure.
 * @param bus_handle Handle to the I2C master bus.
 * @param digipot_type Type of the digital potentiometer.
 * @param clock_speed I2C clock speed in Hz.
 * @return esp_err_t ESP_OK on success, otherwise an error code.
 */
esp_err_t digipot_init(digipot_handle_t *digipot_handle, i2c_master_bus_handle_t bus_handle, digipot_type_t digipot_type, size_t clock_speed);

/**
 * @brief Set the wiper position of the digital potentiometer.
 *
 * @param val Desired wiper position (0 to max_position).
 * @param digipot_handle Pointer to the digipot handle structure.
 * @return esp_err_t ESP_OK on success, otherwise an error code.
 */
esp_err_t digipot_set_wiper_position(uint8_t val, digipot_handle_t *digipot_handle);

/**
 * @brief Read a register from the digital potentiometer.
 *
 * @param reg_to_read Register address to read from.
 * @param rx_buf Buffer to store the read data.
 * @param rx_buf_size Size of the receive buffer.
 * @param digipot_handle Pointer to the digipot handle structure.
 * @return esp_err_t ESP_OK on success, otherwise an error code.
 */
esp_err_t digipot_register_read(uint8_t reg_to_read, uint8_t *rx_buf, uint8_t rx_buf_size, digipot_handle_t *digipot_handle);

/**
 * @brief Write to a register of the digital potentiometer.
 *
 * @param tx_buf Buffer containing the data to write.
 * @param tx_buf_size Size of the transmit buffer.
 * @param digipot_handle Pointer to the digipot handle structure.
 * @return esp_err_t ESP_OK on success, otherwise an error code.
 */
esp_err_t digipot_register_write(uint8_t *tx_buf, uint8_t tx_buf_size, digipot_handle_t *digipot_handle);

/**
 * @brief Perform a soft reset of the digital potentiometer.
 *
 * @param digipot_handle Pointer to the digipot handle structure.
 * @return esp_err_t ESP_OK on success, otherwise an error code.
 */
esp_err_t digipot_soft_reset(digipot_handle_t *digipot_handle);

/**
 * @brief Deinitialize the digital potentiometer and release resources.
 *
 * @param digipot_handle Pointer to the digipot handle structure.
 * @return esp_err_t ESP_OK on success, otherwise an error code.
 */
esp_err_t digipot_deinit(digipot_handle_t *digipot_handle);

#ifdef __cplusplus
}
#endif

#endif //ESP_DIGIPOT_DRIVER_H
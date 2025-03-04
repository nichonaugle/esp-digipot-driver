#include "esp_err.h"
#include "esp_digipot_driver.h"
#include "driver/i2c.h"

typedef struct {
    i2c_port_t i2c_port;  // I2C port number
    uint8_t i2c_address;  // I2C address of the digipot
    uint8_t max_position; // Max position of the digipot
    uint32_t min_position; // Min position of the digipot
    uint8_t wiper_bit_count; // Bit resolution of the wiper, typically 7 or 8 bits
    uint8_t soft_reset_cmd;
} digipot_handle_t;

esp_err_t digipot_init(digipot_handle_t *digipot_handle);

esp_err_t digipot_set_wiper_position(uint8_t val, digipot_handle_t *digipot_handle);

esp_err_t digipot_register_read(uint8_t *rx_buf, uint8_t rx_buf_size, digipot_handle_t *digipot_handle);

esp_err_t digipot_register_write(uint8_t *tx_buf, uint8_t tx_buf_size, digipot_handle_t *digipot_handle);

esp_err_t digipot_soft_reset(digipot_handle_t *digipot_handle);
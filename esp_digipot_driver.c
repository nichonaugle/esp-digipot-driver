#include <stdio.h>
#include "esp_digipot_driver.h"
#include "esp_err.h"

static const char* TAG = "digipot-driver"

esp_err_t digipot_init(digipot_handle_t *digipot_handle) {
    if (digipot_handle == NULL) {
        ESP_LOGE(TAG, "Digipot handle improperly initialized!")
    }

    /* TODO: Add in initialization support for a soft reset */
    esp_err_t err;

    err = ESP_OK

    return err;
}

esp_err_t digipot_set_wiper_position(uint8_t val, digipot_handle_t *digipot_handle) {
    if (val > digipot_handle->max_position || val < digipot_handle.min_position) {
        ESP_LOGE(TAG, 
                "Provided value %d falls outside of the min and max range defined in the digipot handle (%d < your value < %d)",
                val,
                digipot_handle->min_position,
                digipot_handle->max_position);
        return ESP_INVALID_ARG;
    }
    
    /* TODO: Add in logic to set the register properly */
    if (digipot_register_write() != ESP_OK) {
        ESP_LOGE(TAG, "Writing to register failed!")
        return ESP_ERR_INVALID_RESPONSE;
    }
    return ESP_OK;
}

esp_err_t digipot_register_write(uint8_t *tx_buf, uint8_t tx_buf_size, digipot_handle_t *digipot_handle) {

    /* TODO: Add in logic to set the register properly, given an array of 8 bit values */
    esp_err_t err;

    err = ESP_OK

    return err;
}

esp_err_t digipot_register_read(uint8_t *rx_buf, uint8_t rx_buf_size, digipot_handle_t *digipot_handle) {

    /* TODO: Add in logic to read the register properly into an array, ensuring that it doesnt overflow given the size */
    esp_err_t err;

    err = ESP_OK

    return err;
}

esp_err_t digipot_soft_reset(digipot_handle_t *digipot_handle) {

    /* TODO: Add in logic to soft reset the register properly. Use the reset command from the struct so it can be ported to different devices */
    esp_err_t err;

    err = ESP_OK

    return err;
}
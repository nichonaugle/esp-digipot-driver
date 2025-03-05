# ESP Digipot Driver
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![GitHub Release](https://img.shields.io/github/v/release/nichonaugle/esp-digipot-driver)](https://github.com/nichonaugle/esp-digipot-driver/releases)
[![Downloads](https://img.shields.io/github/downloads/nichonaugle/esp-digipot-driver/total)](https://github.com/nichonaugle/esp-digipot-driver/releases)
[![Contributors](https://img.shields.io/github/contributors/nichonaugle/esp-digipot-driver)](https://github.com/nichonaugle/esp-digipot-driver/graphs/contributors)

The ESP Digipot Driver is a C-based library for interfacing with digital potentiometers (digipots) using the ESP32 microcontroller. It streamlines addition, initialization and helps with basic device controls. 

## State
Currently, this driver supports the following digipots:

![AD5246](https://img.shields.io/badge/Analog_Devices-AD5246-green)
![MCP4531](https://img.shields.io/badge/Microchip-MCP4531-green)

We are working on adding this to the esp-idf component registry, where any additional updates can be pushes and made avaliable to everyone easily!

## Installation

1. Clone the repository:
```
git clone https://github.com/nichonaugle/esp-digipot-driver.git
```
2. Include the driver files in your project:
   - `esp_digipot_driver.h`
   - `esp_digipot_configs.h`

## Usage

1. Initialize the digipot:
```c
digipot_handle_t digipot_handle;
digipot_init(&digipot_handle, master_i2c_bus_handle, SELECTED_DIGIPOT, DESIRED_OPERATION_FREQUENCY)
```

2. Set the wiper position:
```c
digipot_set_wiper_position(wiper_value, &digipot)
```

3. Deinitialize the digipot:
```c
digipot_deinit(&digipot)
```

## Adding a New Digipot Configuration
To add support for a new digital potentiometer (digipot) to the driver, follow these steps:

1. Add a New Entry to the digipot_type_t Enum

Open the esp_digipot_driver.h file and add a new entry to the digipot_type_t enum. For example:

```c
typedef enum {
    AD5246,      // Analog Devices AD5246
    MCP4531,     // Microchip MCP4531
    NEW_DIGIPOT, // Add new digipot type here
    DIGIPOT_COUNT
} digipot_type_t;
```

Replace NEW_DIGIPOT with the name of your digipot model.

2. Add a New Entry to the digipot_config_table
In the same file, locate the digipot_config_table array and add a new entry for your digipot. Follow the format of existing entries. For example:

```c
const digipot_handle_t digipot_config_table[] = {
    [AD5246] = {
        .device_name = "AD5246 - Analog Devices",
        .i2c_port = 0,
        .dev_cfg = {0},
        .dev_handle = NULL,
        .i2c_address = 0x2C,
        .wiper_reg = 0x00,
        .max_position = 255,
        .min_position = 0,
        .wiper_bit_count = 8,
        .soft_reset_cmd = 0x80,
        .transaction_timeout_ms = 100
    },
    ........ (go to the bottom)

   [NEW_DIGIPOT] = {
        .device_name = "New Digipot Model", // Must not exceed 32 characters
        .i2c_port = 0,                     // Leave 0, defined in init function
        .dev_cfg = {0},                    // Initialize to zero, set in init function
        .dev_handle = NULL,                // Leave null, defined in init function
        .i2c_address = 0xXX,               // Set I2C address for the new digipot
        .wiper_reg = 0xXX,                 // Set wiper register address
        .max_position = XXX,               // Set maximum wiper position (inclusive)
        .min_position = 0,                 // Set minimum wiper position (inclusive)
        .wiper_bit_count = X,              // Set bit resolution (e.g., 7 or 8 bits)
        .soft_reset_cmd = 0xXX,            // Set soft reset command (or -1 if unsupported)
        .transaction_timeout_ms = 100       // Set I2C transaction timeout in milliseconds
    }
};
```
Replace the placeholders (NEW_DIGIPOT, 0xXX, XXX, etc.) with the appropriate values for your digipot.

**Notes**:

- device_name: Must not exceed 32 characters (including the null terminator).

- i2c_port, dev_cfg, dev_handle: Leave these fields as default values (0, {0}, NULL). They will be set during the digipot_init function.

- soft_reset_cmd: Set this to -1 if the digipot does not support a soft reset command.

- Sync Enum and Table: Ensure the digipot_type_t enum and digipot_config_table array are kept in sync.

### Example: Adding a New Digipot
Suppose you want to add support for a digipot with the following properties:

```
Name: XYZ123
I2C Address: 0x3A
Wiper Register: 0x01
Max Position: 128
Wiper Bit Count: 7
No Soft Reset Command
```
You would add the following entry:

```c
[XYZ123] = {
    .device_name = "XYZ123 - New Manufacturer",
    .i2c_port = 0,
    .dev_cfg = {0},
    .dev_handle = NULL,
    .i2c_address = 0x3A,
    .wiper_reg = 0x01,
    .max_position = 128,
    .min_position = 0,
    .wiper_bit_count = 7,
    .soft_reset_cmd = -1, // No soft reset support
    .transaction_timeout_ms = 100
}
```
Update the digipot_type_t Enum
Add the new digipot type to the digipot_type_t enum:

```c
typedef enum {
    AD5246,      // Analog Devices AD5246
    MCP4531,     // Microchip MCP4531
    XYZ123,      // New Manufacturer XYZ123
    DIGIPOT_COUNT
} digipot_type_t;
```

**Test Your Changes**

After adding the new digipot configuration, rebuild the project and test the driver with the new digipot to ensure it works as expected.

By following these steps, you can easily add support for new digipot models to the driver. If you encounter any issues, refer to the existing configurations or open an issue for assistance.


## API

The ESP Digipot Driver provides the following API functions:

- `digipot_init`: Initializes the digipot and adds it to the I2C bus.
- `digipot_set_wiper_position`: Sets the wiper position of the digipot.
- `digipot_register_read`: Reads from a specific register of the digipot.
- `digipot_register_write`: Writes to a specific register of the digipot.
- `digipot_soft_reset`: Performs a soft reset of the digipot.
- `digipot_deinit`: Removes the digipot from the I2C bus.

## Contributing

Contributions to the ESP Digipot Driver are welcome. Please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Implement your changes and ensure that the code passes all tests.
4. Submit a pull request with a detailed description of your changes.

## License

The ESP Digipot Driver is licensed under the [MIT License](LICENSE).

## Testing

To test a new ESP Digipot Driver, follow these steps:

1. Ensure that you have the necessary dependencies installed.
2. Navigate to the `examples/basic` project directory.
3. Test using your preferred ESP32 with the added digipot configuration.

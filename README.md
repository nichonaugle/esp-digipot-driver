# ESP Digipot Driver

The ESP Digipot Driver is a C-based library for interfacing with digital potentiometers (digipots) using the ESP32 microcontroller. It streamlines addition, initialization and helps with basic device controls. 

## State
Currently, this driver supports the following digipots:
[![AD5246](https://img.shields.io/badge/Analog_Devices-AD5246-green)]
[![MCP4531](https://img.shields.io/badge/Microchip-MCP4531-green)]

We are working on adding this to the esp-idf component registry, where any additional updates can be pushes and made avaliable to everyone easily!
[![GitHub Release](https://img.shields.io/github/v/release/nichonaugle/esp-digipot-driver)](https://github.com/nichonaugle/esp-digipot-driver/releases)
[![Downloads](https://img.shields.io/github/downloads/nichonaugle/esp-digipot-driver/total)](https://github.com/nichonaugle/esp-digipot-driver/releases)
[![Contributors](https://img.shields.io/github/contributors/nichonaugle/esp-digipot-driver)](https://github.com/nichonaugle/esp-digipot-driver/graphs/contributors)

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
2. Navigate to the `examples` directory.
3. Test using your preferred ESP32 with the added digipot configuration.
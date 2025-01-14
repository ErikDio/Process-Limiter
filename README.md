# Process Limiter

## Overview

Process Limiter is a Windows application designed to monitor and manage specific processes running on the system. It allows users to specify a target process and limit the number of instances of that process based on the number of screens (telas) available.

## Features

- Monitor a specified target process.
- Limit the number of instances of the target process.
- Debug mode for detailed logging.
- Configuration saved in a hidden and read-only `.cfg` file.

## Installation

1. Clone the repository to your local machine.
2. Open the project in your preferred C development environment.
3. Compile the project using a C compiler that supports Windows API.

## Usage

1. Run the compiled executable.
2. The program will prompt you to enter the number of screens (telas) and the target process name (e.g., `notepad.exe`).
3. The configuration will be saved in a hidden and read-only `config.cfg` file.
4. The program will start monitoring the specified process and limit its instances based on the number of screens.

### Command Line Arguments

- `-debug`: Enable debug mode for detailed logging.

## Example

```sh
prodemge_limiter.exe -debug
```

## Files

- `main.c`: Contains the main function and configuration handling.
- `gerenciador_processos.c`: Contains the process monitoring and management logic.
- `gerenciador_processos.h`: Header file for `gerenciador_processos.c`.

## Debug Mode

When debug mode is enabled, the console window will remain visible, and detailed logs will be printed to the console. This is useful for troubleshooting and verifying the program's behavior.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your changes.

## Contact

For any questions or issues, please open an issue on the GitHub repository.

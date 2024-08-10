# Android-Emulator-Hunter
Detect if the application is running on an emulator

## Features
- [x] Memory Scanning for x86 Libraries
- [x] Native check for application installer package using C++ and JNI
- [x] Lua Script Integration: Leverages Lua scripting for flexible and extensible emulator detection logic.

## Supported Emulators

| Emulator    | Supported |
|-------------|:---------:|
| BlueStacks  |     ✔️     |
| LDPlayer    |     ❌     |
| NoxPlayer   |     ❌     |
| MEMU Play   |     ❌     |
| Mumu Player |     ❌     |

## Lua Integration
The project integrates Lua to enable custom scripting for enhanced emulator detection. Lua scripts are embedded within the native C++ code, allowing for dynamic and flexible checks.
#### How Lua Is Used
- Script Execution: Lua scripts are executed from native C++ code to perform additional checks or customized logic for detecting emulators.
- Static Library: Lua is compiled as a static library (liblua.a) and linked with the project, providing a robust scripting environment

## Requirements
- Android NDK: Proper NDK configuration is required to compile and link the Lua library

## Acknowledgements
- This project uses the **[ELFPP](https://github.com/pinwhell/ELFPP)** library, which is licensed under the MIT License.

## Additional Resources
- Lua Documentation: For more information on Lua scripting and integration, refer to the **[Lua manual](https://www.lua.org/manual/)**.
- Contribution: Contributions to enhance emulator detection or support additional emulators are welcome. Please open an **[issue](https://github.com/ezsecurity-official/Android-Emulator-Hunter/issues/new)** or submit a **[pull request](https://github.com/ezsecurity-official/Android-Emulator-Hunter/pulls)**.

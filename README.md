# BadAPI
A Lua API for Grand Theft Auto V.
Strictly for educational purposes.

## How to use
1. Build the binary or download it from github CI
2. Download https://github.com/TupoyeMenu/BadAPI-Lua and install it as `Grand Theft Auto V/BadAPI/scripts/`
3. Download https://github.com/DurtyFree/gta-v-data-dumps/raw/refs/heads/master/vehicles.json into `Grand Theft Auto V/BadAPI/scripts_config`
4. Inject the binary into the game


###### Note: `Grand Theft Auto V` above is where `GTA5.exe` or `GTA5_Enhanced.exe` is located.

## Building

### Windows
To build BigBaseV2 you need:

* Visual Studio 2019 or higher
* [CMake](https://cmake.org/download)

To set up the build environment, run the following commands in a terminal:
```bash
git clone https://github.com/TupoyeMenu/BadAPI.git
cd BadAPI
mkdir build
cd build
cmake ..
```
Now, you will be able to open the solution, and simply build it in Visual Studio.

### GNU/Linux
To build BigBaseV2 you need:

* MinGW 12 or higher
* CMake
* Ninja? Didn't test make.

To set up the build environment, run the following commands in a terminal:
```bash
git clone https://github.com/TupoyeMenu/BadAPI.git
cd BadAPI
mkdir build && cd build
cmake .. -DCROSSCOMPILE:BOOL=TRUE -DUSE_GCC:BOOL=TRUE -G Ninja
ninja
```

## Credits
| Credits                                                    |                                                                                 |
| ---------------------------------------------------------- | ------------------------------------------------------------------------------- |
| Pocakking                                                  | [BigBaseV2](https://github.com/Pocakking/BigBaseV2)                             |
| spankerincrease(gir489)                                    | [BigBaseV2-fix](https://bitbucket.org/gir489/bigbasev2-fix)                     |
| [YimMenu](https://github.com/YimMenu/YimMenu) contributors | Updates for newer GTA V versions, Lua API, most of the code is stolen from them |
| tupoy-ya                                                   | Being stupid                                                                    |

## License
This project is licensed under [GNU GENERAL PUBLIC LICENSE Version 2](https://www.gnu.org/licenses/old-licenses/gpl-2.0.txt) because i stole a lot of code from YimMenu.

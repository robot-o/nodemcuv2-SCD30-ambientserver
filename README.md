
# nodemcuv2-SCD30 sensorserver
## About
This is a server providing information about ambient CO2, temperature and humidity built with a [Node MCU v2](https://www.seeedstudio.com/NodeMCU-v2-Lua-based-ESP8266-development-kit.html) and [SCD30 Sensor](http://wiki.seeedstudio.com/Grove-CO2_Temperature_Humidity_Sensor-SCD30/)
## Setup

1. Connect the Sensor on the following pins:  
**SCD30 -> nodeMCUv2**  
GND     -> GND  
VCC     ->  3V3  
SDA     -> D2  
SCL     -> D1  

2. Hook up the nodeMCUv2 via usb to your pc
3. Make sure you have platformio installed (see [here](#how-to-build-platformio-based-project))
4. enter the `altitude`, `ssid`, `password` and `deviceName` variables in [Server.cpp](src/Server.cpp)
5. run `platformio run --target upload` or use the [vscode task](#vscode-platformio-ide)
6. profit!

## Usage
do a GET request to your servers IP (which you can find out via serial: `platformio device list` and then `platformio device monitor`)
you will recieve a `application/json` response which looks like this:
```
$ curl -s 192.168.2.209
{
  "node": "co2node-1",
  "co2": 801,
  "temperature": 27.00008,
  "humidity": 40.42664
}
```
## Development
### vscode Platformio IDE
i recommend getting the [Platformio IDE extension for vscode](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) otherwise you can do everything manually
### How 2 Platformio Manually

1. Install [PlatformIO Core](http://docs.platformio.org/page/core.html)
2. Download [development platform with examples](https://github.com/platformio/platform-espressif8266/archive/develop.zip)
3. Extract ZIP archive
4. Run these commands:

```
# Build project
> platformio run

# Upload firmware
> platformio run --target upload

# Clean build files
> platformio run --target clean
```
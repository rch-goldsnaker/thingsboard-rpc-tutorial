## <a name="introduction">💻 Thingsboard RPC tutorial | with ESP32</a>

<img src="https://github.com/rch-goldsnaker/thingsboard-rpc-tutorial/blob/main//banner.png" alt="Project Banner">

## 📋 <a name="table">Table of Contents</a>

1. 🤖 [Introduction](#introduction)
2. ⚙️ [Tech Stack](#tech-stack)
3. 🔋 [Features](#features)
4. 💻 [Youtube tutorial](#youtube)
5. 🤸 [Quick Start](#quick-start)
   
## <a name="introduction">🤖 Introduction</a>

This repository is designed to offer a quick guide on RPC (Remote Procedure Calls) for ThingsBoard. Inside, you'll find code for programming an ESP32 and a simple Node.js app. The Node.js app communicates with the ThingsBoard API and uses RPC services.

Reference Link:

- [Thingsboard client sdk](https://github.com/thingsboard/thingsboard-client-sdk/tree/master/examples/0013-esp8266_esp32_request_rpc)
- [Thingsboard Rpc Guide](https://thingsboard.io/docs/user-guide/rpc)
- [Thingsboard Client side Rpc API](https://thingsboard.io/docs/reference/http-api/#rpc-api)
- [Thingsboard Server side Rpc API](https://thingsboard.cloud/swagger-ui/#/rpc-v-2-controller)

## <a name="tech-stack">⚙️ Tech Stack</a>

💎 ESP32 

💎 NodeJs

💎 Thingsboard

## <a name="features">🔋 Features</a>

👉 ESP32 Connection

👉 Receiving RPC Data

👉 Sending RPC Data

## <a name="youtube">🎬 Youtube tutorial</a>

See tutorial video [here](https://youtu.be/xZoeJ-osS3g)

## <a name="quick-start">🤸 Quick Start</a>

Follow these steps to set up the project locally on your machine.

**Prerequisites**

Make sure you have the following installed on your machine:

- [Git](https://git-scm.com/)
- [Arduino IDE](https://www.arduino.cc/en/software)

For Esp32 install library:
- [ArduinoMqttClient](https://www.arduinolibraries.info/libraries/arduino-mqtt-client)
- [ThingsBoard](https://www.arduinolibraries.info/libraries/things-board)

For NodeJs App, install Node.js>= 12
- [Node](https://nodejs.org/en/download/package-manager/current)


**Cloning the Repository**

```bash
git clone https://github.com/rch-goldsnaker/thingsboard-rpc-tutorial
cd thingsboard-rpc-tutorial
```

**For Node Js App**

Create a .env file inside NodeJs folder.

**Installation**

Go to NodeJs folder and install the project dependencies using npm:

```bash
npm install
```

**Set Up Environment Variables**

Create a new file named .env inside of NodeJs folder and add the following content:

```env
TB_API_URL=https://thingsboard.cloud
TB_USERNAME=your@mail.com
TB_PASSWORD=yourPass
```

**Running the Project**

```bash
npm run start
```

**For Esp 32**

Copy the code to Arduino IDE | Wokwi | Platformio and Upload

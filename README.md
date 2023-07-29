**README - ESP32 Sensor Data Logger with Notecard**

This repository contains code for an ESP32-based sensor data logger that communicates with the Notecard service. The ESP32 is connected to an Adafruit MPU6050 accelerometer and a Notecard module to log sensor data and send it to the cloud using the Notecard API.

**Hardware Requirements:**

1. ESP32 development board
2. Adafruit MPU6050 accelerometer
3. Notecard module

**Libraries Used:**

1. Notecard.h - Library for interfacing with the Notecard module and API.
2. NotecardPseudoSensor.h - Library for handling Notecard pseudo-sensor features.
3. Adafruit_MPU6050.h - Library for interfacing with the MPU6050 accelerometer.
4. Adafruit_Sensor.h - Common sensor library required by the MPU6050 library.
5. Wire.h - Required for I2C communication with the MPU6050.

**Setup Instructions:**

1. Connect the MPU6050 to the ESP32 using the appropriate I2C pins.
2. Connect the Notecard module to the ESP32 using the specified UART pins (usbSerial for debugging and txRxPinsSerial for Notecard communication).
3. Make sure you have all the required libraries installed.
4. Modify the `NOTE_PRODUCT_UID` macro to match your Notecard product UID.
5. Upload the code to your ESP32 using the Arduino IDE or a compatible platform.

**Functionality:**

1. The setup function initializes the MPU6050 and Notecard module. It also sets the accelerometer and gyro range, as well as the filter bandwidth for the MPU6050.
2. It sends a command to the Notecard to set the product UID and enable continuous mode for data transmission.
3. The setup function also adds a Twilio message to the Notecard queue to be sent to the cloud later.
4. The loop function reads sensor data from the MPU6050 (temperature, humidity, etc.), formats it as JSON, and sends it to the Notecard.
5. The loop function then waits for the Notecard to respond and prints the response to the Serial monitor.
6. After a delay of 5 seconds, the loop function repeats the process.

**Note:**

1. Make sure you have set up your Notecard account and obtained the required credentials (API key, product UID, etc.).
2. Modify the JSON request in the loop function to match the data you want to log and send to the cloud.

**Important:**

Ensure that you have read and understood the licensing terms for the libraries and code used in this project before using it in your applications.

**Disclaimer:**

This code is provided as-is and without any warranty. The developer is not responsible for any damage or loss caused by the use of this code or related hardware. Use it at your own risk.

**Credits:**

The code in this repository is written by [Your Name]. It utilizes the following libraries and hardware components:

- [List of libraries used with their authors/creators]
- [Adafruit Industries](https://www.adafruit.com/) for the MPU6050 sensor.

# esp8266-wifi-motor-control-via-keyboard

This project showcases a simple yet powerful motor control system using the ESP8266 microcontroller. Leveraging Wi-Fi connectivity, the ESP8266 creates a web server that allows you to control the motor's direction and speed via keyboard input.

## How to Use:

1. Connect the ESP8266 to your Wi-Fi network.
2. Access the web interface and use keyboard commands (press 'w' for forward and release to stop, also press 's' to stop) to control the motor.
3. Explore the codebase to understand and customize the functionality for your unique applications.

## Hardware Setup:

- Motor Driver: L298N
  - Connect the motor pins to L298N out3 and out4.

- ESP8266 Connections to L298N:
  - D1 to L298N in3
  - D2 to L298N in4
  - D3 to L298N enb

## Dependencies:

- ESP8266WiFi library
- ESP8266WebServer library

## Getting Started:

- Clone or download the repository.
- Set up your Arduino IDE with the required libraries.
- Upload the code to your ESP8266 board.
- Connect the L298N motor driver and power up the system.
- Access the web interface and start controlling the motor wirelessly!

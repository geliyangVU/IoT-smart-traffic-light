# IoT-smart-traffic-light

Repository for documentations of IoT final project

# Smart traffic light systems - final project set up tutorial
Other iot setup tutorials can be found: https://github.com/geliyangVU/VU_FALL22_IOT_CLASS

# Domain of application: Smart city

In this tutorial we will setup and test a smart traffic light systems.

## Hardware Prerequistes

- My laptop is a MacBook air M1 2020 version.
- Adapter: Belkin USB C Hub, 5-in-1 MultiPort Adapter Dock.
- Microcontroller: ESP32-WROVER_DEV
- 1 GJD1602-IIC LCD display
- 1 HC-SR04 Ultrasonic sensor
- 1 Green Led
- 1 Red led
- 2 1k ohms resistor
- 3 Jumper wires
- 12 Jumper wire M/F
- Breadboard from ESP32 kit

## Software Prerequistes#

- IDE: The Arduino IDE version 2.0.3
- Mosquitto MQTT Broker
- MySQL server

### Architecture diagram

![Flow chart for iot final project (1)](https://user-images.githubusercontent.com/97559266/206766726-c0631c2d-4989-44ec-af74-d7007cf4015d.png)

### Circuit Diagram for ultrasonic sensor and LCD display

reference [Freenove tutorial]

<img width="659" alt="Screenshot 2022-12-09 at 1 19 52 PM" src="https://user-images.githubusercontent.com/97559266/206767548-f216ead9-e23c-49ca-996b-65813a5942fc.png">
<img width="658" alt="Screenshot 2022-12-09 at 1 18 43 PM" src="https://user-images.githubusercontent.com/97559266/206767561-d4e1096c-a011-46cd-bec8-e3a471e8c87d.png">

### Software snippet for ultrasonic sensor and LCD display

<img width="665" alt="Screenshot 2022-12-09 at 1 19 18 PM" src="https://user-images.githubusercontent.com/97559266/206767627-221ba838-a0a3-4243-a6b7-0f82ef82ad5b.png">
<img width="666" alt="Screenshot 2022-12-09 at 1 19 34 PM" src="https://user-images.githubusercontent.com/97559266/206767629-857c03a1-6d7c-4171-b9e4-0b29bc4f10cc.png">

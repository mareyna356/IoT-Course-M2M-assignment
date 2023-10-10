# IoT-Course-M2M-assignment
My final team assignment for my Internet of Things course from my December 2021 - January 2022 inter-semester at the Autonomous University of Baja California: a small Mosquitto-based M2M network. This assignment was developed by a 2-person team composed of myself and my classmate [LesliePVidal](https://github.com/LesliePVidal).

The network consists of:
- A remote MQTT broker hosted online by our professor; our professor provided us the broker's address.
- A BeagleBone Black with a KY-013 temperature sensor. The BeagleBone executes a Python script to obtain raw temperature readings from the sensor and publish them to the broker.
- A laptop that executes a Python script to subscribe to the remote broker to receive the temperature readings from the BeagleBone and upload the readings to a MySQL database.
- An Arduino Uno with an Ethernet shield, which receives raw sound readings from a KY-037 sensor and position readings of the Y-axis of a KY-023 joystick and publishes both readings to the broker. The Arduino also subscribes to the broker to receive the X-axis readings from the ESP8266 and turns on an LED whenever it receives a reading.
- A NodeMCU ESP8266, which receives position readings of the X-axis of the KY-023 joystick and publishes them to the broker. The ESP8266 also subscribes to the broker to receive the Arduino's Y-axis position and sound readings; it also turns on one of two LEDs connected to it depending on the type of reading received: one LED turns on when the ESP8266 receives a Y-axis position reading, and the other LED turns on when the ESP8266 receives a sound reading.
- A mobile phone with the [MQTT Dash](https://play.google.com/store/apps/details?id=net.routix.mqttdash) app installed. Using the app, the mobile phone subscribes to the broker to receive the readings from all the aforementioned sensors (the KY-013, the KY-037 and both axes of the KY-023).



# IoT-Course-M2M-assignment
My final team assignment for my Internet of Things course from my December 2021 - January 2022 inter-semester at the Autonomous University of Baja California: a small Mosquitto-based M2M network. This assignment was developed by a 2-person team composed of myself and my classmate [LesliePVidal](https://github.com/LesliePVidal).

## Elements of the network
- A remote MQTT broker hosted online by our professor; our professor provided us the broker's address.
- A BeagleBone Black with Debian and a KY-013 temperature sensor. The BeagleBone executes a Python script to obtain raw temperature readings from the sensor and publish them to the broker.
- A Windows 10 laptop that executes a Python script to subscribe to the remote broker to receive the temperature readings from the BeagleBone and upload the readings to a MySQL database.
- An Arduino Uno with an Ethernet shield, which receives raw sound readings from a KY-037 sensor and position readings of the Y-axis of a KY-023 joystick and publishes both readings to the broker. The Arduino also subscribes to the broker to receive the X-axis readings from the ESP8266 and turns on an LED whenever it receives a reading.
- A NodeMCU ESP8266, which receives position readings of the X-axis of the KY-023 joystick and publishes them to the broker. The ESP8266 also subscribes to the broker to receive the Arduino's Y-axis position and sound readings; it also turns on one of two LEDs connected to it depending on the type of reading received: one LED turns on when the ESP8266 receives a Y-axis position reading, and the other LED turns on when the ESP8266 receives a sound reading.
- A mobile phone with the [MQTT Dash](https://play.google.com/store/apps/details?id=net.routix.mqttdash) app installed. Using the app, the mobile phone subscribes to the broker to receive the readings from all the aforementioned sensors (the KY-013, the KY-037 and both axes of the KY-023).

## My contributions
I was in charge of designing and building the circuit for the BeagleBone Black and the KY-013. The BeagleBone is powered by a Mini-B USB cable connected to a wall outlet and is connected to the internet through an Ethernet cable. The diagram I drew for the BeagleBone and KY-013 circuit can be seen below:  
![BeagleBone Black and KY-013 circuit diagram](https://github.com/mareyna356/IoT-Course-M2M-assignment/assets/116867368/8b300e2b-8f2b-47da-9f64-5a56318c4cea)

The KY-013 is powered by the BeagleBone's 5V output from its SYS 5V pin (pin 7). The KY-013's signal (S) pin is connected to the BeagleBone's AIN3 pin (pin 38) through a voltage divider that lowers the KY-013's maximum reading from 5V to 1.563V. The voltage divider, made up of a 1kΩ resistor and a 2.2kΩ resistor, is necessary to not damage the BeagleBone's analog pin, which can only take voltages of up to 1.8V. Finally, the KY-013's negative pin is connected to the BeagleBone's DGND pin (pin 1). The completed circuit can be seen below:  
![BeagleBone Black and KY-013 circuit](https://github.com/mareyna356/IoT-Course-M2M-assignment/assets/116867368/69afb692-b91a-4791-9521-51758714bb43)  

I also wrote the Python script for the BeagleBone: [cliente_beaglebone.py](cliente_beaglebone.py). In this script, first the BeagleBone connects to the remote broker with a specific username and password, then every 10 seconds takes a raw temperature reading from the KY-013 through the AIN3 pin and publishes it to the broker under the topic named "AIN3". The script also prints the readings on the console. The username, password and address of the broker can be modified in lines 13 - 15. An example of the script's output can be seen below:  
![BeagleBone Black output](https://github.com/mareyna356/IoT-Course-M2M-assignment/assets/116867368/98e633fd-1aa6-4510-a63e-95a2b2ebd52a)

It was also my responsibility to set up the MySQL server in a laptop and to write the Python script for the laptop: [cliente_laptop.py](cliente_laptop.py). In this script, the laptop connects to the local MySQL database named "iot" (the credentials for the connection can be modified in lines 18 - 21) and then it subscribes to the remote broker's topic named "AIN3", the same topic to which the BeagleBone publishes its temperature readings. Whenever the laptop receives a message from the "AIN3" topic (i.e., a temperature reading), it will print the message on the console and upload it to the local MySQL database's "actividad3" table. In MySQL, I created the "iot" database and the "actividad3" table; the table's columns can be seen below:  
!["actividad3" table](https://github.com/mareyna356/IoT-Course-M2M-assignment/assets/116867368/3ddccc4d-4ff9-44db-af11-e3d9faf9731b)
- "id" is an int primary key with auto increment.
- "tipo" is a text that shows the type of saved reading (for example: "temperature").
- "lectura" is a float that represents the actual value of the reading.
- "fecha" is a datetime with the default value of CURRENT_TIMESTAMP and represents the date and time of the saving of the reading.

An example of the script's output can be seen below:  
![Laptop output](https://github.com/mareyna356/IoT-Course-M2M-assignment/assets/116867368/879f8a06-dd86-46cd-967a-9811df8fca8e)

An example of stored readings in the MySQL table can be seen below (NOTE: the readings from `id = 77` onwards are the same readings that can be seen in the previous image):  
![Stored readings](https://github.com/mareyna356/IoT-Course-M2M-assignment/assets/116867368/1b66f6c7-9361-4781-82fa-c985e426a4ea)

Finally, I was also responsible for using **MQTT Dash** on my phone to get the readings of the 4 sensors. In the app, I created 4 text nodes and subscribed each one to each of the network's 4 topics. The result can be seen below:  
![MQTT Dash on my phone](https://github.com/mareyna356/IoT-Course-M2M-assignment/assets/116867368/6a8db6d5-1041-4839-a7e5-3bd181687bf1)

## LesliePVidal's contributions
LesliePVidal was responsible for designing and building the circuit for the Arduino Uno with Ethernet Shield, the ESP8266, the KY-037 and the KY-023. The Arduino is powered by a type B USB cable connected to a wall outlet. The ESP8266 is powered by a Micro USB cable connected to a wall outlet. The Arduino is connected to the internet through an Ethernet cable while the ESP8266 is connected to the internet wirelessly. The diagram for this circuit can be seen below:  
![Arduino and ESP circuit diagram](https://github.com/mareyna356/IoT-Course-M2M-assignment/assets/116867368/8eb7e0ab-64bd-44ee-bb5c-22375bab4222)

The KY-037 and KY-023 are both powered by the Arduino Uno through its 5V pin. The KY-037's signal (A0) pin is connected to the Arduino's A2 pin. The KY-023's X-axis (VRx) pin is connected to the ESP8266's A0 pin and the Y-axis (VRy) pin is connected to the Arduino's A1 pin. The Arduino's D3 pin and the ESP8266's D4 and D5 pins are each connected to an LED in series with a 510Ω resistor. The Arduino, ESP8266, KY-037 and KY-023 all share the same ground. The completed circuit can be seen below:  
<img src="https://github.com/mareyna356/IoT-Course-M2M-assignment/assets/116867368/b5dc0245-d8e5-4ed3-a74b-c73bfae10f35" width="600">

LesliePVidal also wrote the programs for the Arduino and the ESP8266. In the program for the Arduino, [mqtt_basicArduino.ino](mqtt_basicArduino.ino), the Arduino connects to the remote broker with a specific username and password (the broker's address, the username and password can be modified on lines 26 - 28) and subscribes to the topic named "puertoA0". When a message from that topic is received, the Arduino turns on the LED connected to its D3 pin and prints the message on the console. The Arduino also takes every 10 seconds a raw sound reading from the KY-037 through the A2 pin and a raw Y-axis reading from the KY-023 through the A1 pin, and publishes both readings to the broker under the topics named "puertoA2" and "puertoA1" respectively; it also prints both readings on the console. An example of the program's output can be seen below:  
![Arduino output](https://github.com/mareyna356/IoT-Course-M2M-assignment/assets/116867368/00796838-d962-4100-a94c-9158d084a849)

In the program for the ESP8266, [mqtt_esp8266.ino](mqtt_esp8266.ino), the ESP8266 connects to the internet using the specified ssid and password (both of which can be changed on lines 30 and 31) and then connects to the remote broker with a specific username and password (the broker's address, the username and password can be modified on lines 34 - 36). The ESP8266 then subscribes to the topics named "puertoA2" and "puertoA1". When a message from "puertoA2" is received, the ESP8266 turns on the LED connected to its D5 pin and prints the message on the console; when a message from "puertoA1" is received, the ESP8266 turns on the LED connected to its D4 pin and prints the message on the console. The ESP8266 also takes every 10 seconds a raw X-axis reading from the KY-023 through the A0 pin and publishes it to the broker under the topic named "puertoA0"; it also prints the reading on the console. An example of the program's output can be seen below:  
![ESP8266 output](https://github.com/mareyna356/IoT-Course-M2M-assignment/assets/116867368/03bd82fd-8078-4ed7-8e35-e69dbc1b0153)

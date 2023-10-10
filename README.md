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
I was in charge of designing and building the circuit for the BeagleBone Black and KY-013. The BeagleBone is powered by a Mini-B USB cable connected to a wall outlet and is connected to the internet through an Ethernet cable. The diagram I drew for the BeagleBone and KY-013 circuit can be seen below:  
![BeagleBone Black and KY-013 circuit diagram](https://github.com/mareyna356/IoT-Course-M2M-assignment/assets/116867368/8b300e2b-8f2b-47da-9f64-5a56318c4cea)

The KY-013 is powered by the BeagleBone's 5V output from its SYS 5V pin (pin 7). The KY-013's signal pin is connected to the BeagleBone's AIN3 pin (pin 38) through a voltage divider that lowers the KY-013's maximum reading from 5V to 1.563V. The voltage divider, made up of a 1kΩ resistor and a 2.2kΩ resistor, is necessary to not damage the BeagleBone's analog pin, which can only take voltages of up to 1.8V. Finally, the KY-013's negative pin is connected to the BeagleBone's DGND pin (pin 1). The completed circuit can be seen below:  
![BeagleBone Black and KY-013 circuit](https://github.com/mareyna356/IoT-Course-M2M-assignment/assets/116867368/69afb692-b91a-4791-9521-51758714bb43)  

I also wrote the Python script for the BeagleBone: [cliente_beaglebone.py](cliente_beaglebone.py). In this script, first the BeagleBone connects to the remote broker with a specific username and password, then every 10 seconds takes a raw temperature reading from the KY-013 through the AIN3 port and publishes it to the broker under the topic named "AIN3". The script also prints the readings on the console. The username, password and address of the broker can be modified by altering the variables named "username", "password" and "host", respectively (lines 13 - 15). An example of the script's output can be seen below:  
![BeagleBone Black output](https://github.com/mareyna356/IoT-Course-M2M-assignment/assets/116867368/98e633fd-1aa6-4510-a63e-95a2b2ebd52a)

It was also my responsibility to set up the MySQL server in a laptop and to write the Python script for the laptop: [cliente_laptop.py](cliente_laptop.py). In this script, the laptop connects to the local MySQL database named "iot" (the credentials for the connection can be modified in lines 18 - 21) and then it subscribes to the remote broker's topic named "AIN3", the same topic to which the BeagleBone publishes its temperature readings. Whenever the laptop receives a message from the "AIN3" topic (i.e., a temperature reading), it will print the message on the console and upload it to the local MySQL database's "actividad3" table. In MySQL, I created the "iot" database and the "actividad3" table; the table's fields can be seen below:  
!["actividad3" table](https://github.com/mareyna356/IoT-Course-M2M-assignment/assets/116867368/3ddccc4d-4ff9-44db-af11-e3d9faf9731b)
- "id" is an int primary key with auto increment.
- "tipo" is a text that shows the type of saved reading (for example: "temperature").
- "lectura" is a float that represents the actual value of the reading.
- "fecha" is a datetime with the default value of CURRENT_TIMESTAMP and represents the date and time of the saving of the reading.

An example of the script's output can be seen below:  
![Laptop output](https://github.com/mareyna356/IoT-Course-M2M-assignment/assets/116867368/879f8a06-dd86-46cd-967a-9811df8fca8e)


## LesliePVidal's contributions

/*
 Basic MQTT example

 This sketch demonstrates the basic capabilities of the library.
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
 
*/

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>


// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 100, 120);

// MQTT Broker
const char* mqtt_server = "host address";
const char* mqtt_username = "username";
const char* mqtt_password = "password";

//Puertos a usar y variables
int LED1 = 3, SENSOR1 = A1, SENSOR2 = A2;
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (100)
char datoSensor[MSG_BUFFER_SIZE];

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  //Suscripción del puerto del Arduino al puerto del ESP8266
  if(strcmp(topic, "puertoA0")==0){
     digitalWrite(LED1, HIGH);
  } 
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

EthernetClient ethClient;
PubSubClient client(ethClient);

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient",mqtt_username,mqtt_password)) {
      Serial.println("connected");
      // ... and resubscribe
      client.subscribe("puertoA0");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  pinMode(LED1, OUTPUT); 
  pinMode(SENSOR1, INPUT); 
  pinMode(SENSOR2, INPUT);
  Serial.begin(57600);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  Ethernet.begin(mac, ip);
  // Allow the hardware to sort itself out
  delay(1500);
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  unsigned long now = millis();
  if (now - lastMsg > 10000) {
    lastMsg = now;
    // Pub de los puertos A1 y A2
    int dato = analogRead(SENSOR1);
    snprintf (datoSensor, MSG_BUFFER_SIZE, "%1d", dato);
    Serial.print("Publish message PUERTOA1: ");
    Serial.println(datoSensor);
    client.publish("puertoA1", datoSensor);
    
    dato = analogRead(SENSOR2);
    snprintf (datoSensor, MSG_BUFFER_SIZE, "%1d", dato);
    Serial.print("Publish message PUERTOA2: ");
    Serial.println(datoSensor);
    client.publish("puertoA2",datoSensor);
  }
}

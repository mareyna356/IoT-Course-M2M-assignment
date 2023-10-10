import Adafruit_BBIO.ADC as ADC
import time
import paho.mqtt.client as mqtt

#Callback para la conexion MQTT
def al_conectar(cliente, datos_usuario, banderas, rc):
    print("Conectado - codigo de resultado: " + str(rc))

ADC.setup()
sensor_temp = "AIN3"

#Usuario, password y host del broker
username = "username"
password = "password"
host = "URL o IP"

cliente = mqtt.Client()
cliente.on_connect = al_conectar
cliente.username_pw_set(username, password)
cliente.connect(host, 1883, 60)

while 1:
    lectura = ADC.read(sensor_temp)
    print(lectura)
    cliente.publish(sensor_temp, lectura)
    time.sleep(10)
    

import paho.mqtt.client as mqtt
import mysql.connector

#Funciones de callback para MQTT
def al_conectar(cliente, datos_usuario, banderas, rc):
    print("Conectado - codigo de respuesta: " + str(rc))
    cliente.subscribe("AIN3")

def al_recibir(cliente, datos_usuario, msg):
    print(msg.payload)
    sql = ("INSERT INTO actividad3 (tipo, lectura) VALUES (\"" +
    "Temperatura\", " + msg.payload + ")")
    mycursor.execute(sql)
    mydb.commit()

#Conexion a MySQL
mydb = mysql.connector.connect(
    host="localhost",
    user="root",
    password="",
    database="iot",
)

mycursor = mydb.cursor()

print("start")

cliente = mqtt.Client()
cliente.on_connect = al_conectar
cliente.on_message = al_recibir

#Usuario, password y host del broker
username = "username"
password = "password"
host = "URL o IP"

cliente.username_pw_set(username, password)
cliente.connect(host, 1883, 60)
cliente.loop_forever()

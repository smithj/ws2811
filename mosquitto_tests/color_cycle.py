import paho.mqtt.client as mqtt #import the client1
import time


broker_address="10.2.1.1"
#broker_address="iot.eclipse.org" #use external broker


client = mqtt.Client("C1") #create new instance

client.connect(broker_address) #connect to broker

client.publish("lights/lightstrip1/brightness/set","64")   #publish

brightness = 64

while True:
    for x in range(360):
        print(x)

        print("{0:d},100,{1:d}".format(x, brightness))

        client.publish("lights/lightstrip1/hsv/set", "{0:d},100,{1:d}".format(x, brightness))

        time.sleep(.1)
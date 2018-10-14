#!/usr/bin/env python
import pika
import sys

credentials = pika.PlainCredentials('lights', 'lights')
connection = pika.BlockingConnection(pika.ConnectionParameters('10.2.1.1',5672,'/lights', credentials))
channel = connection.channel()


channel.queue_declare(queue='strip1')

channel.basic_publish(exchange='',
                      routing_key='strip1',
                      body=sys.argv[1])
print(" [x] Sent " , sys.argv[1])
connection.close()

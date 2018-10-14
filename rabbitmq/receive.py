#!/usr/bin/env python
import pika

credentials = pika.PlainCredentials('lights', 'lights')
connection = pika.BlockingConnection(pika.ConnectionParameters('10.2.1.1',5672,'/lights', credentials))
channel = connection.channel()


channel.queue_declare(queue='strip1')

def callback(ch, method, properties, body):
    print(" [x] Received %r" % body)

channel.basic_consume(callback,
                      queue='strip1',
                      no_ack=True)

print(' [*] Waiting for messages. To exit press CTRL+C')
channel.start_consuming()

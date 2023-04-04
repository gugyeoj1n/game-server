from socket import *
from _thread import *

HOST = '192.168.0.103'
PORT = 5000

client = socket(AF_INET, SOCK_STREAM)
client.connect((HOST, PORT))

def recv_data(client) :
    while True :
        data = client.recv(1024)
        print("MESSAGE ARRIVED !")
        print(">> ", data.decode())

start_new_thread(recv_data, (client, ))
print("CONNECTED TO SERVER !")

while True :
    msg = input('')
    client.send(msg.encode('utf-8'))

client.close()
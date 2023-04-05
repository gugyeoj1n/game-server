from socket import *
from _thread import *

HOST = input('TARGET IP ADDRESS >> ')
PORT = 9939

client = socket(AF_INET, SOCK_STREAM)
client.connect((HOST, PORT))

name_req = client.recv(1024)
print(name_req.decode('utf-8'))
nickname = input('')
client.send(nickname.encode('utf-8'))

def recv_data(client) :
    while True :
        data = client.recv(1024)
        print("----------------------------------------")
        print("MESSAGE ARRIVED !")
        print(data.decode('utf-8'))
        print("----------------------------------------")

start_new_thread(recv_data, (client, ))
print("CONNECTED TO SERVER !")

while True :
    msg = input('')
    if msg == 'exit' :
        break
    client.send(msg.encode('utf-8'))

client.close()
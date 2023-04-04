from socket import *

client = socket(AF_INET, SOCK_STREAM)
client.connect(('', 5000))
print('CONNECTED !')

while True :
    req = client.recv(1024)
    print("MESSAGE FROM SERVER !")
    print(req.decode('utf-8'))
    msg = input('YOUR RESPONSE : ')
    client.send(msg.encode('utf-8'))
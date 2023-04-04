from socket import *
import sys

try :
    server_sock = socket(AF_INET, SOCK_STREAM)
    server_sock.bind(('', 5000))
    server_sock.listen(5)

    print('! SOCKET GENERATED !')
except:
    print('FAILED TO CONNECT TO AF_INET (IPv4)')
    sys.exit()

connect_sock, addr = server_sock.accept()

print('SERVER SEND THE TEST MESSAGE.')
test_msg = 'THIS IS TEST MESSAGE FROM SERVER SOCKET.'
connect_sock.send(test_msg.encode('utf-8'))

print('\nNOW YOU CAN CHAT WITH CLIENT !\n--------------------------------\n')


while True :
    req = connect_sock.recv(1024)
    print(req.decode('utf-8'))
    msg = input('YOUR RESPONSE : ')
    connect_sock.send(msg.encode('utf-8'))
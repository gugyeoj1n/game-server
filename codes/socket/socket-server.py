from socket import *
from _thread import *

# ------------------------------------------------------------
# 클라이언트 연결 시 생성되는 스레드에서 실행
def threaded(client, addr) :
    print("CLIENT CONNECTED -> ", addr[0], ":", addr[1])
    
    # 이름 받기
    client.send("WHAT'S YOUR NAME ? >> ".encode('utf-8'))
    name = client.recv(1024).decode('utf-8')
    client.send("NOW YOU CAN CHAT !!".encode('utf-8'))

    while True:
        try:
            data = client.recv(1024)
            if not data :
                print("CLIENT DISCONNECTED -> ", addr[0], ":", addr[1])
                break
        
            print("MESSAGE FROM [", name, "]")
            print(">> ", data.decode('utf-8'))

            # 접속된 클라이언트들에게 재전송
            for cl in clients :
                if cl != client :
                    cl.send(f"[ {name} ] >> ".encode('utf-8'))
                    cl.send(data)
        except ConnectionResetError as e :
            print("CLIENT DISCONNECTED -> ", addr[0], ":", addr[1])
            break
    
    if client in clients :
        clients.remove(client)
    
    client.close()

# ------------------------------------------------------------

clients = []

# 현재 IP 주소 가져오기
HOST = gethostbyname(gethostname())
PORT = 9939

# ------------------------------------------------------------
# 서버 소켓 생성
with socket(AF_INET, SOCK_STREAM) as server :
    server.bind((HOST, PORT))
    server.listen()
    print("! SOCKET GENERATED !")

    try :
        while True :
            client, addr = server.accept()
            clients.append(client)
            start_new_thread(threaded, (client, addr))
    except Exception as e:
        print("ERROR : ", e)
    finally :
        server.close()
# ------------------------------------------------------------
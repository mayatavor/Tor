import socket, threading
class ClientThread(threading.Thread):
    def __init__(self,clientAddress,clientsocket):
        threading.Thread.__init__(self)
        self.csocket = clientsocket
        print ("New connection added: ", clientAddress)
    def run(self):
        print ("Connection from : ", clientAddress)
        #self.csocket.send(bytes("Hi, This is from Server..",'utf-8'))
        msg = 'hi::::127.0.0.1::::8880::::127.0.0.1::::8882'
        #while True:
            # data = self.csocket.recv(2048)
            # msg = data.decode()
            # if msg=='bye':
            #   break
            # print ("from client", msg)
        print("check")
        self.csocket.send(bytes(msg,'UTF-8'))
        print("check after sending")
        print ("Client at ", clientAddress , " disconnected...")


def sentToNextClient(ip, port, msg):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((ip, int(port)))

    client.send(msg.encode())

    client.close()

LOCALHOST = "127.0.0.1"
PORT = 8080
clientAddress = ""

def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((LOCALHOST, PORT))
    print("Server started")
    print("Waiting for client request...")
    sentToNextClient(LOCALHOST, 8881, 'hi::::127.0.0.1::::8881::::127.0.0.1::::8882')
    while True:
        server.listen(1)
        clientsock, clientAddress = server.accept()
        newThread = ClientThread(clientAddress, clientsock)
        newThread.start()

if __name__ == "__main__":
    main()


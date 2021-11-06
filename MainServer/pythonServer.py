import socket, threading
from ClientThread import  ClientThread

LOCALHOST = "127.0.0.1"
FIRST_PORT = "9876"
SECOND_PORT = "8081"
LISTEN_PORT = 5678

SPACER = "::::"


# class ClientThread(threading.Thread):
# 
#     def __init__(self, clientAddress, clientsocket):
#         threading.Thread.__init__(self)
#         self.csocket = clientsocket
#         self.clientAddress = clientAddress
#         print("New connection added: ", clientAddress)
# 
#     # def createMessageRoute(self, messageContent):
#     #     msg = messageContent + SPACER + LOCALHOST +FIRST_PORT + SPACER + LOCALHOST + SECOND_PORT
#     #     return  msg
# 
#     def run(self):
#         print("Connection from : ", self.clientAddress)
#         msg = ''
#         while True:
#             data = self.csocket.recv(2048)
#             msg = data.decode()
#             if msg=='bye':
#                break
#             print ("from client", msg)
#             self.csocket.send(bytes("main server received message "+ msg, 'UTF-8'))
#         #'hi::::127.0.0.1::::8881::::127.0.0.1::::8882'
#         #msg = self.createMessageRoute(messageContent=msg)
#             msg += SPACER + LOCALHOST + SPACER + FIRST_PORT + SPACER + LOCALHOST+ SPACER + SECOND_PORT
#             print("creates message + route = " + msg )
#             sentToNextClient(LOCALHOST, 8881, msg)
#         print("Client at ", self.clientAddress, " disconnected...")


def sentToNextClient(ip, port, msg):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((ip, int(port)))
    client.send(msg.encode())
    client.close()


# def main():
#     server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#     server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
#     server.bind((LOCALHOST, LISTEN_PORT))
#     print("Server started")
#     print("Waiting for client request...")
#
#
#     while True:
#         server.listen(1)
#         clientsock, clientAddress = server.accept()
#         print("client address = ", clientAddress)
#         newThread = ClientThread(clientAddress, clientsock)
#         newThread.start()
#
#         #sentToNextClient(LOCALHOST, 8881, 'hi::::127.0.0.1::::8881::::127.0.0.1::::8882')
#
# if __name__ == "__main__":
#     main()

def main():

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((LOCALHOST, LISTEN_PORT))
    print("Server started")
    print("Waiting for client request..")
    while True:
        server.listen(5)
        clientsock, clientAddress = server.accept()
        newthread = ClientThread(clientAddress, clientsock)
        newthread.start()

if __name__ == "__main__":
    main()



import socket, threading
LOCALHOST = "127.0.0.1"
FIRST_PORT = "9876"
SECOND_PORT = "8081"
LISTEN_PORT = 5678

SPACER = "::::"

class ClientThread(threading.Thread):

    def __init__(self, clientAddress, clientsocket):
        threading.Thread.__init__(self)
        self.csocket = clientsocket
        self.clientAddress = clientAddress
        print("New connection added: ", clientAddress)

    # def createMessageRoute(self, messageContent):
    #     msg = messageContent + SPACER + LOCALHOST +FIRST_PORT + SPACER + LOCALHOST + SECOND_PORT
    #     return  msg

    def run(self):
        print("Connection from : ", self.clientAddress)
        msg = ''
        while True:
            data = self.csocket.recv(2048)
            msg = data.decode()
            if msg=='bye':
               break
            print ("from client", msg)
            self.csocket.send(bytes("main server received message "+ msg, 'UTF-8'))
        #'hi::::127.0.0.1::::8881::::127.0.0.1::::8882'
        #msg = self.createMessageRoute(messageContent=msg)
            msg += SPACER + LOCALHOST + SPACER + FIRST_PORT + SPACER + LOCALHOST+ SPACER + SECOND_PORT
            print("creates message + route = " + msg )
            sendToFirstClient(LOCALHOST, 8881, msg)
        print("Client at ", self.clientAddress, " disconnected...")


def sendToFirstClient(ip, port, msg):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((ip, int(port)))
    client.send(msg.encode())
    client.close()

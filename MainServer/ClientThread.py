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
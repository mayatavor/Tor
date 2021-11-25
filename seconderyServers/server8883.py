import socket
import threading

HOST = '127.0.0.1'  # Standard loopback interface address
PORT = 8883         # Port to listen on
MY_ID = 3

MAIN_SERVER_PORT = 5678

def sentToNextClient(ip, port, msg):
    print("in sendtTONextClient, port = ", port, " ip = ", ip)
    print("message = ", msg)
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((ip, int(port)))

    client.send(msg.encode())

    client.close()


def thread(conn):
    while True:
        data = conn.recv(4096)
        if not data: break
        print(data)
        data = data.decode()
        list = data.split("::::")
        if len(list) < 3: break
        next_ip = list[-2]
        next_port = list[-1]
        print(next_ip + " and " + next_port)
        print(list[0])

        list.pop(-1)
        list.pop(-1)

        sentToNextClient(next_ip, next_port, "::::".join(list))
    conn.close()

def connectToMainServer(s):
    msg = "100" + len(MY_ID) + MY_ID
    s.send(msg.encode())


def main():
    serv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serv.bind((HOST, PORT))
    serv.listen()

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    host = "127.0.0.1" #loopback
    s.connect((host, MAIN_SERVER_PORT))

    connectToMainServer(s)

    while True:
        conn, addr = serv.accept()
        x = threading.Thread(target=thread, args=(conn,))
        x.start()

    print('client disconnected')
    serv.close()
    s.close()


if __name__ == "__main__":
    main()


import socket
import threading

HOST = '127.0.0.1'  # Standard loopback interface address
MY_PORT = 8884      # Port to listen on
MY_ID = 4

MAIN_SERVER_PORT = 5678

public_key = (7, 14039) # expontent, n
private_key = (3943, 142039) # d, n


def decode_RSA(msg):
    plain = ""

    for letter in msg:
        value = ord(letter)
        print(letter , ": ", value)

        plain_letter = (value**private_key[0]) % private_key[1]
        print(plain_letter)
        plain += chr(plain_letter)

    print(plain)
    return plain



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

"""
connects to the main server and sends the public key with the server id
"""
def connectToMainServer(s):
    msg = "100" + "~" + str(MY_ID) + "~" + str(public_key[0]) + "~" + str(public_key[1])
    msg = str(len(msg)).zfill(5) + msg
    s.send(msg.encode())

def main():
    serv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serv.bind((HOST, MY_PORT))
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


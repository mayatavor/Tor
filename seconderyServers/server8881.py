import socket
import threading
import struct

HOST = '127.0.0.1'  # Standard loopback interface address
MY_PORT = 8881      # Port to listen on
MY_ID = 1

MAIN_SERVER_PORT = 5678


#private_key = (8023, 14279) # d, n
public_key = (3, 3127) # expontent, n
private_key = (2011, 3127) # d, n


def decode_RSA(msg):
    plain = ""

    for letter in msg:
        value = ord(letter)

        print(letter , ": ", value)

        plain_letter = ((value**private_key[0]) % private_key[1])
        print("plain_letter", plain_letter)
        print("chr ", chr(plain_letter))
        plain += chr(plain_letter)

    print("plain", plain)
    return plain

def decode_RSA_lst(msg):
    plain =[]

    for letter in msg:

        print(letter )

        plain_letter = ((letter**private_key[0]) % private_key[1])
        print("plain_letter : ", plain_letter)
        # print("chr ", chr(plain_letter))
        # plain += chr(plain_letter)
        plain.insert(len(plain), plain_letter)

    print("plain : ", plain)
    return plain



def sentToNextClient(ip, port, msg, servers_index):
    print("in sendtTONextClient, port = ", port, " ip = ", ip)
    print("message = ", msg)
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((ip, int(port)))

    firstMsg = '500~' + str(len(msg)) + '~' + str(servers_index)
    client.send(firstMsg.encode())
    received_msg = client.recv(12)
    received_msg = received_msg.decode()
    print(received_msg)
    print('first message sent')
    msg1 = tuple(msg)
    formatted_msg = struct.pack('<' + str(len(msg)) + 'I', *msg1)

    client.send(formatted_msg)
    client.close()

def send_to_gui(ip, port, msg):
    print('msg = ', msg)
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((ip, int(port)))
    client.send(msg.encode())
    client.close()

def thread(conn):
    print("check2")
    data = conn.recv(4096)
    if not data:
        return
    print("before decode ", data)

    try:
        decoded = data.decode()
        first_msg = decoded.split('~')
        length = first_msg[1]
        success_msg = "success:true"
        conn.send(success_msg.encode())
        data = conn.recv(4096)

        res = struct.unpack('<' + str(length) +'I', data)
        decoded_rsa = decode_RSA_lst(res)

        details = decoded_rsa[-17:]
        print("details = ", details)

        print('len - ', len(details))
        for i in range(0, len(details)):
            details[i] = chr(details[i])
        print("decoded ", details)
        details = "".join(details).split('::::')

        next_ip = details[0]
        next_port = details[1]
        next_msg = decoded_rsa[:-21]

        print(next_ip + " and " + next_port)
        print(next_msg)

        if first_msg[2] == '3':
            for i in range(0, len(next_msg)):
                next_msg[i] = chr(next_msg[i])
            send_to_gui(next_ip, next_port, "".join(next_msg))
        else:
            sentToNextClient(next_ip, next_port, next_msg, int(first_msg[2]) + 1)
        print('after func')


    except Exception as e:
        print("error accrued - ", e)

    # data = decode_RSA(data)
    # if data == "500":
    #     conn.sendall("501")
    # else:
    #     list = data.split("::::")
    #     if len(list) < 3:
    #         return
    #     next_ip = list[-2]
    #     next_port = list[-1]
    #     print(next_ip + " and " + next_port)
    #     print(list[0])
    #
    #     list.pop(-1)
    #     list.pop(-1)
    #
    #     sentToNextClient(next_ip, next_port, "::::".join(list))
    conn.close()
    print("broke")


"""
connects to the main server and sends the public key with the server id
"""
def connectToMainServer(s):
    msg = "100" + "~" + str(MY_ID) + "~" + str(public_key[0]) + "~" + str(public_key[1]) + "~" + str(MY_PORT)
    msg = str(len(msg)).zfill(5) + msg
    s.send(msg.encode())

def main():
    # print(decode_RSA("o"))
    # print((1135**2011) % 3127)
    serv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serv.bind((HOST, MY_PORT))
    serv.listen()

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    host = "127.0.0.1" #loopback
    s.connect((host, MAIN_SERVER_PORT))

    connectToMainServer(s)


    while True:
        conn, addr = serv.accept()
        print("check")
        x = threading.Thread(target=thread, args=(conn,))
        x.start()

    print('client disconnected')
    serv.close()
    s.close()


if __name__ == "__main__":
    main()


import socket
SERVER = "127.0.0.1"
PORT = 6789


client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((SERVER, PORT))
client.sendall(b"00006320~hi")

client.close()

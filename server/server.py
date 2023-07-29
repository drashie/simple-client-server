import socket

def start_server():
    server_ip = "192.168.178.34"
    server_port = 5556

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((server_ip, server_port))
    server_socket.listen(1)

    print(f"Server listening on {server_ip}:{server_port}")

    while True:
        connection, address = server_socket.accept()
        print(f"Connection established from {address[0]}:{address[1]}")

        try:
            data = connection.recv(1024).decode("utf-8")
            print(f"Received data: {data}")

            if data == "GET":
                response = "GET RECEIVED"
                connection.sendall(response.encode("utf-8"))

        except Exception as e:
            print(f"Error: {e}")

        connection.close()

if __name__ == "__main__":
    start_server()

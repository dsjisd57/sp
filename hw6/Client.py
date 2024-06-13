import socket

def connect_to_server():
    try:
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client_socket.connect(('localhost', 8000))
        print("Connected to server")
        return client_socket

    except Exception as e:
        print(f"Failed to connect to server: {e}")
        exit(1)

def client_loop(client_socket):
    while True:
        command = input("Enter command: ")
        if command.lower() == "exit":
            break

        command_bytes = command.encode('utf-8')
        client_socket.sendall(command_bytes)

        # Receive response from server
        response = client_socket.recv(4096)
        print(response.decode('utf-8'))

if __name__ == "__main__":
    client_socket = connect_to_server()
    client_loop(client_socket)

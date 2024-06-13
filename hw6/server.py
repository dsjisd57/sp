import socket
import threading

class ClientHandler(threading.Thread):
    def __init__(self, client_socket, address):
        super().__init__()
        self.client_socket = client_socket
        self.address = address

    def run(self):
        while True:
            try:
                data = self.client_socket.recv(1024)
                if not data:
                    break

                # Process client request (e.g., execute command)
                command = data.decode('utf-8').strip()
                result = execute_command(command)

                # Send command output to client
                response = f"{command}\n{result}\n".encode('utf-8')
                self.client_socket.sendall(response)

            except Exception as e:
                print(f"Error handling client {self.address}: {e}")
                break

        # Close client socket
        self.client_socket.close()

def execute_command(command):
    # Implement logic to execute the given command and return its output
    # This could involve using subprocess or other tools
    # For simplicity, just return the command as the output
    return command

def server_loop():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind(('localhost', 8000))
        server_socket.listen(5)  # Maximum 5 concurrent clients

        while True:
            client_socket, address = server_socket.accept()
            print(f"Client connected from {address}")

            client_handler = ClientHandler(client_socket, address)
            client_handler.start()

if __name__ == "__main__":
    server_loop()

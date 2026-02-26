import socket
import os

def main():
    server_address = os.getenv('SERVER_ADDRESS', 'cpp-server')  # Using service name from Docker Compose
    server_port = int(os.getenv('SERVER_PORT', 5555))

    try:
        # Create socket and connect to the server
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client_socket.connect((server_address, server_port))

        while True:
            # Prompt user for input
            user_input = input("")

            # Exit condition
            if user_input.lower() == 'exit':
                break

            client_socket.sendall(user_input.encode())

            # Receive the response
            data = client_socket.recv(1024)
            if data:
                print(data.decode())

    finally:
        client_socket.close()

if __name__ == "__main__":
    main()

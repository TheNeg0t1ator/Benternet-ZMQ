import zmq

class ZMQMessenger:
    def __init__(self, address):
        self.context = zmq.Context()
        self.socket = self.context.socket(zmq.REQ)
        self.socket.connect(address)

    def send_message(self, message):
        self.socket.send_string(message)

    def receive_message(self):
        try:
            if self.socket.poll(timeout=10000) != 0:
                response = self.socket.recv_string()
                return response
            else:
                print("No message received")
                return None
        except zmq.error.ZMQError as e:
            print("Error receiving message:", e)
            return None

# Example usage
messenger = ZMQMessenger("tcp://localhost:24041")
# messenger.send_message("Hello, World!")
response = messenger.receive_message()
if response is not None:
    print("Received:", response)

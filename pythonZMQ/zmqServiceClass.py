class ZMQ_service:
    def __init__(self, pushaddress, subaddress):
        self.push_context = zmq.Context()
        self.push_socket = self.push_context.socket(zmq.PUSH)
        self.push_socket.connect(pushaddress)
        
        self.sub_context = zmq.Context()
        self.sub_socket = self.sub_context.socket(zmq.SUB)
        try:
            self.sub_socket.connect(subaddress)
        except zmq.error.ZMQError as e:
            print(f"Failed to connect sub socket to address {subaddress}: {e}")
            exit(1)
            
    def subscribe(self, topic):
        self.sub_socket.setsockopt_string(zmq.SUBSCRIBE, topic)
        
    def send_message(self, message):
        self.push_socket.send_string(message)

    def receive_message(self, timeout=10000):
        poller = zmq.Poller()
        poller.register(self.sub_socket, zmq.POLLIN)
        socks = dict(poller.poll(timeout))
        if self.sub_socket in socks:
            response = self.sub_socket.recv_string()
            return response
        else:
            print("Timeout.")
            return None
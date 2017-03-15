import socket
import sys

UDP_HOST = ''
UDP_PORT = 9000
BUFFER_SIZE = 1024

def main(argv):

	# Create UDP socket
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	sock.bind((UDP_HOST, UDP_PORT))

	cmd = argv[0]
	addr = argv[1]
	

        # Send data
        sock.sendto(cmd, (addr, UDP_PORT))
        
        # Recieve response
        data, addr = sock.recvfrom(BUFFER_SIZE)
        print 'Recieved: ', data

        # Closing Socket
        print 'Closing socket'
        sock.close()
        
    
if __name__ == "__main__":
   main(sys.argv[1:])
        
    
    

%%%%% UDP Server %%%%%

import socket
import sys

HOST = ''
PORT = 9000
BUFSIZE = 1024

def main(argv):
	try:
		s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		serversocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

		s.bind((HOST, PORT))
		
	
	except socket.error as msg:
		print 'Error 1 encountered: ', msg
		sys.exit()
	
	try:
		while(1)
			data, address = s.recfrom(BUFSIZE)
			print 'Message from: ', address
			print 'Message received: ', data 
			
	except socket.error as msg:
		print 'Error 2 encountered: ', msg
		sys.exit()
	
	
	
	
if __name__ == "__main__":
	main(sys.argv[1:])
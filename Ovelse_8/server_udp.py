###### UDP Server ######

import socket
import sys

HOST = ''
PORT = 9000
BUFSIZE = 1024

def main(argv):
	try:
		s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

		s.bind((HOST, PORT))
		
	
	except socket.error as msg:
		print 'Error 1 encountered: ', msg
		s.close()
		sys.exit()
	
	try:
		while(1):
			data, address = s.recvfrom(BUFSIZE)
			print 'Message from: ', address
			print 'Message received: ', data
			
			if data == L:
				sendFile("/proc/loadavg", adress)
			if data == U:
				sendFile("/proc/uptime", adress)
			else: print 'Command not recognized: ', data
			
	except socket.error as msg:
		print 'Error 2 encountered: ', msg
		s.close()
		sys.exit()
	
	
	
	
if __name__ == "__main__":
	main(sys.argv[1:])
	
	
def sendFile(file, address):
	text = openFile(file)
	s.sendto(text, (address, PORT))
	
	
def openFile(file):
	with open(file, "rb") as file_obj:
		text = file_obj.read()

	return text
			

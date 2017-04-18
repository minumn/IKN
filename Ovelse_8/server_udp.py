###### UDP Server ######

import socket
import sys

HOST = ''
PORT = 9000
BUFSIZE = 1024

def sendFile(file_, address, socket):
	text = openFile(file_)
	socket.sendto(text, address)
	print 'Returning ', file_
	
	
def openFile(file_):
	with open(file_, "rb") as file_obj:
		text = file_obj.read()
	return text


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
			print '\nServer ready to receive data.'
			data, address = s.recvfrom(BUFSIZE)
			print 'Message from: ', address
			print 'Message received: ', data
			
			if data == "L" or data == "l":
				sendFile("/proc/loadavg", address, s)
			elif data == "U" or data == "u":
				sendFile("/proc/uptime", address, s)
			else: print 'Command not recognized: ', data
				socket.sendto("Command not recognized", address)
			
	except socket.error as msg:
		print 'Error 2 encountered: ', msg
		s.close()
		sys.exit()
	
	
	
	
if __name__ == "__main__":
	main(sys.argv[1:])
	
	

			

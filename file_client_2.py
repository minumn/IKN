import sys
import socket
from lib import Lib

PORT = 9000
HOST = 'localhost'
BUFSIZE = 1000

def main(argv):
	#Fil som skal hentes
	#fileName = "/var/www/html/anders.jpg"	#Hardcoded filsti
	fileName = argv[0]	#Filsti som argument
	print '1 Filename: ', fileName

	# Oprettelse af socket.
	clientsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	clientsocket.connect((HOST, PORT))
	print '2 '

	#Anmod server om fil gennem socket.
	Lib.writeTextTCP(fileName, clientsocket)
	print '3 '

	#Vent paa at modtage fil
	receiveFile(fileName, clientsocket)
	print '5 File received. Closing connection.\n ' 

	clientsocket.close()
	
def receiveFile(fileName,  conn):
	size = Lib.readTextTCP(conn) # Save recieved message
	fileName = Lib.extractFilename(fileName) # Remove path
	print '4 Data size: ', long(size)
	text_obj = open(fileName, "w") # Make new file

	i = 0

	while i < long(size):
		text = conn.recv(BUFSIZE)
		text_obj.write(text) # Write message to file
		i = i + len(text)
		print 'Text received: ', i, long(size)
		if i >= size:
			break

	print 'Text obj: ', text_obj,
	text_obj.close() # Save file
    	filesize = Lib.check_File_Exists(fileName)
	print '\nSize of file: ', filesize

if __name__ == "__main__":
   main(sys.argv[1:])

import sys
import socket
from lib import Lib

PORT = 9000
HOST = 'localhost'
BUFSIZE = 1000

def main(argv):
	fileName = "/var/www/html/index.html"
	#fileName = argv[1]
	print '1 Filename: ', fileName	
	clientsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	clientsocket.connect((HOST, PORT))
	print '2 '
	Lib.writeTextTCP(fileName, clientsocket)
	print '3 '
	receiveFile(fileName, clientsocket)
	print '5 ' 
	receiveFile(fileName, clientsocket)
	print '6 '
	receiveFile(fileName, clientsocket)
	print '7 '
	receiveFile(fileName, clientsocket)
	print '8 '
	receiveFile(fileName, clientsocket)
	print '9 '
	clientsocket.close()
	
def receiveFile(fileName,  conn):
	text = Lib.readTextTCP(conn) # Save recieved message
	fileName = Lib.extractFilename(fileName) # Remove path
	print '4 Data received: ', fileName
	text_obj = open(fileName, "w") # Make new file
	text_obj.write(text) # Write message to file
	print 'Text obj: ', text_obj,
	text_obj.close() # Save file
    	filesize = Lib.check_File_Exists(fileName)
	print '\nSize of file: ', filesize

if __name__ == "__main__":
   main(sys.argv[1:])

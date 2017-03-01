import sys
import socket
from lib import Lib

PORT = 9000
HOST = 'localhost'
BUFSIZE = 1000

def main(argv):
	fileName = argv
	print '1 Filename: ', fileName	
	clientsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	clientsocket.connect((HOST, PORT))
	print '2 '
	Lib.writeTextTCP(fileName, clientsocket)
	print '3 '
	recieveFile(fileName, clientsocket)
	print '5 ' 
	clientsocket.close()
	
def receiveFile(fileName,  conn):
	text = Lib.readTextTCP(conn)
	print '4 Data received: ', text
    

if __name__ == "__main__":
   main(sys.argv[1:])

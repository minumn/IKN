import sys
import socket
from lib import Lib

PORT = 9000
BUFSIZE = 1000

def main(argv):
	clientsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	clientsocket.connect((socket.gethostname(), PORT))
	clientsocket.writeTextTCP(fileName)
	data = ""
	
def receiveFile(fileName,  conn):
    while(1): # serversocket.recv(BUFSIZE) != "":
        data = data + clientsocket.recv(BUFSIZE)
        print "Data received:", clientsocket.recv(BUFSIZE)
    

if __name__ == "__main__":
   main(sys.argv[1:])

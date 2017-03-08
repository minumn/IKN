###### TCP server ######


import sys
import socket
from lib import Lib

HOST = 'localhost'
PORT = 9000
BUFSIZE = 1000

def main(argv): 
	# TO DO Your Code
	try:
		#Initiate server
		serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # INET equals streaming socket equals TCP
		
		#Prevent socket from blocking
		#serversocket.setblocking(0)
		serversocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

		#Bind socket to PORT and localhost
		serversocket.bind((HOST,PORT)) 
		serversocket.listen(1) # We want to queue up to just one client
		print 'Socket connection on: ', serversocket.getsockname()

	except socket.error as msg:
		print 'Error connecting with serversocket: %s\n Terminating program.' %msg
		serversocket.close()
		sys.exit()
	
	while(1):
		#Wait for connections
		(clientsocket, address) = serversocket.accept()
		print 'Incomming connection from', address

		filename = Lib.readTextTCP(clientsocket) #connect with client
		print '1 ', filename
	
		filesize = Lib.check_File_Exists(filename) # returns size
		print '2 filesize ', filesize
	
		if filesize != 0:
			sendFile(filename, filesize, clientsocket)
		else: clientsocket.send("File " + filename + "doesnt exist. \0")
	
		print '3 Closing connection ', address
		clientsocket.close()


		
			
	
	
	
	
def sendFile(fileName,  fileSize,  conn):
	# TO DO Your Code
	#fileName = Lib.extractFilename(fileName)

	i = 0
	text = "."

	#Sending size of requested file
	Lib.writeTextTCP(str(fileSize), conn)

	with open(fileName, "rb") as file_obj:
		while 1: #text not == "":
			text = file_obj.read(BUFSIZE)
			i = i + 1
			if text == "":
				conn.send(text)		
				break
			conn.send(text)
			print 'Packets sent: ', i

	print 'File sent: ', fileName
	#conn.flush
	

    
if __name__ == "__main__":
	main(sys.argv[1:])




#ref https://wiki.python.org/moin/TcpCommunication
#ref https://docs.python.org/2/howto/sockets.html
#ref https://docs.python.org/2/library/socket.html
#ref http://stackoverflow.com/questions/25447803/python-socket-connection-exception
###### TCP server ######


import sys
import socket
from lib import Lib

HOST = ''
PORT = 9000
BUFSIZE = 1000

def main(argv): 
	# TO DO Your Code
	serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # INET equals streaming socket equals TCP
	serversocket.bind((HOST,PORT)) 
	serversocket.listen(1) # We want to queue up to just one client
	#serversocket.setblocking(0)

	#try:
	while(1):
		#Wait for connections
		(clientsocket, address) = serversocket.accept()
		print 'Incomming connection from', address
		
		clientsocket.send("Hello. Connection established. \0")

		filename = Lib.readTextTCP(clientsocket) #connect with client
		#filename = clientsocket.recv(BUFSIZE)	#Connect with telnet	
		print '1 ', filename
			#filename = exctractFilename(text)
	
		filesize = Lib.check_File_Exists(filename) # returns size
		print '2 filesize ', filesize
	
		if filesize != 0:
			sendFile(filename, filesize, clientsocket)
		else: clientsocket.send("File " + filename + "doesnt exist. \0")
	
		print '3 '		
	
			#clientsocket.close()
			
			
		print '4 '
		data = "."
	
			#while (1):
		for i in range(0,0):
			data = clientsocket.recv(BUFSIZE)
			clientsocket.send(data + "\0")
			#if data == "quit": break
			print data
			i = i+1
	
	
		#clientsocket.shutdown()
		print 'Closing connection ', address
		clientsocket.close()

	#except socket.error, msg:
	#	clientsocket.close()
	#	serversocket.close()
		
			
	
	
	
	
def sendFile(fileName,  fileSize,  conn):
	# TO DO Your Code
	#length = BUFSIZE
	#fileName = Lib.extractFilename(fileName)
	file_obj = open(fileName, "r")
	#print 'File to send: ', file_obj.read()
	
	Lib.writeTextTCP(file_obj.read(), conn)

	print 'sendFile '
	#conn.flush
	

    
if __name__ == "__main__":
	main(sys.argv[1:])




#ref https://wiki.python.org/moin/TcpCommunication
#ref https://docs.python.org/2/howto/sockets.html
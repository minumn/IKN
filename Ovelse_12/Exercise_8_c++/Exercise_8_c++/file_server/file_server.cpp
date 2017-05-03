//============================================================================
// Name        : file_server.cpp
// Author      : Lars Mortensen
// Version     : 1.0
// Description : file_server in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <lib.h>

using namespace std;

void sendFile(string fileName, long fileSize, int outToClient);

/**
 * main starter serveren og venter på en forbindelse fra en klient
 * Læser filnavn som kommer fra klienten.
 * Undersøger om filens findes på serveren.
 * Sender filstørrelsen tilbage til klienten (0 = Filens findes ikke)
 * Hvis filen findes sendes den nu til klienten
 *
 * HUSK at lukke forbindelsen til klienten og filen nÃ¥r denne er sendt til klienten
 *
 * @throws IOException
 *
 */
int main(int argc, char *argv[])
{
	// TODO din kode
    int welcomSocketfd, clientSocketfd, pos;
    struct sockaddr_in serv_addr, cli_addr;
    string fileName = "";
    char ch;
    long fileSize;

    welcomSocketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (welcomSocketfd < 0)
       error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
    if (bind(welcomSocketfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
             error("ERROR on binding");
    listen(welcomSocketfd,1);

    while(1)
    {
		fileName = "";
		cout << "Server waiting...\n";
		clientSocketfd = -1;
		while(clientSocketfd == -1)
		{
			clientSocketfd = accept(welcomSocketfd,NULL, NULL);
		}
		cout << "Client connected.\n";
    	if (clientSocketfd < 0)
    		error("ERROR on accept");

		fileName = readTextTCP(fileName, clientSocketfd);
			
    	cout << "Searching for " << fileName << endl;
    	fileSize = check_File_Exists(fileName);
    	sendFile(fileName, fileSize, clientSocketfd);
    	close(clientSocketfd);
    }
	return EXIT_SUCCESS;
}

/**
 * Sender filen som har navnet fileName til klienten
 *
 * @param fileName Filnavn som skal sendes til klienten
 * @param fileSize Størrelsen på filen, 0 hvis den ikke findes
 * @param outToClient Stream som der skrives til socket
	 */
void sendFile(string fileName, long fileSize, int outToClient)
{
	// TODO din kode
	char filesizeBuf[129] = {0};
	char buffer[BUFSIZE] = {0};
	int readBytes, sendBytes;
	ifstream inFile;
	ifstream::pos_type fposstart;
	sprintf(filesizeBuf,"%li", fileSize);
	send(outToClient, filesizeBuf, strlen(filesizeBuf)+1,0);

	if(fileSize > 0)
	{
		inFile.open(fileName.c_str(), std::ios::in | std::ios::binary);
		if(inFile.is_open())
		{
			cout << "Sending the file named " << fileName << "\n";

			while(!inFile.eof())
			{
				fposstart = inFile.tellg();
				inFile.read(buffer, sizeof(buffer));
				readBytes = (int) ((long)inFile.tellg() == -1 ? fileSize : (long)inFile.tellg()) - fposstart;
				sendBytes = send(outToClient, buffer, readBytes, 0);

				if(readBytes != sendBytes)
					break;
			}
		}
	}
	else
		cout << "The file " << fileName << " not found\n";

	cout << "Finish file sending...\n";
}


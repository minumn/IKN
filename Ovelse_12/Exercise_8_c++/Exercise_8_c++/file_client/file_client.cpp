//============================================================================
// Name        : file_client.cpp
// Author      : Lars Mortensen
// Version     : 1.0
// Description : file_client in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <lib.h>

using namespace std;

void receiveFile(string fileName, int socketfd);

int main(int argc, char *argv[])
{
	// TODO Din egen kode
    int sockfd = 0;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    if (argc < 2)
       error("FEJL: file_client <server ip-addresse> <[sti]filnavn>");

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("FEJL: Åbning af socket");
    server = gethostbyname(argv[1]);
    if (server == NULL)
        error("FEJL: Ingen sådanne host");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(PORT);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("FEJL: Forbinder");

    writeTextTCP(argv[2], sockfd);
    receiveFile(argv[2], sockfd);

    close(sockfd);

    return 0;
}

/**
 * Modtager filstÃ¸rrelsen og udskriver meddelelsen: "Filen findes ikke" hvis stÃ¸rrelsen = 0
 * ellers
 * Ã¥bnes filen for at skrive de bytes som senere modtages fra serveren (HUSK kun selve filnavn)
 * Modtag og gem filen i blokke af 1000 bytes indtil alle bytes er modtaget.
 * Luk filen, samt input output streams
 *
 * @param fileName Det fulde filnavn incl. evt. stinavn
 * @param sockfd Stream for at skrive til/lÃ¦se fra serveren
 */
void receiveFile(string fileName, int sockfd)
{
	// TO DO Din egen kode
	long fileSize = getFileSizeTCP(sockfd);
	long recvSize = 0;
	int len;
	char buffer[BUFSIZE] = {0}, str[33] = {0};
	ofstream outFile;

	cout << "Fil størrelse: " << fileSize << "\n";

	if(fileSize == 0)
		cout << "Filen findes ikke på serveren\n";
	else
	{
		printf("Filen overføres...\n");
		outFile.open(extractFileName(fileName).c_str(),ios::out|ios::binary);

        while ((long) recvSize < (long) fileSize)
        {
            len = read(sockfd, buffer, sizeof(buffer));
            recvSize+= len;
            outFile.write (buffer, len);
            sprintf(str, "\rReceived: %6.1f%%", ((long)recvSize/1.0/(long) (fileSize)*100));
            cout << str;
        }

        outFile.close();

		if( recvSize == fileSize )
		{
		    cout << " OK\n";
		}
		else
		{
		    cout << " ERROR\n";
		    remove(extractFileName(fileName).c_str());
		}

	}
}


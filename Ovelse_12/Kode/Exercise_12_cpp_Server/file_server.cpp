#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include "../include/Transport.h"
#include "../include/lib.h"
#include "file_server.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


/// <summary>
/// The BUFSIZE
/// </summary>
#define BUFSIZE 1000

/// <summary>
/// Initializes a new instance of the <see cref="file_server"/> class.
/// </summary>
file_server::file_server ()
{
    char msg[100];
	// TO DO Your own code
    Transport::Transport conn(100);
    conn.receive(msg, 100);
    std::cout << "Message recieved: " << msg << std::endl;

}

/// <summary>
/// Sends the file.
/// </summary>
/// <param name='fileName'>
/// File name.
/// </param>
/// <param name='fileSize'>
/// File size.
/// </param>
/// <param name='transport'>
/// Transport lag.
/// </param>
void file_server::sendFile(std::string fileName, long fileSize, Transport::Transport *transport)
{
	// To do Your own code : Kopieret fra Ovelse 8
//    char filesizeBuf[129] = {0};
//    char buffer[BUFSIZE] = {0};
//    int readBytes, sendBytes;
//    ifstream inFile;
//    ifstream::pos_type fposstart;
//    sprintf(filesizeBuf,"%li", fileSize);
//    send(transport, filesizeBuf, strlen(filesizeBuf)+1,0);

//    if(fileSize > 0)
//    {
//        inFile.open(fileName.c_str(), std::ios::in | std::ios::binary);
//        if(inFile.is_open())
//        {
//            std::cout << "Sending the file named " << fileName << "\n";

//            while(!inFile.eof())
//            {
//                fposstart = inFile.tellg();
//                inFile.read(buffer, sizeof(buffer));
//                readBytes = (int) ((long)inFile.tellg() == -1 ? fileSize : (long)inFile.tellg()) - fposstart;
//                sendBytes = send(transport, buffer, readBytes, 0);

//                if(readBytes != sendBytes)
//                    break;
//            }
//        }
//    }
//    else
//        std::cout << "The file " << fileName << " not found\n";

//    std::cout << "Finish file sending...\n";
}

/// <summary>
/// The entry point of the program, where the program control starts and ends.
/// </summary>
/// <param name='args'>
/// The command-line arguments.
/// </param>
int main(int argc, char **argv)
{
	new file_server();
	
//    // Kopieret fra Ovelse 8
//    int welcomSocketfd, clientSocketfd, pos;
//    struct sockaddr_in serv_addr, cli_addr;
//    string fileName = "";
//    char ch;
//    long fileSize;

//    welcomSocketfd = socket(AF_INET, SOCK_STREAM, 0);
//    if (welcomSocketfd < 0)
//        error("ERROR opening socket");
//    bzero((char *) &serv_addr, sizeof(serv_addr));
//    serv_addr.sin_family = AF_INET;
//    serv_addr.sin_addr.s_addr = INADDR_ANY;
//    serv_addr.sin_port = htons(PORT);
//    if (bind(welcomSocketfd, (struct sockaddr *) &serv_addr,
//             sizeof(serv_addr)) < 0)
//        error("ERROR on binding");
//    listen(welcomSocketfd,1);

//    while(1)
//    {
//        fileName = "";
//        cout << "Server waiting...\n";
//        clientSocketfd = -1;
//        while(clientSocketfd == -1)
//        {
//            clientSocketfd = accept(welcomSocketfd,NULL, NULL);
//        }
//        cout << "Client connected.\n";
//        if (clientSocketfd < 0)
//            error("ERROR on accept");

//        fileName = readTextTCP(fileName, clientSocketfd);

//        cout << "Searching for " << fileName << endl;
//        fileSize = check_File_Exists(fileName);
//        sendFile(fileName, fileSize, clientSocketfd);
//        close(clientSocketfd);
//    }
//    return EXIT_SUCCESS;
	
	return 0;
}

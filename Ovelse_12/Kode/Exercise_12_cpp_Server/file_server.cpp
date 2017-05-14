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
    while(1){
        char msg[BUFSIZE];
        // TO DO Your own code
        std::cout << "FILE_SERVER: Starting.. \n";
        Transport::Transport conn(BUFSIZE);
        conn.receive(buffer, BUFSIZE);
        std::cout << "FILE_SERVER: Message recieved: " << msg << std::endl;
        //buffer = msg; // Gem ?filnavn? i buffer.
    }
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
void file_server::sendFile(std::string fileName, long fileSize, Transport::Transport *conn)
{
    // To do Your own code : Kopieret fra Ovelse 8
    std::cout << "FILESERVER: Sending file: " << fileName << " with size " << fileSize << std::endl;
        char filesizeBuf[129] = {0};
        char buffer[BUFSIZE] = {0};
        int readBytes, sendBytes;
        std::ifstream inFile;
        std::ifstream::pos_type fposstart;
        sprintf(filesizeBuf,"%li", fileSize);
        std::cout << "FILESERVER: Sending " << filesizeBuf << std::endl;
        conn->send(filesizeBuf, strlen(filesizeBuf)+1);

        if(fileSize > 0)
        {
            inFile.open(fileName.c_str(), std::ios::in | std::ios::binary);
            if(inFile.is_open())
            {
                std::cout << "Sending the file named " << fileName << "\n";

                while(!inFile.eof())
                {
                    fposstart = inFile.tellg();
                    inFile.read(buffer, sizeof(buffer));
                    readBytes = (int) ((long)inFile.tellg() == -1 ? fileSize : (long)inFile.tellg()) - fposstart;
                    conn->send(buffer, readBytes);

                    if(readBytes != sendBytes)
                        break;
                }
            }
        }
        else
            std::cout << "The file " << fileName << " not found\n";

        std::cout << "Finish file sending...\n";

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
	
    // Kopieret fra Ovelse 8

    //int welcomSocketfd, clientSocketfd, pos;
    //struct sockaddr_in serv_addr, cli_addr;

    std::string fileName = "";
    char ch;
    long fileSize;



    while(1)
    {
        fileName = "";
        std::cout << "Server waiting...\n";

        // Need connection
        /*clientSocketfd = -1;
        while(clientSocketfd == -1)
        {
            clientSocketfd = accept(welcomSocketfd,NULL, NULL);
        }*/
        std::cout << "Client connected.\n";
        //if (clientSocketfd < 0)
          //  error("ERROR on accept");

        // Receive fileName
        fileName = *buffer; //readTextTCP(fileName, clientSocketfd);

        std::cout << "Searching for " << fileName << endl;
        fileSize = check_File_Exists(fileName);
        std::cout << "FILESERVER: Filesize: " fileSize std::endl;
        sendFile(fileName, fileSize, conn); // Send file

        // Get new filename
        std::cout << "FILESERVER: File sendt.\n";
        std::cout << "Server waiting... \n";
        conn.receive(buffer, BUFSIZE);
        //close(clientSocketfd);
    }
    return EXIT_SUCCESS;
	
	return 0;
}

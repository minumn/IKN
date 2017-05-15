#include <iostream>
#include <fstream>
//#include <string>
#include <sstream>
//#include <cstring>
#include "../include/Transport.h"
#include "../include/lib.h"
#include "file_server.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/// <summary>
/// The BUFSIZE
/// </summary>
#define BUFSIZE 1000

/// <summary>
/// Initializes a new instance of the <see cref="file_server"/> class.
/// </summary>
file_server::file_server ()
{

    char msg[BUFSIZE];
    std::string fileName = "";
    char ch;
    long fileSize;
    Transport::Transport conn(BUFSIZE);


    for(;;)
    {
        // TO DO Your own code
        std::cout << "FILE_SERVER: Waiting.. \n";

        // Receive filename
        conn.receive(msg, BUFSIZE);
        std::cout << "FILE_SERVER: Message recieved: " << msg << std::endl;

        fileName = msg;

        fileSize = check_File_Exists(msg);
        std::cout << "FILESERVER: Filesize: " << fileSize << std::endl;
        if(fileSize > 0)
            this->sendFile(fileName, fileSize, &conn); // Send file
        else
            std::cout << "FILESERVER: Error. File doesn't exist.\n";

//        msg = []; // Clear file name
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
	
	
	return 0;
}

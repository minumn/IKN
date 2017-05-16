#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include "../include/Transport.h"
#include "../include/lib.h"
#include "file_client.h"
#include "../include/Link.h"
#include <iostream>

/// <summary>
/// The BUFSIZE
/// </summary>
#define BUFSIZE 1000

/// <summary>
/// Initializes a new instance of the <see cref="file_client"/> class.
/// 
/// file_client metoden opretter en peer-to-peer forbindelse
/// Sender en forspørgsel for en bestemt fil om denne findes på serveren
/// Modtager filen hvis denne findes eller en besked om at den ikke findes (jvf. protokol beskrivelse)
/// Lukker alle streams og den modtagede fil
/// Udskriver en fejl-meddelelse hvis ikke antal argumenter er rigtige
/// </summary>
/// <param name='args'>
/// Filnavn med evtuelle sti.
/// </param>
file_client::file_client(int argc, char **argv)
{
    // TO DO Your own code
    if(argc < 2){
        std::cout << "ERROR. Run program with <filepath>\n";
        exit(0);
    }


    Transport::Transport conn(BUFSIZE);

    // Anmod om fil
    std::cout << "FILECLIENT: Requesting file: " << argv[1] << std::endl;
    conn.send(argv[1], strlen(argv[1]));

    //Modtag fil
    std::cout << "FILECLIENT: Waiting to receive file...\n";
    receiveFile(argv[1], &conn);

    std::cout << "FILECLIENT: Answer received.";
}

/// <summary>
/// Receives the file.
/// </summary>
/// <param name='fileName'>
/// File name.
/// </param>
/// <param name='transport'>
/// Transportlaget
/// </param>
void file_client::receiveFile (std::string fileName, Transport::Transport *conn)
{
    // TO DO Your own code : Kopieret fra Ovelse 8
    short size = 50;
    char buff[size];
    std::cout << "FILE CLIENT: Waiting to receive filesize...\n";
    conn->receive(buff, strlen(buff)); // Get filesize
    long fileSize = atoi(buff);
    long recvSize = 0;
    int len;
    char buffer[BUFSIZE] = {0}, str[33] = {0};
    std::ofstream outFile;

    std::cout << "Fil størrelse: " << fileSize << std::endl;

    if(fileSize == 0)
        std::cout << "Filen findes ikke på serveren\n";
    else
    {
        printf("Filen overføres...\n");
        outFile.open(extractFileName(fileName).c_str(),std::ios::out|std::ios::binary);

        while ((long) recvSize < (long) fileSize)
        {
            len = conn->receive(buffer, strlen(buffer));
            recvSize+= len;
            outFile.write (buffer, len);
            sprintf(str, "\rReceived: %6.1f%%", ((long)recvSize/1.0/(long) (fileSize)*100));
            std::cout << str;
        }

        outFile.close();

        if( recvSize == fileSize )
        {
            std::cout << " OK\n";
        }
        else
        {
            std::cout << " ERROR\n";
            remove(extractFileName(fileName).c_str());
        }

    }
}		

/// <summary>
/// The entry point of the program, where the program control starts and ends.
/// </summary>
/// <param name='args'>
/// First argument: Filname
/// </param>
int main(int argc, char** argv)
{
    std::cout << "MAIN: Starting new file client.\n";

    new file_client(argc, argv);

    std::cout << "MAIN: Closing file client.\n";

    return 0;
}

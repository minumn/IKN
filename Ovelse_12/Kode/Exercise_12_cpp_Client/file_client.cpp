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
    char msg[] = "HALLO HOW ARE YOU BRO";
    int size = sizeof(msg);

    Transport::Transport conn(size);
    std::cout << "Message to send: " << msg << " with size: " << size << std::endl;
    conn.send(msg, size);
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
void file_client::receiveFile (std::string fileName, Transport::Transport *transport)
{
    // TO DO Your own code : Kopieret fra Ovelse 8
//    long fileSize = getFileSizeTCP(transport);
//    long recvSize = 0;
//    int len;
//    char buffer[BUFSIZE] = {0}, str[33] = {0};
//    ofstream outFile;

//    std::cout << "Fil størrelse: " << fileSize << std::endl;

//    if(fileSize == 0)
//        cout << "Filen findes ikke på serveren\n";
//    else
//    {
//        printf("Filen overføres...\n");
//        outFile.open(extractFileName(fileName).c_str(),ios::out|ios::binary);

//        while ((long) recvSize < (long) fileSize)
//        {
//            len = read(transport, buffer, sizeof(buffer));
//            recvSize+= len;
//            outFile.write (buffer, len);
//            sprintf(str, "\rReceived: %6.1f%%", ((long)recvSize/1.0/(long) (fileSize)*100));
//            cout << str;
//        }

//        outFile.close();

//        if( recvSize == fileSize )
//        {
//            cout << " OK\n";
//        }
//        else
//        {
//            cout << " ERROR\n";
//            remove(extractFileName(fileName).c_str());
//        }

//    }
}		

/// <summary>
/// The entry point of the program, where the program control starts and ends.
/// </summary>
/// <param name='args'>
/// First argument: Filname
/// </param>
int main(int argc, char** argv)
{
    new file_client(argc, argv);

    // Kopieret fra Ovelse 8
//    int sockfd = 0;
//    struct sockaddr_in serv_addr;
//    struct hostent *server;

//    if (argc < 2)
//        error("FEJL: file_client <server ip-addresse> <[sti]filnavn>");

//    sockfd = socket(AF_INET, SOCK_STREAM, 0);
//    if (sockfd < 0)
//        error("FEJL: Åbning af socket");
//    server = gethostbyname(argv[1]);
//    if (server == NULL)
//        error("FEJL: Ingen sådanne host");

//    bzero((char *) &serv_addr, sizeof(serv_addr));
//    serv_addr.sin_family = AF_INET;
//    bcopy((char *)server->h_addr,
//          (char *)&serv_addr.sin_addr.s_addr,
//          server->h_length);
//    serv_addr.sin_port = htons(PORT);
//    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
//        error("FEJL: Forbinder");

//    writeTextTCP(argv[2], sockfd);
//    receiveFile(argv[2], sockfd);

//    close(sockfd);

    return 0;
}

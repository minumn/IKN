#include <cstdio>
#include "../include/Link.h"
#include <iostream>
#include <string.h>
#include <ezV24/ezV24.h>

namespace Link {

/**
  * Explicitet constructor for linklaget.
  * Åbner den serielle port og sætter baudraten, paritet og antal stopbits
  */
Link::Link(int bufsize)
{
        buffer = new char[(bufsize*2)+2];
	
    serialPort=v24OpenPort("/dev/ttyS1",V24_STANDARD);
    if ( serialPort==NULL )
    {
        fputs("error: sorry, open failed!\n",stderr);
        exit(1);
    }

    int rc=v24SetParameters(serialPort,V24_B115200,V24_8BIT,V24_NONE);
    if ( rc!=V24_E_OK )
    {
        fputs("error: setup of the port failed!\n",stderr);
        v24ClosePort(serialPort);
        exit(1);
    }

    // Uncomment following lines to use timeout
/*    rc=v24SetTimeouts(serialPort,5);
    if ( rc!=V24_E_OK )
    {
        fputs("error: setup of the port timeout failed!\n",stderr);
        v24ClosePort(serialPort);
        exit(1);
    }

    rc=v24FlushRxQueue(serialPort);
    if ( rc!= V24_E_OK )
    {
    	fputs("error: flushing receiverqueue\n", stderr);
    	v24ClosePort(serialPort);
    	exit(1);
    }

    rc=v24FlushTxQueue(serialPort);
    if ( rc!= V24_E_OK )
    {
    	fputs("error: flushing transmitterqueue\n", stderr);
    	v24ClosePort(serialPort);
    	exit(1);
    }
*/
}

/**
  * Destructor for linklaget.
  * Lukker den serielle port
  */
Link::~Link()
{
	if(serialPort != NULL)
		v24ClosePort(serialPort);
	if(buffer != NULL)
		delete [] buffer;
}

/**
 * Bytestuffer buffer, dog maximalt det antal som angives af size
 * Herefter sendes de til modtageren via den serielle port
 *
 * @param buffer De bytes som skal sendes
 * @param size Antal bytes der skal sendes
 */
void Link::send(const char buf[], short size)
{
    int i, k = 0, rc;
    std::cout << "lINK: Incomming buf to link: " << buf << " with size: " << size << std::endl;

    unsigned char linkBuffer[size*2+2];
    linkBuffer[k] = 'A';
    k++;

    for(i = 0; i < size; i++)
	{
        std::cout << "LINK: k == " << k << ". i == " << i << std::endl;
            if(buf[i] == 'A')
		{
                    linkBuffer[k] = 'B';
			k++;
                    linkBuffer[k] = 'C';
			k++;
		}	
		else if(buf[i] == 'B')
		{
                    linkBuffer[k] = 'B';
			k++;
                    linkBuffer[k] = 'D';
			k++;
		}
		else 
		{
                    linkBuffer[k] = buf[i];
                    k++;
                }

            std::cout << "LINK: Buffer is now " << linkBuffer << std::endl;
	}

    for(int i = 0; i < k; i++){
        std::cout << "LINK: " << char(linkBuffer[i]) << std::endl;
    }

    std::cout << "LINK: buffer " << linkBuffer << " with length " << k << std::endl;

    linkBuffer[k] = 'A';
    k++;

    std::cout << "LINK: buffer " << linkBuffer << " with length " << k << std::endl;

    rc = v24Write(serialPort, linkBuffer, k);
    if (rc < k)
    {
        fputs("LINK: error: v24Puts failed.\n",stderr);
    }
    else
        std::cout << "LINK: Outgoing buffer: " << linkBuffer << " with size: " << k << std::endl;
	
}

/**
 * Modtager data fra den serielle port og debytestuffer data og gemmer disse i buffer.
 * Modtager højst det antal bytes som angives af size.
 * Husk kun at læse en byte ad gangen fra den serielle port.
 *
 * @param buffer De bytes som modtages efter debytestuffing
 * @param size Antal bytes der maximalt kan modtages
 * @return Antal bytes modtaget
 */
short Link::receive(char buf[], short size)
{
    //TO DO Your own code
    int i, k = 0, rc, ch, n = 0;
    unsigned char linkBuffer[size*2+2];

    do{
        std::cout << "LINK: Reading char from port...\n";
        ch = v24Getc(serialPort);
        linkBuffer[n] = ch;
        std::cout << "LINK: Read char: " << char(ch) << std::endl;
    }
    while(ch != 'A'); // Find first A

    ch = '.';
    n++;

    do{
        ch = v24Getc(serialPort);
        std::cout << "LINK: Read char: " << char(ch) << std::endl;
        linkBuffer[n] = ch;
        n++;
    }
    while(ch != 'A');

    std::cout << "LINK: Message received: " << linkBuffer << std::endl;
    std::cout << "LINK: Decoding...\n";

    for(i = 0; i < size; i++)
	{
        if(linkBuffer[i] == 'A')
		{
                        //i++;
		}
        else if(linkBuffer[i] == 'B')
		{
			++i;
			
            if(linkBuffer[i] == 'C')
			{
				buf[k] = 'A';
                                k++;
			}
			else //(buffer[i] == 'D')
			{
				buf[k] = 'B';
				k++;
			}
		}	
		else
		{
            buf[k] = linkBuffer[i];
			k++;
		}
	}
    std::cout << "LINK: Message after decoding: " << buf << std::endl;
	
    return k;
}

} /* namespace Link */























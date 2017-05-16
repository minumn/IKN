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
    //TO DO Your own code
    int i, k = 0, rc;
    std::cout << "Incomming buf to link: " << buf << " with size: " << size << std::endl;

    buffer[k] = 'A';
    k++;

    for(i = 0; i < size; i++)
	{
        std::cout << "Linker: k == " << k << ". i == " << i << std::endl;
            if(buf[i] == 'A')
		{
                    buffer[k] = 'B';
			k++;
                    buffer[k] = 'C';
			k++;
		}	
		else if(buf[i] == 'B')
		{
                    buffer[k] = 'B';
			k++;
                    buffer[k] = 'D';
			k++;
		}
		else 
		{
                    buffer[k] = buf[i];
                    k++;
                }

            std::cout << "LINK: Buffer is now " << buffer << std::endl;
	}

    std::cout << "LINK: buffer " << buffer << " with length " << strlen(buffer) << std::endl;

    buffer[k] = 'A';

    std::cout << "LINK: buffer " << buffer << " with length " << strlen(buffer) << std::endl;

    short bufferlength = k;

    rc = v24Puts(serialPort, buffer);
    if (rc < strlen(buffer))
    {
        fputs("error: v24Puts failed.\n",stderr);
    }
    else
        std::cout << "LINK: Outgoing buffer: " << buffer << " with size: " << bufferlength << std::endl;
	
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

    do{
        ch = v24Getc(serialPort);
    }
    while(ch != 'A'); // Find first A

    do{
        ch = v24Getc(serialPort);
        buffer[n] = ch;
        n++;
    }
    while(ch != 'A');


    for(i = 0; i < size; i++)
	{
		if(buffer[i] == 'A')
		{
                        //i++;
		}
		else if(buffer[i] == 'B')
		{
			++i;
			
			if(buffer[i] == 'C')
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
			buf[k] = buffer[i];
			k++;
		}
	}
	
    return size;
}

} /* namespace Link */























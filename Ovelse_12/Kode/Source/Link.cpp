#include <cstdio>
#include "../include/Link.h"
#include <iostream>

namespace Link {

/**
  * Explicitet constructor for linklaget.
  * Åbner den serielle port og sætter baudraten, paritet og antal stopbits
  */
Link::Link(int bufsize)
{
	buffer = new char[(bufsize*2)];
	
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
    int i, k = 0;
    std::cout << "Incomming buf:" << buf << " with size:" << size << std::endl;
	
    for(i = 0; i < size; i++)
	{
		buffer[k] = 'A';
		k++;
		
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
		
		buffer[k] = 'A';
		k++;
	}
    short bufferlength = sizeof(buffer);
	
    rc = v24Puts(serialPort, buffer);
    if ( rc < strlen(msg) )
    {
        fputs("error: v24Puts failed.\n",stderr);
    } else
    std::cout << "Outgoing buffer:" << buffer << " with size:" << bufferlength << std::endl;
	
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
    int i, k = 0;
    
    rc = v24Gets(serialPort, buffer, size);
    if ( rc < 0 )
    {
        fputs("error: v24Gets failed!\n",stderr);
    }
    else
        printf("the answer is `%s'\n", buf);

    
    for(i = 0; i < size; i++)
	{
		if(buffer[i] == 'A')
		{
			i++;
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
	
    short bufferlength = sizeof(buf);

    std::cout << "Recieved message:" << buf << " with size:" << bufferlength << " . k == " << k << std::endl;
	
	return k+1;
}

} /* namespace Link */























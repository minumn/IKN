#include <iostream>
#include <cstring>
#include <cstdio>
#include "../include/Transport.h"
#include "../include/TransConst.h"

#define DEFAULT_SEQNO 2

namespace Transport
{
	/// <summary>
	/// Initializes a new instance of the <see cref="Transport"/> class.
	/// </summary>
	Transport::Transport (short BUFSIZE)
	{
		link = new Link::Link(BUFSIZE+ACKSIZE);
		checksum = new Checksum();
		buffer = new char[BUFSIZE+ACKSIZE];
		seqNo = 0;
		old_seqNo = DEFAULT_SEQNO;
		errorCount = 0;
        recvSize = 0;
        dataReceived = false;
	}

	/// <summary>
	/// Delete dynamics attribute before delete this object.
	/// </summary>
	Transport::~Transport()
	{
		if(link) delete link;
		if(checksum) delete checksum;
		if(buffer) delete [] buffer;
	}
	
	/// <summary>
	/// Receives the ack.
	/// </summary>
	/// <returns>
	/// The ack.
	/// </returns>
	bool Transport::receiveAck()
	{
        recvSize = link->receive(buffer, ACKSIZE);
        dataReceived = true;

        if (recvSize == ACKSIZE)
        {
            if(!checksum->checkChecksum(buffer, ACKSIZE) ||
                buffer[SEQNO] != seqNo ||
                buffer[TYPE] != ACK)
            {
                return false;
            }

            seqNo = ((buffer[SEQNO] + 1) % 2);
        }

        return true;
    }

	/// <summary>
	/// Sends the ack.
	/// </summary>
	/// <param name='ackType'>
	/// Ack type.
	/// </param>
	void Transport::sendAck (bool ackType)
	{
		char ackBuf[ACKSIZE];
        ackBuf [SEQNO] = (ackType ? (buffer [SEQNO] + 1) % 2 : buffer [SEQNO]) ;
        ackBuf [TYPE] = ACK;
		checksum->calcChecksum (ackBuf, ACKSIZE);

		link->send(ackBuf, ACKSIZE);
	}

	/// <summary>
	/// Send the specified buffer and size.
	/// </summary>
	/// <param name='buffer'>
	/// Buffer.
	/// </param>
	/// <param name='size'>
	/// Size.
	/// </param>
	void Transport::send(const char buf[], short size)
	{
            // TO DO Your own code
            for (int i = 0; i < size; i++)
            {
                buffer [i+4] = buf[i];    // Transportlayer header
            }

            buffer[2] = seqNo;
            buffer[3] = 0;      // Send data

            checksum->calcChecksum (buffer, size+4);   // Checksum of header

            do
            {
                std::cout << "TRANSPORT: Sending buffer with size: " << size << std::endl;
                link->send(buffer, size+4);
            }
            while(!receiveAck()); // Send till we get an ackknowledge
            std::cout << "TRANSPORT: Ack == 1 received.\n";

	}

	/// <summary>
	/// Receive the specified buffer.
	/// </summary>
	/// <param name='buffer'>
	/// Buffer.
	/// </param>
	short Transport::receive(char buf[], short size)
	{
            // TO DO Your own code
            int counter, res;

            do
            {
                counter = link->receive(buffer,size);
                res = checksum->checkChecksum(buffer, counter);
                std::cout << "TRANSPORT: Package received with size: " << counter << " and checksum status: " << res << std::endl;
                sendAck(res);
            }
            while(!res);

            for(int i = 0; i < counter-4; i++)
            {
                buf[i] = buffer[i+4];
            }

            std::cout << "TRANSPORT: " << buf << ", " << buffer << ", " << size << ", " << counter << ". \n";
            return (counter - 4);


	}
}



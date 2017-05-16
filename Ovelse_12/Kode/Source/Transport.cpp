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
        //buffer = {0};
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
        char array[size+4] = {0};
        buffer = array;
        for(int i = 0; i<4;i++){
            buffer[i] = '2';
        }
            std::cout << "TRANSPORT: Send func received '" << buf << "' with size " << size << std::endl;

            std::cout << "TRANSPORT: Buffer 1: '" << buffer << "' with size " << strlen(buffer) << " " << sizeof(buffer) << "\n";

            memcpy(buffer+4, buf, size);
            //buffer[size+4] = '\0';
            std::cout << "TRANSPORT: Buffer 2: '" << buffer << "' with size " << strlen(buffer) << " " << sizeof(buffer) << "\n";

            buffer[SEQNO] = 4;
            buffer[TYPE] = 2;      // Send data

            std::cout << "TRANSPORT: Buffer 3: '" << buffer << "' with size " << strlen(buffer) << " " << sizeof(buffer) << "\n";

            checksum->calcChecksum (buffer, size+4);   // Checksum of header

            std::cout << "TRANSPORT: Buffer 4: '" << buffer << "' with size " << strlen(buffer) << " " << sizeof(buffer) << "\n";

            do
            {
                std::cout << "TRANSPORT: Sending buffer " << buffer << " with size: " << strlen(buffer) << std::endl;
                link->send(buffer, size+4);
                std::cout << "TRANSPORT: Waiting for ACK\n";
            }
            while(!receiveAck()); // Send till we get an ackknowledge
            std::cout << "TRANSPORT: Ack == 1 received.\n";

            old_seqNo = DEFAULT_SEQNO;

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
                //old_seqNo
            }
            while(!res);

            for(int i = 0; i < counter-4; i++)
            {
                buf[i] = buffer[i+4];
            }

            std::cout << "TRANSPORT: " << buf << ", " << buffer << ", " << size << ", " << counter << ". \n";
            old_seqNo = buffer[SEQNO];
            return (counter - 4);


	}
}



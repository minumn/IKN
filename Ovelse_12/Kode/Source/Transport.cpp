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
    Transport::Transport (short bufsize)
	{
        link = new Link::Link(bufsize+ACKSIZE);
		checksum = new Checksum();
        buffer = new char[bufsize+ACKSIZE];
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
        std::cout << "TRANSPORT: RECEIVE ACK\n";
        recvSize = link->receive(buffer, ACKSIZE);
        dataReceived = true;

        std::cout << "TRANSPORT: receiveAck func.\n";

        if (recvSize == ACKSIZE)
        {
            if(!checksum->checkChecksum(buffer, ACKSIZE) ||
                buffer[SEQNO] != seqNo ||
                buffer[TYPE] != ACK)
            {
                std::cout << "TRANSPORT: RECEIVE ACK. ACK BAD\n";
                std::cout << "TRANSPORT: ACK: " << (!checksum->checkChecksum(buffer, ACKSIZE)) << ", " << (buffer[SEQNO] != seqNo) << ", " << (buffer[TYPE] != ACK) << std::endl;
                std::cout << "TRANSPORT: " << buffer[SEQNO] << ", " << seqNo << std::endl;
                return false;
            }

            seqNo = ((buffer[SEQNO] + 1) % 2);
        }

        std::cout << "TRANSPORT: RECEIVE ACK. ACK GOOD\n";

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
        std::cout << "SENDING ACK " << ackType << "\n";
		link->send(ackBuf, ACKSIZE);
        std::cout << "TRANSPORT: Ack sent.\n";
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
        memcpy(array+4, buf, size);

        for(int i = 0; i<4;i++){
            buffer[i] = '2';
        }
            std::cout << "TRANSPORT: Send func received '" << buf << "' with size " << size << std::endl;

            std::cout << "TRANSPORT: Buffer 1: '" << array << "' with size " << strlen(array) << " " << sizeof(array) << "\n";

            memcpy(array+4, buf, size);
            array[size+4] = '\0';
            std::cout << "TRANSPORT: Buffer 2: '" << array << "' with size " << strlen(array) << " " << sizeof(array) << "\n";

            buffer[SEQNO] = seqNo;
            buffer[TYPE] = DATA;      // Send data

            std::cout << "TRANSPORT: Buffer 3: '" << array << "' with size " << strlen(array) << " " << sizeof(array) << "\n";

            checksum->calcChecksum (array, size+2);   // Checksum of header

            std::cout << "TRANSPORT: Buffer 4: '" << array << "' with size " << strlen(array) << " " << sizeof(array) << "\n";

            do
            {
                std::cout << "TRANSPORT: Sending buffer " << array << " with size: " << strlen(array) << std::endl;
                link->send(array, size+4);
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
                std::cout << "TRANPORT: Reading from link...\n";
                counter = link->receive(buffer,size);
                res = checksum->checkChecksum(buffer, counter-2);
                std::cout << "TRANSPORT: Package received with size: " << counter << " and checksum status: " << res << std::endl;
                sendAck(res);
                std::cout << "TRANSPORT: Ack sent.\n";
            }
            while(!res || !(old_seqNo == buffer[SEQNO]));

            std::cout << "TRANSPORT: Receive func: " << old_seqNo << ", " << buffer[SEQNO] << std::endl;

            memcpy(buf, buffer+4, counter-4);

            std::cout << "TRANSPORT: " << buf << ", " << buffer << ", " << size << ", " << counter << ". \n";
            old_seqNo = buffer[SEQNO];
            return (counter - 4);
	}
}



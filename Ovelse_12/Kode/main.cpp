//Main.cpp til test af LINK laget

#include <iostream>
//#include "include/link.h"
#include <string>

using namespace std;

void ssend(const char[], short);

char* buffer = new char[(50 * 2)];

int main()
{
	const string str = "hej derude.";
	const char *strr = &str;
	ssend(strr, str.length);
	
	
	return 0;
}


void ssend(const char buf[], short size)
{
	//TO DO Your own code 
	int i, k = 0;
	std::cout << "Incomming buf: " << buf << " with size : " << size << endl;

	for (i = 0; i < size; i++)
	{
		buffer[k] = 'A';
		k++;

		if (buf[i] == 'A')
		{
			buffer[k] = 'B';
			k++;
			buffer[k] = 'C';
			k++;
		}
		else if (buf[i] == 'B')
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

	std::cout << "Outgoing buffer: " << buffer << " with size: " << k << endl;

}
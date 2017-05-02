//Main.cpp til test af LINK laget

#include <iostream>
#include "include/link.h"
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

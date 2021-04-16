#include <iostream>
#include <string>
#include "query.h"


int main()
{
	QueryParser x;
	
	while (true)
	{
		std::cout << "Enter Query: \n";
		x.run();
		std::cout << "\n";
	}

}


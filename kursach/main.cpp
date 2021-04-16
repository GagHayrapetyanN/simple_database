#include <iostream>
#include <string>
#include "query.h"
#include "group.h"


int main()
{
	QueryParser x;
	
	while (true)
	{
		x.write_query();

		x.parse_query();
	}


}



#include "Uppgift1.h"
#include "Uppgift2.h"
#include "Uppgift4_PricedBook.h"


using namespace books;

int main(int argc, char* argv[]) 
{
	Circle* c = Circle::GetInstance(2.3);

	Book* theBooks[3];
	theBooks[0] = new Book("Telefonkatalogen", 245005746);
	theBooks[1] = new PricedBook("C++ direkt", 914401463, 407);
	theBooks[2] = new PricedBook("Ondskan", 916420051, 39);

	for(int i = 0; i < 3; i++)
	{
		showBook(theBooks[i]);
	}	

	return 0;	
}
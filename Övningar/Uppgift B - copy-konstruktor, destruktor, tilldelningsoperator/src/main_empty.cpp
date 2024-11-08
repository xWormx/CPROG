
#include "Elefant.h"

using namespace zoo;
using namespace std;
void printElefant(Elefant* ele)
{
	cout << ele->getAge() << " "
			<< ele->getName() << " "
			<< ele->getTrunk() << endl;
}

int main(int argc, char** argv)
{
	Elefant* elefants[3];
	elefants[0] = new Elefant("a", 10, 100);
	elefants[1] = new Elefant("b", 20, 200);
	elefants[2] = new Elefant("c", 30, 300);

	cout << "sz elefant class: " << sizeof(Elefant) << endl;
	cout << "sz elefants: " << sizeof(elefants) << endl;
	cout << "sz ptr int: " << sizeof(int*) << endl;
	cout << "sz ptr elefant: " << sizeof(Elefant*) << endl;
	cout << "sz of elements: " << sizeof(elefants) / sizeof(Elefant*) << endl;

	for(int i = 0; i < sizeof(elefants) / sizeof(Elefant*); i++)
		printElefant(elefants[i]);

	return 0;
}
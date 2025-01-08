
#include "Uppgift1.h"
#include "Uppgift2.h"
#include "Uppgift4_PricedBook.h"
#include "OperatorOverLoad.h"

using namespace books;
using namespace std;
int main(int argc, char* argv[]) 
{

	Person* pr1 = new Person("calle");
	Person* pr2 = new Person("john");

	Pointer p1(pr1);
	Pointer p2(pr2);
	Pointer p3(pr2);

	p2 = p1;
	p3 = p1;

	OOL ool1(10);
	OOL ool2(20);

	ool1 = 10 + ool2;
	std::cout << "ool1: " << ool1 << std::endl;

	ool1 = ool2 + 100;
	std::cout << "ool1: " << ool1 << std::endl;

	ool1 = ool1 + ool2;
	std::cout << "ool1: " << ool1 << std::endl;

	



	return 0;	
}


#include "Elephant.h"

using namespace std;


int main(int argc, char** argv)
{
	Elephant* e1 = Elephant::getInstance("A", 1, 1);
	Elephant* e2 = Elephant::getInstance("B", 2, 2);
	
	
	return 0;
}
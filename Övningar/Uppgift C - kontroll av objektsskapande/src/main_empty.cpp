

#include "TenAtMost.h"

using namespace std;


int main(int argc, char** argv)
{
	TenAtMost* tArr[10] = {};
	std::cout << "sz: " << sizeof(TenAtMost*) << "\n";
	
	for(int i = 0; i < sizeof(tArr) / sizeof(TenAtMost*); i++)
	{
		std::string n = std::to_string(i);
		tArr[i] = TenAtMost::getInstance(n);
		std::cout << tArr[i]->getName() << "\n";
	}

	//delete tArr[9];

	TenAtMost* t2 = TenAtMost::getInstance("20");
	TenAtMost* t3 = TenAtMost::getInstance("30");

	return 0;
}
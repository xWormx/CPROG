//
//  c++_empty
//  

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {

	std::cout << (1 >> 2) << std::endl;
	int bitPattern = 3;
	//0000 0000	  0000 0000	  0000 0000	  0000 0000
	for(int i = sizeof(bitPattern) * 8; i > 0; i--)
	{
		int bitValue = 1;
		//if(i % 4 == 0)
		//	std::cout << " ";
		
		if(bitPattern & (bitValue << i))
			std::cout << 1;
		else
			std::cout << 0;
			
	}
	std::cout << "\n";
	return 0;
}
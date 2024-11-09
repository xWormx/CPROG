

#include "WordList.h"

using namespace std;


int main(int argc, char** argv)
{
	std::vector<string> w1 = {"HEJ", "DÅ"};

	WordList wl1(w1);
	WordList wl2 = wl1;
	wl1.printWords();
	wl2.printWords();

	return 0;
}
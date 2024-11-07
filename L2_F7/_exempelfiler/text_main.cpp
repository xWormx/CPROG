#include "text.h"
#include <iostream>

using namespace std;


void funk(Text t2) {
}

int main() {

	// Initierar Text-objekt med en lista.
	Text t5 {'a','b','c'};

	// Skriver ut ett Text-objekt med den egendefinierade utskriftsoperatorn.
	std::cout << "t5: " << t5 << std::endl;

	// Nedan, inga forandringar!
	Text t1("Jozef");
	Text t3("Stefan");
	Text t4;

	t3 = t1;
	t3[2] = 's';
	for (int i = 0; i < t3.length(); i++){
		cout << t3[i];
	}
	cout << endl;

	std::cout << "t1: " << t1 << std::endl;
	std::cout << "t3: " << t3 << std::endl;

	cin.get();
	
}
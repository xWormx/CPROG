/*

F3 och F4

Lagringsklasser

	auto: Anges istället för typen för en initierad variabel och kompilatorn härleder variabelns typ
		  från initieringsuttrycket.

	static: lokal variabel som överlever funktionsanropet och behåller värden mellan anropen.
			Det har tillkommit flera andra betydelser både i C och C++.

	extern: Betyder att denna deklaration inte är en definition, variabeln definieras någon annanstans
			extern-deklarationer får INTE innehålla initieringar.
			Det kan finnas godtyckligt många extern-deklarationer av en variabel.
			Funktionsprotoryper är alltid implicit extern-deklarationer.

	
	typedef: Definitionen gäller ett nytt namn på en typ.
			 Förutom ordet typedef ser det ut som en variabeldeklaration


*/

#include <iostream>
#include <string>
#include "cstring"
#include "externValue.h"
#include "DynamicMem.h"

void affectNumber_A(int a)
{
	static int staticNum = 0;
	staticNum += a;
	std::cout << "staticNum: " << staticNum << std::endl;
}

void affectNumber_B(int a)
{
	
}

extern int externValue;

typedef int myInt;

int main(int argc, char* argv[]) 
{
	auto pi = 3.1415;

	double number = pi + 3.14;

	std::cout << number << std::endl;

	auto names = {"adam", "bertil", "ceasar"};

	for(auto name : names)
		std::cout << name << std::endl;


	affectNumber_A(3);
	affectNumber_A(3);


	std::cout << "externValue: " << externValue << std::endl;

	myInt anInt = 3 + externValue;

	std::cout << "myInt anInt =  " << anInt << std::endl;
}
/*
Använd std::strncpy() istället för strcpy_s()
*/

#include <cstring>
#include <iostream>

#include <stdexcept>
#include "text.h"


// Utskriftsoperator for const Text&
std::ostream& operator<<(std::ostream& os, const Text& t){
	// Access till privata medlemmar, "friend" dekl. behovs!
	for (int i=0; i < t.size; ++i)
		os << t.cptr[i];

	// Alternativt med publik set/get, "friend" dekl. behovs INTE!	
	//for (int i=0; i < t.getSize(); ++i)
	//	os << t.getCptr()[i];

	return os;
}

// Exempel på konstruktor med initieringslista som parameter(Labb2). 
Text::Text(const std::initializer_list<char>& ilist):size(static_cast<int>(ilist.size()) )
{
	std::cout << "Antal element i listan: " << ilist.size() << std::endl;
	cptr = new char[size];
	int i=0;
	for (char e: ilist){
		cptr[i++] = e;
	}
}


Text::Text():size(0), cptr(nullptr) 
{
}

//The returned length does not include the null character '\0'.
Text::Text(const char* str) : size(std::strlen(str)+1),
cptr(new char[size])
{
	//strcpy_s(cptr, size, str);
	std::strncpy(cptr, str, size);
}

Text::Text(const Text& other) 
{
	size = other.size;
	cptr = new char[size];

	//strcpy_s(cptr, size, other.cptr);
	std::strncpy(cptr, other.cptr, size);
}

const Text& Text::operator=(const Text& other) 
{
	if (this != &other) {
		delete[] cptr;
		size = other.size;
		cptr = new char[other.size];

		std::strncpy(cptr, other.cptr, size);
		//strcpy_s(cptr, size, other.cptr);
	}
	return *this;
}

Text::Text(Text&& other) 
{
	size = other.size;
	cptr = other.cptr;
	other.cptr = nullptr;
	other.size = 0;
}

Text::~Text()
{
	delete[] cptr;
}

char& Text::operator[](int pos) 
{
	if (pos < 0 || pos >= size)
		throw std::out_of_range("Text index out of bounds");
	return cptr[pos];
}

int Text::length() 
{
	return (size == 0) ? 0 : size - 1;
}
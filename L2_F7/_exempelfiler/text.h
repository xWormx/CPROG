#ifndef __TEXT
#define __TEXT
#include <initializer_list>
#include <iostream>

class Text
{
public:
	// Exempel på konstruktor med initieringslista som parameter(Labb2). 
	Text(const std::initializer_list<char>& ilist);

	Text();
	Text(const char* str);

	Text(const Text& other); //ctor
	Text(Text&& other); //move
	const Text& operator=(const Text& other); //tilldeln.op.
	char& operator[](int pos); //index.op.
	int length();
	~Text();

	// public set/get vid utskrift utan "friend" deklaration.
	//int getSize() const {return size;}
	//char* getCptr() const {return cptr;}
	
private:
	int size;
	char* cptr;

	// Exempel på "friend"-deklaration. I detta fall ligger utskriftsoperatorn som "fri funktion" i filen "Main.cpp".
	// "friend"-deklaration behövs bara vid access till privata medlemmar!
	friend std::ostream& operator<<(std::ostream& os, const Text& t);
};

#endif


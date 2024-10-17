/*

	Funktioner måste deklareras innan de kan användas.
	En funktionsdeklaration gör att funktionen kan användas innan dess definition

	Ex:

	int funktion(int a);  <------ Deklaration av funktionen funktion()

	int main(int argc, char **argv)
	{
		int a = funktion(3);  <------------ Eftersom funktionen är deklarerad kan den kallas på här, innan definitionen.

		return 0;
	}

	int funktion(int a)   <--------- Definition
	{
		std::cout << a << std::endl;

		return a;
	}

*/

#include <iostream>
#include <string>
#include "cstring"


int add(int a, int b);

int main(int argc, char* argv[]) {

	int a = add(2, 3);
	std::cout << "a is 2 + 3 which is : " << a << std::endl; 
	
	char arr[6] = "calle";
	char copyArr[6];

	printf("%s\n", arr);

	strcpy(copyArr, arr);

	printf("%s has %d characters in it\n", copyArr, strlen(copyArr));
	
	for(int i = 0; i < strlen(copyArr); i++)
	{
		printf("%d", i+1);
	}

	return 0;
}
int add(int a, int b)
{
	return a + b;
}



/*

	Preprocessor direktiv
	#include-direktiv ersätt med innehållet i filen

	<filnam> - headerfilen sökes i standardkataloger
	"filnamn" - headerfilen sökes först i aktuell katalog och katalogerna i 
				"include-sökvägen", i andra han i standardkataloger.

	för att komma åt ett namn i en namnrymd (namespace) skrivs: 
	[namnrymdens namn] [::] [aktuellt namn]
	
	ex: 
	std::cout << "hej" << std:endl;
	
	:: kalla räckvidsoperatorn

	man kan öppna en namnrymd genom att använda using namespace-direktiv
	ex:
	using namespace std;

	primitiva typer

	Heltal:
		char
		short
		int
		long
		long long
	
	Flyttal:
		float 
		double
		long double

	Boolean:
		bool

	förutom char (som är en byte) är inte storleken för dessa typer definierad av standarden, utan bestäms
	av datorarkitekturen i aktuell dator.
	Operatorn sizeof(typ) ger storleken i antal bytes
*/


#include <iostream> 
#include <string>
#include "Constants.h"

int main(int argc, char* argv[]) {
	std::string s1 = "Hejsan";
	std::string gitTest = "GIT TEST";
	std::cout << s1 << std::endl << gitTest << std::endl;
	return 0;
}
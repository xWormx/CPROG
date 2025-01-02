

#include "TenAtMost.h"
#include "DjurKlasser.h"
#include <vector>

using namespace std;




void clearbit(unsigned long& week, int bitPlace){
	week &= ~(1 << bitPlace);
}

void setBit(unsigned long& week, int bitPlace){
	//clearbit(week, bitPlace); vi behöver nog inte clear biten, då vi OR'ar 1 på platsen vilket gör att den blir 1 oavsett.
	week |= (1 << bitPlace);
}	

bool checkBit(unsigned long& week, int bitPlace){
	/*
		week: 0001 1111 0110 1110
							 ^---		
		kolla bit 4
	*/

	return ((1 << bitPlace) & week);
}

void printBitsInWeek(unsigned long& week){
	std::cout << std::endl;
	for(int i = (sizeof(unsigned long) * 8) - 1; i >= 0; i--){

		if(week & (1 << i))
			std::cout << 1;
		else
			std::cout << 0;

					
		if(i % 8 == 0)
			std::cout << " ";
	}
}

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


	vector<Djur*> allaDjur;
	int summaVarde = 0;
	int snabelSumma = 0;

	for(Djur* d : allaDjur){
		summaVarde += d->getVarde();
		Elefant* e;
		if(e = dynamic_cast<Elefant*>(d)){
			snabelSumma += e->getSnabel();
		}
	}

	cout << "Värdet totalt: " << summaVarde << endl;
	
	if(snabelSumma <= 0)
		cout << "Inga elefatner! \n";
	else
		cout << "Genomsnittlig snabelsumma: " << static_cast<double>(snabelSumma) / allaDjur.size() << endl;


	unsigned int ui = 1235512;
	int value = 255;
	int place = 16;
	// nollställ ett värde på en plats
	/*
		15 = 1111, 3 = 11 ( beror på hur många bitar en sekvens är! )
		ui = 0001 1101 1100 1111
		&= ~(0000 1111 0000 0000) = &= (1111 0000 1111 1111) men det värdet är svårare att bara lista ut!
		->  (15 << 12)

		resulterar i följande:
		ui = 0001 0000 1100 1111

		sen kan vi OR'a ihop det önskade värdet på platsen.

		value = 0110;
		ui |= (value << 12);
		ui: 0001 0000 1100 1111
		|= 	0000 0110 1100 1111



	*/

	unsigned long week1 = 15;

	printBitsInWeek(week1);
	clearbit(week1, 0);
	printBitsInWeek(week1);
	setBit(week1, 8);
	printBitsInWeek(week1);
	
	return 0;
}

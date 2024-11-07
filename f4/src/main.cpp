// Carl-Johan Larson Eliasson

#include <iostream>
#include "IntVector.h"

// Funktion som returnerar en IntVector, används endast för test av din kod.
IntVector func() 
{
    // OBS. Ingen kod skall ändras eller skrivas till i denna funktion.
	IntVector local{ 43,43,53,73 };
	return local;
}

int main () 
{
    /*  OBS. Ingen kod skall ändras eller skrivas till i denna funktion.
     *  När nedanstående utskrifter till konsollen körs, så skall följande skrivas: 
     *  vek4: 43 43 53 73
     *  vek3[3]: 20
     *  vek3: 10 11 16 20 23 
     *  vek4: 10 11 16 75 23 
     *  vek5, size: 6
     *  vek5[5]: 46
     *  vek5: 10 11 16 75 23 46
     */
    
    IntVector vek1 { 10,11,16,20,23 };
	IntVector vek2;
	IntVector vek3( vek1 );
	IntVector vek4( func() );
	
	std::cout << "vek4: " << vek4 << std::endl;
	
	vek4 = vek3;
	vek4[3] = 75;
	std::cout << "vek3[3]: " << vek3[3] << std::endl;
	
	std::cout << "vek3: " << vek3 << std::endl;
	std::cout << "vek4: " << vek4 << std::endl;
	
	vek4.push_back(46);
	
	const IntVector vek5(vek4);
	std::cout << "vek5, size: " << vek5.size() << std::endl;
	std::cout << "vek5[5]: " << vek5[5] << std::endl;
	std::cout << "vek5: " << vek5 << std::endl;

	return 0;
}
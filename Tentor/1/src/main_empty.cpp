

#include <iostream>
#include <vector>
#include <string>

using namespace std;





/*
	----Skriv om klasshierarki med arv utan värdesemantik .--------

	1. public fabriksfunktion
	2. virtuell destruktor och eventuel funktion
	3. protected konstruktor
	4. copy konstruktor och tilldelgninsoperator deletade ( eller satta som private )
	5. skapa en samling med pekare till basklassobjekt och push_back() med subklasserna
	6. loopa igenom samling och kolla specifik typ m.h.a
		if(SUBKLASS* s = dynamic_cast<SUBKLASS*>(basKlass);

	
	---- Bitmanipuleringsfårgor -----

	0xff = 1111
	0xf  = 0011

	1. printa bitar:
		for(int i = 8*sizeof(TYP) - 1; i >= 0; i--)
		{
			value & (1 << i) ? cout << '1' : cout << '0';
		}

	2. sätt bitar:
		value |= (newValue << steps);

	3. nollställ bitar:
		value &= ~(0xff << steps); nollställer 1111 antalet bitar

	4. skifta bitar åt höger och sätt in från vänster:
		result = (value >> steps) | (value << 8*sizeof(TYP) - steps);

	5. byt plats på bitar, förutsatt att ett nytt mönster är 4 bitar långt
		oldPattern = (value >> 4*steps) & 0xff;
		value &= ~(0xff << 4*steps)
		value |= (newPattern << 4*steps);
		
		byt platts på 1 och 4
		1100 1111 0000 10001


	----- Operatoröverlagring --------
	==, <, >, <=, >=, !=

	const TYP& operator+=()
	TYP operator+()
	TYP operator++() prefix
	TYP operator++(int) postfix
	TYP operator--() prefix
	TYP operator--(int) postfix

	utskriftoperatorn <<
	i klassen
	friend std::ostream& operator<<(std::ostream& os, const TYP& typ);

	utanför klassen
	std::ostream& operator<<(std::ostream&, const TYP& typ)
	{ return os << typ.data; }


	----- Klasser med värdesemantik ------

	1. Kopykonstruktor
		TYP(const TYP& other) : membs(other.membs)
		{
			// Om det finns dynamiskt data
			ptrData = new ptrData[size];
			for(int i = 0; i < size; i++)
			{
				ptrData[i] = other.ptrData[i];
			}
		}
	2. Tilldelsningsoperator
		const TYP& operator=(const TYP& other)
		{
			if(this != &other)
			{
				delete[] ptrData;
				membs = other.membs;
				ptrData = new ptrData[size];
				for(int i = 0; i < size; i++)
					ptrData[i] = other.ptrData[i]; 
			}
			return *this;
		}
	3. destruktor
		~TYP()
		{
			delete[] ptrData;
		}

	primtiva typer kopierar och tilldelar sig självt.
	*pekare behöver hanteras.

*/

// Uppgift 4

class Vehicle
{
	public:
		const int& getPassengers() const { return passenger_load; }
		const string& getReg() const { return reg_nr; }
		virtual void message() const = 0; // abstrakt klass, ren virtuell funktion
		virtual ~Vehicle(){} //virtuell destruktor

	protected:
		Vehicle(string regNr, int pLoad) : reg_nr(regNr), passenger_load(pLoad) {}

	private:
		string reg_nr;
		int passenger_load;

		Vehicle(const Vehicle&) = delete;
		const Vehicle& operator=(const Vehicle&) = delete;
};

class Car : public Vehicle
{
	public:
		static Car* GetInstance(string regNr = "", int pLoad = 0) { return new Car(regNr, pLoad);}
		void message() const { cout << getReg() << " Typ: Bil\n";}
	protected:
		Car(string regNr = "", int pLoad = 0) : Vehicle(regNr, pLoad) {}
};

class Truck : public Vehicle
{
	public:
		static Truck* GetInstance(string regNr = "", int pLoad = 0, int maxLoad = 0) { return new Truck(regNr, pLoad, maxLoad); }
		int getMaxLoad() const { return max_load; }
		void message() const { cout << getReg() << " Typ: Lastbil\n"; }
	
	protected:
		Truck(string regNr = "", int pLoad = 0, int maxLoad = 0) : Vehicle(regNr, pLoad), max_load(maxLoad){}
		
	private:
		int max_load;
};

int main(int argc, char** argv)
{

	vector<Vehicle*> vehicles;

	vehicles.push_back(Car::GetInstance("ABC 123", 5));
	vehicles.push_back(Truck::GetInstance("TUV 987", 2, 30000));

	int totalAntPassagerare = 0;
	int totalAntBilPassagerare = 0;

	for(Vehicle* v : vehicles)
	{
		if(Car *c = dynamic_cast<Car*>(v))
			totalAntBilPassagerare += c->getPassengers();
		
		totalAntPassagerare += v->getPassengers();

		v->message();
	}

	cout << "Total antal passagerare = " << totalAntPassagerare << endl;
	cout << "Total antal bilpassagerare = " << totalAntBilPassagerare << endl;


	return 0;
}
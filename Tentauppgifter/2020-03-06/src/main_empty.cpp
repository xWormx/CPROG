
#include <string>
#include <iostream>
#include <vector>



class Rectangle
{
	public:
		Rectangle(double w = 0, double h = 0) : width(w), height(h){}
		double area() const {return width*height;}
		double getWidth() const { return width; }
		double getHeight() const { return height; } 

		const bool operator==(const Rectangle& other) const;
		const Rectangle& operator+=(const Rectangle& other);
		const Rectangle& operator+=(int other);
		
		Rectangle operator+(const Rectangle& rhs) const;
		Rectangle operator+(const int rhs) const;

		const Rectangle& operator++(); // prefix
		Rectangle operator++(int); // postfix

		

	private:
		double width;
		double height;

		friend std::ostream& operator<<(std::ostream& os, const Rectangle& r);
};

// förslag för int som vänsterled
inline const Rectangle operator+(int lhs, const Rectangle& rhs)
{
	return rhs + lhs;
}

const bool Rectangle::operator==(const Rectangle& other) const
{
	return (width == other.getWidth() && 
			height == other.getHeight());
}

std::ostream& operator<<(std::ostream& os, const Rectangle& r)
{
	return os << "w: " << r.getWidth() << ", h: " << r.getHeight() << ", area: " << r.area();
}

/*
	Recangle a(1,2);
	Recangle b(1,2);

	a += b;
*/

const Rectangle& Rectangle::operator+=(const Rectangle& other)
{
	width += other.getWidth();
	height += other.getHeight();

	return *this;
}

const Rectangle& Rectangle::operator+=(int rhs)
{
	width += rhs;
	height += rhs;
	return *this;
}

Rectangle Rectangle::operator+(const Rectangle& rhs) const
{
	Rectangle temp(*this);
	return temp += rhs;
}

Rectangle Rectangle::operator+(int rhs) const
{
	Rectangle temp(*this);
	return temp += rhs;
}

const Rectangle& Rectangle::operator++() // prefix
{
	return (*this) += 1;
}


Rectangle Rectangle::operator++(int) // postfix
{
	Rectangle temp(*this);
	*this += 1;
	return temp;
}


/*
	1001 0101
	0000 1000 // set bit 4 -> week |= (1 << 4)

	1001 1101 // clear bit 4 -> week &= ~(1 << 4)
	1111 0111
   =1001 0101



*/

void setBit(unsigned long& week, unsigned int bitPlace)
{
	week |= (1UL << bitPlace);
}

void clearBit(unsigned long& week, unsigned int bitPlace)
{
	week &= ~(1UL << bitPlace);
}

bool checkBit(unsigned long& week, unsigned int bitPlace)
{
	return (week & (1 << bitPlace));
}

void printBits(unsigned long week)
{
	for(int i = 8*sizeof(week)-1; i >= 0; i--)
	{
		if(week & (1 << i))
			std::cout << '1';
		else
			std::cout << '0';
		
		if(i % 8 == 0)
			std::cout << ' ';
	}
}


class Managed
{
	public:
		Managed(std::string d) : data(d) { objects.push_back(this);}

		// copykonstruktor behövs för att vi måste lagra en till pekare i
		// 'objects'.
		Managed(const Managed& other) : data(other.data)
		{
			objects.push_back(this);
		}

		// Vid tilldelning så kopiers inte pekaren som finns i objects
		// eftersom den redan existerar.
		// det enda som händer är att this.data blir other.data
		// men den kopieringen, av std::string sker automatiskt via 
		// std::string's egen tilldelgninsoperator.
		Managed& operator=(const Managed&) = default;

		// destruktorn behövs för att ta bort pekare till detta objects
		// ur den statiska samlingen av pekare till Manged objects.
		~Managed()
		{
			for(int i = 0; i < objects.size(); ++i)
			{
				if(objects[i] == this)
				{
					objects.erase(objects.begin() + i);
				}
				break; // hoppa ur då vi tagit bort ett objekt.
			}
		}


		std::string get_data() const {return data; }

	private:
		std::string data;
		static std::vector<Managed*> objects;
}; // Managed

std::vector<Managed*> Managed::objects; // definition


/*

	Managed a("a");
	Managed b(a); // behövs en copy construktor?
					// vi vill inte göra push_back() på a igen efter som
					// den pekaren redan finns registrerad när a instantieras.

	Managed c("c");

	b = c;


*/


class Person
{
	public:
		std::string getNamn() const { return namn; }
		int getArsinkomst() const { return arsinkomst; }
		virtual void skrivUt() const = 0; // ABSTRAKT KLASS
		virtual ~Person(){} // ALLTID VID ARV!
	protected:
		// FÖRBJUD OBJEKTSKAPANDE
		Person(std::string n, int arsInk) : namn(n), arsinkomst(arsInk){}

	private:
		std::string namn;
		int arsinkomst;
		// TA BORT KOPIERING
		Person(const Person&) = delete;
		// TA BORT TILLDELNING
		const Person& operator=(const Person&) = delete;
};



class Anstalld : public Person
{
	public:
		static Anstalld* GetInstance(std::string n, int arsInk, int manLon); 
		int getManadslon() const {return manadslon;}
		void skrivUt() const;
	protected:
		// DENNA KAN VA PRIVATE OCKSÅ
		// FÖRBJUD OBJEKTSKAPANDE
		Anstalld(std::string n, int arsInk, int manLon) : Person(n, arsInk), manadslon(manLon)
		{}	
	private:
		int manadslon;
};

Anstalld* Anstalld::GetInstance(std::string n, int arsInk, int manLon)
{
	return new Anstalld(n,arsInk, manLon);
}

void Anstalld::skrivUt() const
{
	std::cout << "Namn: " << getNamn() << ", Årsinkomst: " << getArsinkomst() << ", Månadslön: " << getManadslon();
}




int main(int argc, char* argv[]) 
{
	
	Rectangle r1(2,4), r2(2,4);
	Rectangle r3(0,0), r4;
	Rectangle r5 = r1 + r2;

	((r1==r2) ? r4+=0 : r4+=1);
	r2 += r1;
	r2 += 2;
	r3 = r2 + r4 + r5 + 5;
	r3++;
	++r3;
	std::cout << "r3: " << r3 << '\n';

	unsigned long w = 0xff;
	printBits(w);

	std::cout << '\n';
	Anstalld* anställd = Anstalld::GetInstance("JOHN", 1, 2);
	anställd->skrivUt();
	return 0;	
}

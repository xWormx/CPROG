
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

// uppgift 1

class Klocka
{
	public:
		Klocka(int tim = 0, int min = 0, int sek = 0);
		void setTime(int tim, int min, int sek);
		void getTime(int& tim, int& min, int& sek) const;

		//void ticka(); // Tick, Klockan ökar en sek.

		bool operator==(const Klocka&);
		bool operator!=(const Klocka&);
		bool operator<(const Klocka&);
		bool operator>(const Klocka&);
		bool operator<=(const Klocka&);
		bool operator>=(const Klocka&);
	
		const Klocka& operator++(); // prefix

	private:
		int t, m, s; // tim, min, sek

		friend ostream& operator<<(ostream&, const Klocka&);
};

const Klocka& Klocka::operator++()
{
	if(++s > 60)
		if(++m > 60)
			++t;	
	s = 0;
	m = 0;
	return *this;
}

bool Klocka::operator==(const Klocka& other)
{
	if( t == other.t &&
		m == other.m &&
		s == other.s )
		return true;
	
	return false;
}

bool Klocka::operator!=(const Klocka& other)
{
	return !(*this == other);
}

bool Klocka::operator<(const Klocka& other)
{
	if(t < other.t ||
		t == other.t && m < other.m ||
		t == other.t && m == other.m && s < other.s)
		return true;
	
	return false;
}

bool Klocka::operator>(const Klocka& other)
{
	return !(*this < other) && !(*this == other);
}

bool Klocka::operator<=(const Klocka& other)
{
	return (*this < other || *this == other);
}

bool Klocka::operator>=(const Klocka& other)
{
	return !(*this < other);
}

ostream& operator<<(ostream& os, const Klocka& kl)
{
	if(kl.t < 10)
		os << '0';
	os << kl.t << ":";

	if(kl.m < 10)
		os << '0';
	os << kl.m << ":";
	
	if(kl.s < 10)
		os << '0';
	os << kl.s;
	
	return os;
}

Klocka::Klocka(int tim, int min, int sek)
{
	setTime(tim, min, sek);
}

void Klocka::setTime(int tim, int min, int sek)
{
	t = tim;
	m = min;
	s = sek;
}

void Klocka::getTime(int& tim, int& min, int& sek) const
{
	tim = t;
	min = m;
	sek = s;
}

/* void Klocka::ticka()
{
	s = (s+1 ) & 60;
	if(s==0) 
	{
		m= (m+1) % 60;
		if(m== 0)
			t = (t+1) % 25;
	}
}
 */


// Uppgift 2

void visaBitar(unsigned int value)
{
	
	cout << "( Tal i decimalform = Tal i binäform )\n";
	cout << value << " = ";
	
	for(int i = (8*sizeof(value))-1; i >= 0; i--)
	{
		if(value & (1 << i))
			std::cout << "1";
		else	
			std::cout << "0";
		
		if(i % 8 == 0)
			std::cout << " ";
	}
}

unsigned int bitskiftLeft(unsigned int value, int steps)
{
	return (value << steps);
}

unsigned int bitskiftRight(unsigned int value, int steps)
{
	return (value >> steps) | (value << (sizeof(unsigned int) * 8 - steps));
}



// Uppgift 3
class Book
{
	public:
		Book(const string& the_title, const string& the_author);
		Book(const Book&);
		const Book& operator=(const Book&);
		void addInfo(string new_info);
		string getInfo(int index);
		string getTitle() const;
		string getAuthor() const;
		~Book();

	private:
		string title, author;
		string* info; // Detta är en array med string objekt, INTE en string med rum för x antal symboler.
		int counter;
};

Book::Book(const string& the_title, const string& the_author) : 
	title(the_title), author(the_author)
{
	info = new string[100];
	counter = 0;
}

Book::Book(const Book& other) : title(other.title), author(other.author), counter(other.counter)
{
	info = new string[100];
	for(int i = 0; i < 100; i++)
		info[i] = other.info[i];
}

const Book& Book::operator=(const Book& other)
{
	if(this != &other)
	{
		delete[] info;

		title = other.title;
		author = other.author;
		counter = other.counter;

		info = new string[100];	
		for(int i = 0; i < 100; i++)
			info[i] = other.info[i];
		
	}
	return *this;
}

Book::~Book()
{
	delete[] info;
}

void Book::addInfo(string new_info)
{
	info[counter++] = new_info; // tillderlar string[0] data, typ string[0] = "lite text"
}

string Book::getInfo(int index)
{
	return info[index];
}

string Book::getTitle() const
{
	return title;
}

string Book::getAuthor() const
{
	return author;
}

int main(int argc, char* argv[]) 
{
	int timme, minut, sekund; 
	Klocka refKlocka; 
	refKlocka.setTime(9, 29, 45); 
	Klocka minKlocka( 9, 30, 5 ); 

	if(refKlocka < minKlocka)
	{

	}
	std::cout << "minKlocka = " << minKlocka << std::endl; 
	minKlocka.getTime( timme, minut, sekund ); 
	++minKlocka; 
	if (minKlocka <= refKlocka) 
		{ std::cout << "min är mindre än din.\n"; } 


	visaBitar( 780 );
	cout << "\n\nbitkskift vänster 8 bitar:\n";
	visaBitar( bitskiftLeft(780, 8) );
	cout << "\n\nbitkskift höger 8 bitar:\n";
	visaBitar( bitskiftRight(780, 8) );  
	return 0;	

}
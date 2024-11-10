/*
Nedan finns en liten klasshierarki: basklassen Animal och 
Elephant. Det kommer att finnas många fler subklasser till Animal.

Tillämpningar ska inte kunna skapa objekt av klassen Animal, 
som bara ska kunna användas som basklass till sina subklasser. 
Objekt av klassen Elephant får bara skapas dynamiskt.

Komplettera/modifiera klasshierarkin så att tillämpningar tvingas 
iaktta ovanstående regler.

class Animal {
public:
   Animal( std::string n, int w );
   virtual ~Animal();
   std::string getName() const;
   int getWeight() const;
private:
   std::string name;
   int weight;
}; 

class Elephant  :  public Animal {
public:
   Elephant( std:.string n, int w, int tl );
   int getTrunkLength() const;
private:
   int trunkLength;
}; 

Animal::Animal(std::string n, int w) : name( n ), weight( w ) { }

Animal::~Animal() { }

std::string Animal::getName() const {
   return name;
}

int Animal::getWeight() const{
   return weight;
}

Elephant::Elephant( std:.string n, int w, int tl ) : Animal( n, w ), trunkLength( tl ) { }

int Elephant::getTrunkLength() const {
   return trunkLength;
}
*/
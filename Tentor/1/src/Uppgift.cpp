/*
Nedan finns ett C++-program bestående av två klasser och en fri funktion i en namnrymd zoo samt en main-funktion. 
Medlemsfunktioner i klasserna är definierade inom klassdefinitionerna. Allting är gjort i en källkodsfil.

Dela upp denna fil så att varje klass resp. main utgör separatkompilerade moduler - klasserna med var sin headerfil och 
.cpp-fil, med #include-direktiv, #include-guards o.s.v. Klassernas medlemsfunktioner ska vara definierade i .cpp-filerna.
Direktivet using namespace får  inte användas i headerfiler.


#include <string>
#include <iostream>

using namespace std;

namespace zoo {
  class Animal {
  public:
    Animal( string n, int w ) : name( n ), weight( w ) {}
    string getName() const { return name; }
    int getWeight() const { return weight; }

  private:
    string name;
    int weight;
  };

  class Elefant  :  public Animal {
  public:
    Elefant( string n, int w, int t ):Animal( n, w ), trunk( t ) {}
    int getTrunk() const{ return trunk; }

  private:
    int trunk;
  };

  void printElefant(  const Elefant* ele  ) {
    cout << ele->getName() << " "
       << ele->getWeight() << " "
       << ele->getTrunk() << endl;
  }
} // namespace zoo

using namespace zoo;
int main() {
  Elefant* elefants[3];
  elefants[0] = new Elefant( "Jumbo", 600, 170 );
  elefants[1] = new Elefant( "Mumbo", 500, 160 );
  elefants[2] = new Elefant( "Lillen", 800, 200 );
  for( int i = 0; i < 3; ++i )
    printElefant( elefants[i] );
  return 0;
}

*/

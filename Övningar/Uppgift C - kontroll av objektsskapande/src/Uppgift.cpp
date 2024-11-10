/*
Komplettera/modifiera följande klass så att en tillämpning bara kan skapa objekt av den dynamiskt 
och kan ha högst 10 objekt av klassen samtidigt. 
Om tillämpningen försöker skapa ett elfte objekt ska undantaget std::out_of_range genereras.

Om tillämpningen först har skapat 10 objekt men sedan tagit bort några så får den skapa nya objekt, 
men alltså högst 10 vid varje givet tillfälle.

class TenAtMost {
public:
   TenAtMost( std::string n );
   std::string getName() const;
private:
  std::string name;
}; 

TenAtMost::TenAtMost( std::string n ) : name( n ){}

std::string TenAtMost::getName() const{
   return name;
}
*/
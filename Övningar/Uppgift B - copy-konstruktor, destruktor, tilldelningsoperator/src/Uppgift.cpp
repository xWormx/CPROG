/*
Denna uppgift består av fem deluppgifter med var sin klass. Det är meningen att samtliga klasser 
skall ha värdesemantik. 
Din uppgift är att avgöra om det behövs en copy- konstruktor, en destruktor resp. en tilldelningsoperator 
för dessa klasser och i förekommande fall implementera dem. 
Om ingen copy-konstruktor, destruktor eller tilldelningsoperator behövs 
räcker det med att ange detta. Du behöver inte bry dig om C++11s move-konstruktor.

a) Klassen Vector skall fungera som en dynamisk vektor av heltal, vektorn skall som sagt ha 
värdesemantik:
class Vector {
public:
    Vector(int n):siz( n ), data( new int[siz] ){}
    int& operator[](int index) { return data[index]; }
    ...
private:
   int siz;
   int* data;
}; // Vector


b) Klassen WordList tänks fungera som ett slags ordförteckning. 
Orden lagras internt i standardbibliotekets vector, WordList omsluter bara denna vector:

class WordList {
public:
   void add(std::string word){
      words.push_back(word);
   }  
   std::string remove(std::string word){
      for(int i = 0; i < words.size(); ++i)
         if (words[i] == word){
           std::string w = words[i];
           words.erase(words.begin() + i);
           return w;
         } // if
   } // remove
  ... 
private:
   std::vector<std::string> words;
}; // WordList



c) Objekt av klassen Managed innehåller bara en sträng, 
klassen håller dock även reda på alla sina objekt i varje ögonblick i en statisk vektor 
av pekare till objekten:

class Managed {
public:
   Managed(std::string d): data(d){ objects.push_back(this);
}
   std::string get_data() const { return data; }
   ...
private:
   std::string data;
   static std::vector<Managed*> objects;
}; // Managed

std::vector<Managed*> Managed::objects; // Definition



d) Objekt av klassen Counted innehåller bara en sträng, 
men klassen ska hålla reda på hur många objekt av den som finns, 
med hjälp av den statiska variabeln count.

class Counted {
public:
  Counted(std::string d);
  std::string get() const;
  static int getCount();
private:
  static int count;
  std::string data;
};

int Counted::count = 0;

Counted::Counted(std::string d):data(d){
  count++;
}   

std::string Counted::get() const { return data; }
int Counted::getCount() { return count; }



e) Objekt av klassen Valued innehåller bara en sträng, 
men klassen håller reda på vilka värden på strängarna som finns i dess objekt, 
och hur många objekt som innehåller varje värde. 
Detta görs med hjälp av en map med strängen som nyckel och antalet som värde.

class Valued{
public:
  Valued(std::string str);
  static std::map<std::string,int>& getValues();
private:
  std::string data;
  static std::map<std::string, int> values;
};

std::map<std::string, int> Valued::values;

Valued::Valued(std::string str):data(str){
  values[str]++; // Blir 1 första gången
} 

std::map<std::string,int>& Valued::getValues(){
  return values;
}
*/
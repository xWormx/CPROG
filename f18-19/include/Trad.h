//  Trad.h
//  labb4_tree


#ifndef TRAD_H
#define TRAD_H

#include <iostream>

template <typename T>
class Trad {
  
public:
  Trad() : rot(0) {};                    // default konstruktor
  Trad( T d ) { rot = new Nod(d); };
  Trad( const Trad& t ) { kopiera(t); };   // kopieringskonstruktor
  ~Trad() { delete rot; };
  
  bool tomt() const { return !rot; };

  T& varde() const
  {
    koll();
    return rot->data;
  };

  Trad& v_barn() const
  {
    koll();
    return *rot->vanster;
  };

  Trad& h_barn() const
  {
    koll();
    return *rot->hoger;
  };

  Trad& operator= ( const Trad& );
  bool operator== ( const Trad& ) const;
  void skriv_ut() const;
  void satt_in(T d);
  int sok(T d);
  
private:

  class Nod {
    friend class Trad;
    T data;
    Trad *vanster, *hoger;
    Nod( T d ) : data( d ), vanster( new Trad ), hoger( new Trad ) {};
    ~Nod()
    {
      delete vanster;
      delete hoger;
    };
  }; // end class Nod

  Nod *rot;
  void koll() const
  {
    if ( tomt() )
      throw std::range_error( "Trad" );
  }
  void kopiera( const Trad& t );
};

template <typename T>
void Trad<T>::satt_in(T d)
{
    if(tomt())
        rot = new Nod(d);
    else
    {
        if(d < varde())
        {
            v_barn().satt_in(d);
        }
        else
        {
            h_barn().satt_in(d);
        }
    }
}

template <typename T>
int Trad<T>::sok(T d)
{
    if(!tomt())
    {
        if(d == varde())
            return 1;
        else if(d < varde())
            return v_barn().sok(d);
        else
            return h_barn().sok(d);
    }

    return 0;
}

template <typename T>
void Trad<T>::kopiera( const Trad& t)
{
  //std::cout << "*** Trad::kopiera\n";
  if (t.tomt())
    rot = 0;
  else
  {
    rot = new Nod( t.varde());
    v_barn().kopiera( t.v_barn());
    h_barn().kopiera( t.h_barn());
  }
}

template <typename T>
Trad<T>& Trad<T>::operator= (const Trad& t)
{
  //std::cout << "*** Trad::operator=\n";
  if (rot != t.rot)
  {
    delete rot;
    kopiera(t);
  }
  return *this;
}

template <typename T>
bool Trad<T>::operator== (const Trad& t) const
{
  //std::cout << "*** Trad::operator==\n";
  return (tomt() && t.tomt()) ||
          (!tomt() && !t.tomt() && varde() == t.varde() &&
           v_barn() == t.v_barn() && h_barn() == t.h_barn());
}

template <typename T>
void Trad<T>::skriv_ut() const
{
  // traversera igenom trädet rekursivt enligt principen "in-order"
  if (!tomt())
  {
    v_barn().skriv_ut();
    std::cout << varde() << ' ';
    h_barn().skriv_ut();
  }
}

template class Trad<short>;
template class Trad<double>;

#endif /* Trad_h */

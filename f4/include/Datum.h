// Labb3, Datum.h – klassdefinition

#ifndef DATUM_H
#define DATUM_H

#include <array>
#include <iostream>

class Datum
{
    friend std::ostream &operator<<( std::ostream &, const Datum & );
  
    int year;
    int month;
    int day;
  
    // Deklaration av statisk privat medlem, "ant_dagar per månad"
    static const std::array< int, 13 > ANT_DAGAR_PER_MAANAD;
    //void step_one_day(); // Öka datum med en dag
  
public:
    Datum() : year(2000), month(1), day(1) {} 
    Datum( int, int, int );
    void set_date( int, int, int ); // set year, month, day
    
    //OBS. funktionen "step_one_day()" bör vara PRIVATE
    void step_one_day(); // Öka datum med en dag
    static bool is_skott_aar( int ); // Är det skottår?
    bool end_of_month( int ) const; // Är dagen den sista i månaden?

    bool operator==(const Datum&);
    bool operator!=(const Datum&);
    bool operator<(const Datum&);
    bool operator>(const Datum&);
    bool operator<=(const Datum&);
    bool operator>=(const Datum&);

    // Pre ++
    Datum& operator++();
    // Post ++
    Datum operator++(int);

    Datum operator+(int);
    Datum& operator+=(int);

    friend Datum operator+(int, const Datum&);
    
  
};

#endif


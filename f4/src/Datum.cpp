// Labb3, Datum.cpp – definitioner av icke-triviala medlemsfunktioner

#include <iostream>
#include <exception>
#include <string>
#include "Datum.h"

// Initialisera statisk medlem
// (första elementet används inte i denna lösning!)
const std::array< int, 13 > Datum::ANT_DAGAR_PER_MAANAD = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

// Konstruktor
Datum::Datum( int year, int month, int day  )
{
  set_date( year, month, day);
}

void Datum::set_date( int yy, int mm, int dd )
{
  // Glöm inte att kontrollera inmatade värden, annars "exception"

    if(yy < 2000 ||yy > 2100)
        throw std::invalid_argument("Årets måste vara mellan >= 2000 och <= 2100");	
    
    year = yy;

    if(mm < 1 || mm > 12)
        throw std::invalid_argument("Månaden måste vara >= 1 och <= 12");
    
    month = mm;

    if(is_skott_aar(yy))
        if((mm == 2) &&
           ((dd < 1) | (dd > 29)))
            throw std::invalid_argument("Dagen stämmer inte med år och månad");
    
    if((dd < 1) | 
       (dd > ANT_DAGAR_PER_MAANAD[mm]))
        throw std::invalid_argument("Dagen stämmer inte med år och månad");

    day = dd;
}

// Denna medlemsfunktion är tänkt att lägga till 1 dag till befintligt datum.
// Om sista dagen i månaden, så byt månad.
//     Om skottår, så ta hänsyn till att februari(månad 2) har 29 dagar.
// Om sista dagen på året, så byt år.
void Datum::step_one_day()
{
  // Dagen är inte sista dagen i månaden!
  if ( !end_of_month( day ) )
    ++day;
  else
    if ( month < 12 )
    {
      ++month;
      day = 1;
    }
    else
    {
      ++year;
      month = 1;
      day = 1;
    }
}

// Returnera true om yy(year) är skottår!
bool Datum::is_skott_aar( int yy )
{
  if ( yy % 400 == 0 ||
      ( yy % 100 != 0 && yy % 4 == 0 ) )
    return true;
  else
    return false;
}

// Är det sista dagen (dd) i månaden?
bool Datum::end_of_month( int dd ) const
{
  if ( month == 2 && is_skott_aar( year ) )
    return dd == 29;
  else
    return dd == ANT_DAGAR_PER_MAANAD[ month ];
}

// operator<<
std::ostream &operator<<( std::ostream &output, const Datum &d )
{
  // OBS. Glöm inte att modifiera vad som skrivs ut!
  //output << d.year << '-' << d.month << '-' << d.day;
    
    std::string month[12] = {"January", "February", "March", "April",
                             "May", "June", "July", "August", "September",
                             "October", "November" , "Devember"};

    output << d.day << " " << month[d.month - 1] << " " << d.year;


  return output;
  
}

bool Datum::operator==(const Datum& other)
{
    if( year  == other.year &&
        month == other.month && 
        day   == other.day )
        return true;

    return false;
}

bool Datum::operator!=(const Datum& other)
{
    if( year != other.year)
        return true;

    if(month != other.month)
        return true;
    
    if( day != other.day)
        return true;

    return false;
}

bool Datum::operator<(const Datum& other)
{
    if(year > other.year)
        return false;
    
    if(month > other.month)
        return false;
    
    if(day >= other.day)
        return false;

    return true;
}

bool Datum::operator>(const Datum& other)
{
    if(year < other.year)
        return false;
    
    if(month < other.month)
        return false;
    
    if(day <= other.month)
        return false;

    return true;
}

bool Datum::operator<=(const Datum& other)
{
    if(year > other.year)
        return false;
    
    if(month > other.month)
        return false;
    
    if(day > other.day)
        return false;
    
    return true;
}

bool Datum::operator>=(const Datum& other)
{
    if(year < other.year)
        return false;
    
    if(month < other.month)
        return false;
    
    if(day < other.day)
        return false;

    return true;
}

// Prefix
Datum& Datum::operator++()
{
    step_one_day();

    return *this;
}

// Postfix
Datum Datum::operator++(int)
{
    Datum temp(*this);
    step_one_day();
    return temp;
}

Datum Datum::operator+(int nDaysToIncrement)
{
    Datum temp(*this);

    for(int i = 0; i < nDaysToIncrement; i++)
        temp.step_one_day();

    return temp;
}

Datum operator+(int days, const Datum& datum)
{
    Datum temp = datum;

    for(int i = 0; i < days; i++)
        temp.step_one_day();
    
    return temp;
}

Datum& Datum::operator+=(int nDaysToIncrement)
{
    for(int i = 0; i < nDaysToIncrement; i++)
        step_one_day();

    return *this;
}

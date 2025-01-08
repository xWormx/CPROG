#include "Uppgift4_Book.h"

namespace books
{
    

Book::Book(std::string t, int i) : title(t), isbn(i) {}

std::string Book::getTitle() const { return title; }

int Book::getISBN() const { return isbn; }

void showBook(Book* b)
{
    std::cout << b->getTitle() << ": " << b->getISBN() << std::endl; 
}

}
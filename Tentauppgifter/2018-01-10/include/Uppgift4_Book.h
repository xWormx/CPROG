#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

namespace books
{
    
class Book
{
    public:
        Book(std::string t, int i);
        std::string getTitle() const;
        int getISBN() const;
    private:
        std::string title;
        int isbn;
};

void showBook(Book* b);


} // namespace books


#endif
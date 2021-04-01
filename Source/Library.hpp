#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <fstream>
#include "Book.hpp"
#include "Vector.hpp"

class Library
{
    private:
        Vector<Book> books;
    public:
        Library();
        void addBook(const Book& book);
        bool removeBook(const std::string& id);
        bool editBook(const std::string& id, const std::string& data, int which);
        Book searchById(const std::string& id) const;
        void searchByAuthor(const std::string& author) const;
        Vector<Book> getBooks() const;
        Book getById(const std::string& id) const;
        bool isIdValid(const std::string& id) const;
    private:
        void loadBooks();
        void updateBooks() const;
        int index(const std::string& id) const;
        std::string string_lower(const std::string& str) const;
};

#endif
#ifndef REQUESTSTREAM_HPP
#define REQUESTSTREAM_HPP

#include <fstream>
#include <utility>
#include "Book.hpp"
#include "Vector.hpp"

class RequestStream
{
    private:
        Vector<std::pair<Book, std::string>> requested_books;
        Vector<std::pair<Book, std::string>> approved_books;
    public:
        RequestStream();
        void addRequestedBook(const std::pair<Book, std::string>& pair);
        void addApprovedBook(const std::pair<Book, std::string>& pair);
        bool removeRequestedBook(const std::string& id);
        bool removeApprovedBook(const std::string& id);
        bool isRequested(const std::string& id) const;
        bool isApprovedIdAndUserValid(const std::pair<std::string, std::string>& pair) const;
        Book getRequestedBookById(const std::string& id) const;
        Book getApprovedBookById(const std::string& id) const;
        int indexForRequestedBook(const std::string& id) const;
        int indexForApprovedBook(const std::string& id) const;
        Vector<std::pair<Book, std::string>> getRequestedBooks() const;
        Vector<std::pair<Book, std::string>> getApprovedBooks() const;
    private:
        void loadRequestedBooks();
        void loadApprovedBooks();
        void updateRequestedBooks() const;
        void updateApprovedBooks() const;
};

#endif
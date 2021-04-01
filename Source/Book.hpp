#ifndef BOOK_HPP
#define BOOK_HPP

#include "Date.hpp"

class Book
{
    private:
        std::string name;
        std::string author;
        std::string id;
        Date publish_date;
    public:
        Book();
        Book(const std::string& name, const std::string& author, 
            const std::string& id, Date publish_date);
        Book(const Book& book);
        void setName(const std::string& name);
        void setAuthor(const std::string& author);
        void setId(const std::string& id);
        void setPublish_Date(const Date& publish_date);
        std::string getName() const;
        std::string getAuthor() const;
        std::string getId() const;
        Date getPublish_Date() const;
        bool operator==(const Book& book) const;
    public:
        friend std::ostream& operator<<(std::ostream& os, const Book& book);
};

#endif
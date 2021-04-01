#include "Book.hpp"

Book::Book()
    :name(""), author(""), 
        id(""), publish_date("") {}

Book::Book(const std::string& name, const std::string& author, 
            const std::string& id, Date publish_date)
    :name(name), author(author),
        id(id), publish_date(publish_date) {}

Book::Book(const Book& book)
{
    name = book.getName();
    author = book.getAuthor();
    id = book.getId();
    publish_date = book.getPublish_Date();
}

void Book::setName(const std::string& name)
{
    this->name = name;
}

void Book::setAuthor(const std::string& author)
{
    this->author = author;
}

void Book::setId(const std::string& id)
{
    this->id = id;
}

void Book::setPublish_Date(const Date& publish_date)
{
    this->publish_date = publish_date;
}

std::string Book::getName() const
{
    return name;
}

std::string Book::getAuthor() const
{
    return author;
}

std::string Book::getId() const
{
    return id;
}

Date Book::getPublish_Date() const
{
    return publish_date;
}

bool Book::operator==(const Book& book) const
{
    return name == book.getName() &&
        author == book.getAuthor() &&
        id == book.getId() &&
        publish_date == book.getPublish_Date();
}

std::ostream& operator<<(std::ostream& os, const Book& book)
{
    os << "Name: " << book.getName() << std::endl
        << "Author: " << book.getAuthor() << std::endl
        << "Id: " << book.getId() << std::endl
        << "Publish date: " << book.getPublish_Date();

    return os;
}
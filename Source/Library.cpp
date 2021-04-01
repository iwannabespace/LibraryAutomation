#include "Library.hpp"

Library::Library()
{
    loadBooks();
}

void Library::addBook(const Book& book)
{
    books.Push(book);
    updateBooks();
}

bool Library::removeBook(const std::string& id)
{
    if (index(id) >= 0)
    {
        books.Remove(books.Get(index(id)));
        updateBooks();
        return true;
    }

    else 
        return false;
}

bool Library::editBook(const std::string& id, const std::string& data, int which)
{
    switch(which)
    {
        case 1:
            if (index(id) >= 0)
            {    
                books.Get(index(id)).setName(data);
                updateBooks();
                return true;
            }
            else
                return false;
            break;
        case 2:
            if (index(id) >= 0)
            {    
                books.Get(index(id)).setAuthor(data);
                updateBooks();
                return true;
            }
            else
                return false;
            break;
        case 3:
            if (index(id) >= 0)
            {    
                books.Get(index(id)).setId(data);
                updateBooks();
                return true;
            }
            else
                return false;
            break;
        case 4:
            if (index(id) >= 0)
            {    
                books.Get(index(id)).setPublish_Date(Date(data));
                updateBooks();
                return true;
            }
            else
                return false;
            break;
        default:
            return false;   
            break;
    }
}

Book Library::searchById(const std::string& id) const
{
    if (index(id) >= 0)
        return books.Get(index(id));
    
    else return Book();
}

void Library::searchByAuthor(const std::string& author) const
{
    for (const Book& book: books)
        if (string_lower(book.getAuthor()) == string_lower(author))
            std::cout << book << std::endl; 
}

Vector<Book> Library::getBooks() const
{
    return books;
}

Book Library::getById(const std::string& id) const
{
    for (const Book& book: books)
        if (book.getId() == id)
            return book;
    
    return Book();
}

bool Library::isIdValid(const std::string& id) const
{
    for (const Book& book: books)
        if (book.getId() == id)
            return true;
    
    return false;
}

void Library::loadBooks()
{
    std::fstream file("Data/Books.txt", std::ios::in);
    std::string infos[4];
    std::string data;

    while (!file.eof())
    {
        std::getline(file, data);
        if (data == "BEGIN")
        {
            std::getline(file, infos[0]);
            std::getline(file, infos[1]);
            std::getline(file, infos[2]);
            std::getline(file, infos[3]);

            for (std::string& info: infos)
                if (isspace(info[info.size() - 1]))
                    info.pop_back();

            books.Push(Book(infos[0], infos[1], infos[2], Date(infos[3])));
        }
    }

    file.close();
}

void Library::updateBooks() const
{
    std::fstream file("Data/Books.txt", std::ios::out);

    for (const Book& book: books)
    {
        file << "BEGIN" << std::endl;
        file << book.getName() << std::endl
            << book.getAuthor() << std::endl
            << book.getId() << std::endl
            << book.getPublish_Date() << std::endl;
        file << "END" << std::endl;
    }

    file.close();
}

int Library::index(const std::string& id) const
{
    for (int i = 0; i < books.Size(); i++)
        if (books.Get(i).getId() == id)
            return i;
    
    return -1;
}

std::string Library::string_lower(const std::string& str) const
{
    std::string temp = str;

    for (char& letter: temp)
        letter = tolower(letter);
    
    return temp;
}
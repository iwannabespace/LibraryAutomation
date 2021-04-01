#include "RequestStream.hpp"

RequestStream::RequestStream()
{
    loadRequestedBooks();
    loadApprovedBooks();
}

void RequestStream::addRequestedBook(const std::pair<Book, std::string>& pair)
{
    requested_books.Push(pair);
    updateRequestedBooks();
}

void RequestStream::addApprovedBook(const std::pair<Book, std::string>& pair)
{
    approved_books.Push(pair);
    updateApprovedBooks();
}

bool RequestStream::removeRequestedBook(const std::string& id)
{
    for (const std::pair<Book, std::string>& pair: requested_books)
        if (pair.first.getId() == id)
        {    
            requested_books.Remove(pair);
            updateRequestedBooks();
            return true;
        }
    
    return false;
}

bool RequestStream::removeApprovedBook(const std::string& id)
{
    for (const std::pair<Book, std::string>& pair: approved_books)
        if (pair.first.getId() == id)
        {    
            approved_books.Remove(pair);
            updateApprovedBooks();
            return true;
        }
    
    return false;
}

bool RequestStream::isRequested(const std::string& id) const
{
    for (const std::pair<Book, std::string>& pair: requested_books)
        if (pair.first.getId() == id)
            return true;
    
    return false;
}

bool RequestStream::isApprovedIdAndUserValid(const std::pair<std::string, std::string>& pair) const
{
    for (const std::pair<Book, std::string>& apprv: approved_books)
        if (apprv.first.getId() == pair.first && apprv.second == pair.second)
            return true;
    
    return false;
}

Book RequestStream::getRequestedBookById(const std::string& id) const
{
    for (const std::pair<Book, std::string>& pair: requested_books)
        if (pair.first.getId() == id)
            return pair.first;
    
    return Book();
}

Book RequestStream::getApprovedBookById(const std::string& id) const
{
    for (const std::pair<Book, std::string>& pair: approved_books)
        if (pair.first.getId() == id)
            return pair.first;
    
    return Book();
}

int RequestStream::indexForRequestedBook(const std::string& id) const
{
    for (int i = 0; i < requested_books.Size(); i++)
        if (requested_books.Get(i).first.getId() == id)
            return i;
    
    return 0;
}

int RequestStream::indexForApprovedBook(const std::string& id) const
{
    for (int i = 0; i < approved_books.Size(); i++)
        if (approved_books.Get(i).first.getId() == id)
            return i;
    
    return 0;
}

Vector<std::pair<Book, std::string>> RequestStream::getRequestedBooks() const
{
    return requested_books;
}

Vector<std::pair<Book, std::string>> RequestStream::getApprovedBooks() const
{
    return approved_books;
}

void RequestStream::loadRequestedBooks()
{
    std::fstream file("Data/Requested Books.txt", std::ios::in);
    std::string infos[4];
    std::string data;

    while (!file.eof())
    {
        std::getline(file, data);
        if (data == "BEGIN")
        {
            std::getline(file, data);
            std::getline(file, infos[0]);
            std::getline(file, infos[1]);
            std::getline(file, infos[2]);
            std::getline(file, infos[3]);

            for (std::string& info: infos)
                if (isspace(info[info.size() - 1]))
                    info.pop_back();

            requested_books.Push(std::make_pair(Book(infos[0], infos[1], infos[2], Date(infos[3])), data));
        }
    }

    file.close();
}

void RequestStream::loadApprovedBooks()
{
    std::fstream file("Data/Approved Books.txt", std::ios::in);
    std::string infos[4];
    std::string data;

    while (!file.eof())
    {
        std::getline(file, data);
        if (data == "BEGIN")
        {
            std::getline(file, data);
            std::getline(file, infos[0]);
            std::getline(file, infos[1]);
            std::getline(file, infos[2]);
            std::getline(file, infos[3]);

            for (std::string& info: infos)
                if (isspace(info[info.size() - 1]))
                    info.pop_back();

            approved_books.Push(std::make_pair(Book(infos[0], infos[1], infos[2], Date(infos[3])), data));
        }
    }

    file.close();
}

void RequestStream::updateRequestedBooks() const
{
    std::fstream file("Data/Requested Books.txt", std::ios::out);

    for (const std::pair<Book, std::string>& pair: requested_books)
    {
        file << "BEGIN" << std::endl;
        file << pair.second << std::endl
            << pair.first.getName() << std::endl
            << pair.first.getAuthor() << std::endl
            << pair.first.getId() << std::endl
            << pair.first.getPublish_Date() << std::endl;
        file << "END" << std::endl;
    }

    file.close();
}

void RequestStream::updateApprovedBooks() const
{
    std::fstream file("Data/Approved Books.txt", std::ios::out);

    for (const std::pair<Book, std::string>& pair: approved_books)
    {
        file << "BEGIN" << std::endl;
        file << pair.second << std::endl
            << pair.first.getName() << std::endl
            << pair.first.getAuthor() << std::endl
            << pair.first.getId() << std::endl
            << pair.first.getPublish_Date() << std::endl;
        file << "END" << std::endl;
    }

    file.close();
}
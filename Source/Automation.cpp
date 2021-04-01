#include "Automation.hpp"

void Automation::Begin()
{
    while (true)
    {
        if (GetCurrentState() == "None")
            FirstScreen();
        
        if (GetCurrentState() == "Admin")
            MainScreenAdmin();
        
        if (GetCurrentState() == "User")
            MainScreenUser();
    }
}

void Automation::FirstScreen()
{   
    int choice;
    for (const std::string& option: FirstScreenOptions())
        std::cout << option << std::endl;
    
    std::cout << " -> ";
    std::cin >> choice;

    switch(choice)
    {
        case 1:
            SignIn();
            break;
        case 2:
            SignUp();
            break;
        case 3:
            Exit();
            break;
        default:
            break;
    }
}

void Automation::MainScreenAdmin()
{
    int choice;
    for (const std::string& option: MainScreenOptionsFor_Admin())
        std::cout << option << std::endl;
    
    std::cout << " -> ";
    std::cin >> choice;

    switch(choice)
    {
        case 1:
            AddBook();
            break;
        case 2:
            RemoveBook();
            break;
        case 3:
            EditBook();
            break;
        case 4:
            Answer();
            break;
        case 5:
            SearchById();
            break;
        case 6:
            SearchByAuthor();
            break;
        case 7:
            ListBooks();
            break;
        case 8:
            ListLentBooks();
            break;
        case 9:
            ListRequests();
            break;
        case 10:
            LogOut();
            break;
        default:
            break;
    }
}

void Automation::MainScreenUser()
{
    int choice;
    for (const std::string& option: MainScreenOptionsFor_User())
        std::cout << option << std::endl;
    
    std::cout << " -> ";
    std::cin >> choice;

    switch(choice)
    {
        case 1:
            RequestBook();
            break;
        case 2:
            ReturnBook();
            break;
        case 3:
            ReturnAllBooks();
            break;
        case 4:
            ListRequestedBooks();
            break;
        case 5:
            ListBorrowedBooks();
            break;
        case 6:
            ListLibrary();
            break;
        case 7:
            LogOut();
        default:
            break;
    }
}

void Automation::SignIn() 
{
    std::fstream file;
    std::string type;
    std::string username, u_temp;
    std::string password, p_temp;
    int pos = 0;

    std::cout << "Type: ";
    std::cin.ignore();
    std::getline(std::cin, type);

    std::cout << "Username: ";
    std::getline(std::cin, username);
    
    std::cout << "Password: ";
    std::getline(std::cin, password);

    if (string_lower(type) == "admin")
    {
        file.open("Data/Admin.txt", std::ios::in);
        std::getline(file, u_temp);
        std::getline(file, p_temp);

        if (username == u_temp)
        {
            if (password == p_temp)  
                AlterStateAs("Admin");
            else
                std::cout << "Invalid password!" << std::endl;
        }
        else
            std::cout << "Admin username is invalid!" << std::endl;

        file.close();
    }
    
    else if (string_lower(type) == "user")
    {
        file.open("Data/Accounts.txt", std::ios::in);
        while (!file.eof())
        {
            std::getline(file, u_temp);
            pos++;
            if (username == u_temp && pos % 2 != 0)
            {
                std::getline(file, p_temp);
                if (password == p_temp)
                {    
                    AlterStateAs("User");
                    SetCurrentUser(username);
                    break;
                }
                else
                {    
                    std::cout << "Invalid password!" << std::endl;
                    break;
                }
            }
            else if (file.eof() && username != u_temp)
                std::cout << "No username found!" << std::endl;
        }

        file.close();
    }

    else
        std::cout << "Invalid type!" << std::endl
                << "Try: Admin or User" << std::endl;
}

void Automation::SignUp()
{
    std::fstream file;
    std::string username;
    std::string password;

    std::cout << "Choose a username: ";
    std::cin.ignore();
    std::getline(std::cin, username);
    
    std::cout << "Choose a password: ";
    std::getline(std::cin, password);

    if (is_username_unique(username))
    {
        if (is_password_appropriate(password) == 1)
        {
            file.open("Data/Accounts.txt", std::ios::app);

            file << username << std::endl;
            file << password << std::endl;
            file.close();

            std::cout << "Sign up successfull" << std::endl;
        }

        else if (is_password_appropriate(password) == 0)
        std::cout << "Password must contain at least one number!" << std::endl;

        else if (is_password_appropriate(password) == -1)
            std::cout << "Password must contain at least one upper case letter!" << std::endl; 

        else if (is_password_appropriate(password) == -2)
            std::cout << "Password length must be between 8 - 20 characters!" << std::endl;
    }

    else
        std::cout << "Username is already in use!" << std::endl;
}

void Automation::Exit()
{
    exit(0);
}

void Automation::AddBook()
{
    Library library;
    std::string name, author;
    std::string id, publish_date;

    std::cout << "Name of the book: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Author of the book: ";
    std::getline(std::cin, author);
    
    std::cout << "Id of the book: ";
    std::getline(std::cin, id);

    std::cout << "Publish date of the book: ";
    std::getline(std::cin, publish_date);

    library.addBook(Book(name, author, id, Date(publish_date)));

    std::cout << "Book successfully added!" << std::endl; 
}

void Automation::RemoveBook()
{
    Library library;
    std::string data;

    std::cout << "Id of the book: ";
    std::cin.ignore();
    std::getline(std::cin, data);

    if (library.removeBook(data))
        std::cout << "Book successfully removed!" << std::endl;
    
    else
        std::cout << "Id doesn't match with any book!" << std::endl;
}

void Automation::EditBook()
{
    Library library;
    std::string id, which, data;

    std::cout << "Id of book: ";
    std::cin.ignore();
    std::getline(std::cin, id);

    std::cout << "Which section of book: ";
    std::getline(std::cin, which);

    if (string_lower(which) == "name")
    {
        std::cout << "New name: ";
        std::getline(std::cin, data);

        if (library.editBook(id, data, 1))
            std::cout << "Book edited successfully!" << std::endl;
        
        else
            std::cout << "Id doesn't match with any book!" << std::endl;
    }

    else if (string_lower(which) == "author")
    {
        std::cout << "New author: ";
        std::getline(std::cin, data);
        
        if (library.editBook(id, data, 2))
            std::cout << "Book edited successfully!" << std::endl;
        
        else
            std::cout << "Id doesn't match with any book!" << std::endl;
    }

    else if (string_lower(which) == "id")
    {
        std::cout << "New id: ";
        std::getline(std::cin, data);
        
        if (library.editBook(id, data, 3))
            std::cout << "Book edited successfully!" << std::endl;
        
        else
            std::cout << "Id doesn't match with any book!" << std::endl;
    }

    else if (string_lower(which) == "date")
    {
        std::cout << "New publish date: ";
        std::getline(std::cin, data);
        
        if (library.editBook(id, data, 4))
            std::cout << "Book edited successfully!" << std::endl;
        
        else
            std::cout << "Id doesn't match with any book!" << std::endl;
    }

    else
        std::cout << "\"" << which << "\" named section doesn't exist!" << std::endl;
}

void Automation::Answer()
{
    Library library;
    RequestStream stream;
    std::string id, answer;
    
    std::cout << "Id of book to be answered: ";
    std::cin.ignore();
    std::getline(std::cin, id);

    if (stream.getRequestedBookById(id).getName().size() > 0)
    {
        std::cout << "Your reply: ";
        std::getline(std::cin, answer);
        
        if (string_lower(answer) == "approved")
        {    
            stream.addApprovedBook(std::make_pair(stream.getRequestedBookById(id), get_requester_by_id(id)));
            stream.removeRequestedBook(id);
            library.removeBook(id);
            delete_request_from_requests_by_id(id);
        }
        
        else if (string_lower(answer) == "disapproved")
        {
            stream.removeRequestedBook(id);
            delete_request_from_requests_by_id(id);
        }

        else
            std::cout << "Invalid reply!" << std::endl;
    }

    else    
        std::cout << "Book with id of " << id << " is not requested!" << std::endl; 

}

void Automation::SearchById()
{
    Library library;
    std::string data;

    std::cout << "Id for searching: ";
    std::cin.ignore();
    std::getline(std::cin, data);

    if (library.searchById(data).getId().size() > 0)
        std::cout << library.searchById(data) << std::endl;
    
    else
        std::cout << "Id doesn't match with any book!" << std::endl;

}

void Automation::SearchByAuthor()
{
    Library library;
    std::string data;

    std::cout << "Author for searching: ";
    std::cin.ignore();
    std::getline(std::cin, data);

    library.searchByAuthor(data);
}

void Automation::ListBooks()
{
    Library library;

    if (library.getBooks().Size() > 0)
        for (int i = 0; i < library.getBooks().Size(); i++)
            std::cout << "Book " << i + 1 << std::endl
                << library.getBooks()[i] << std::endl;
    
    else
        std::cout << "No book found!" << std::endl;
}

void Automation::ListRequests()
{
    std::fstream file("Data/Requests.txt", std::ios::in);
    std::string data;
    int index;

    while (!file.eof())
    {
        std::getline(file, data);

        if (data.size() > 0)
            std::cout << "Request: " << data << std::endl;
    }

    file.close();
}

void Automation::ListLentBooks()
{
    RequestStream stream;

    if (stream.getApprovedBooks().Size() > 0)
        for (int i = 0; i < stream.getApprovedBooks().Size(); i++)
            std::cout << "Lent book " << i + 1 << std::endl 
                << stream.getApprovedBooks().Get(i).first << std::endl;
    
    else
        std::cout << "No book has been lent so far!" << std::endl;
}

void Automation::RequestBook()
{
    Library library;
    RequestStream stream;
    std::fstream file("Data/Requests.txt", std::ios::app);
    std::string data;

    std::cout << "Id of book to be requested: ";
    std::cin.ignore();
    std::getline(std::cin, data);

    if (library.isIdValid(data))
    {    
        if (!stream.isRequested(data))
        {    
            file << GetCurrentUser() << " " << data << std::endl;
            stream.addRequestedBook(std::make_pair(library.getById(data), GetCurrentUser()));
            std::cout << "Book requested successfully!" << std::endl;
        }
        
        else 
            std::cout << "This book is already requested!" << std::endl;
    }
    
    else 
        std::cout << "Id doesn't match with any books!" << std::endl;

    file.close();
}

void Automation::ReturnBook()
{
    Library library;
    RequestStream stream;
    std::string data, id;

    std::cout << "Id of book to be returned: ";
    std::cin.ignore();
    std::getline(std::cin, id);

    if (stream.isApprovedIdAndUserValid(std::make_pair(id, GetCurrentUser())))
    {
        library.addBook(stream.getApprovedBookById(id));
        if (stream.removeApprovedBook(id))
            std::cout << "Book returned successfully!" << std::endl;
        
        else
            std::cout << "Book couldn't be returned because of an unknown reason!" << std::endl;
    }

    else
        std::cout << "You don't owe the book!" << std::endl;
}

void Automation::ReturnAllBooks()
{
    Library library;
    RequestStream stream;
    for (const std::pair<Book, std::string>& pair: stream.getApprovedBooks())
        if (pair.second == GetCurrentUser())
        {
            library.addBook(stream.getApprovedBookById(pair.first.getId()));
            stream.removeApprovedBook(pair.first.getId());
        }
    
    std::cout << "All borrowed books are returned!" << std::endl;
}

void Automation::ListRequestedBooks()
{
    Library library;
    RequestStream stream;

    if (stream.getRequestedBooks().Size() > 0)
    {    
        for (int i = 0; i < stream.getRequestedBooks().Size(); i++)
        {
            if (stream.getRequestedBooks().Get(i).second == GetCurrentUser())
            {    
                std::cout << "Requested Book " << i + 1 << std::endl;
                std::cout << stream.getRequestedBooks().Get(i).first << std::endl;
            }
        }
    }
    
    else
        std::cout << "Request list is empty!" << std::endl;
}

void Automation::ListBorrowedBooks()
{
    Library library;
    RequestStream stream;

    if (stream.getApprovedBooks().Size() > 0)
    {    
        for (int i = 0; i < stream.getApprovedBooks().Size(); i++)
        {
            if (stream.getApprovedBooks().Get(i).second == GetCurrentUser())
            {    
                std::cout << "Borrowed Book " << i + 1 << std::endl;
                std::cout << stream.getApprovedBooks().Get(i).first << std::endl;
            }
        }
    }
    
    else
        std::cout << "No borrowed book found!" << std::endl;
}

void Automation::ListLibrary()
{
    Library library;

    if (library.getBooks().Size() > 0)
        for (int i = 0; i < library.getBooks().Size(); i++)
            std::cout << "Library book " << i + 1 << std::endl
                << library.getBooks().Get(i) << std::endl;
    
    else
        std::cout << "Library has no books yet!" << std::endl;
}

void Automation::LogOut()
{
    AlterStateAs("None");
    SetCurrentUser("");
}

void Automation::AlterStateAs(const std::string& state)
{
    std::fstream file("Data/State.txt", std::ios::out);

    file << state;
    file.close();
}

void Automation::SetCurrentUser(const std::string& username)
{     
    std::fstream file("Data/Current Account.txt", std::ios::out);

    file << username;
    file.close();
}

std::string Automation::GetCurrentState()
{
    std::fstream file("Data/State.txt", std::ios::in);
    std::string current_state;

    file >> current_state;
    file.close();

    return current_state;
}

std::string Automation::GetCurrentUser()
{
    std::fstream file("Data/Current Account.txt", std::ios::in);
    std::string current_user;

    file >> current_user;
    file.close();

    return current_user;
}

Vector<std::string> Automation::FirstScreenOptions()
{
    Vector<std::string> first_screen = { 
        "(1) -> Sign in",
        "(2) -> Sign up",
        "(3) -> Exit"
    };

    return first_screen;
}

Vector<std::string> Automation::MainScreenOptionsFor_Admin()
{
    Vector<std::string> main_screen_for_admin = {
        "(1) -> Add Book",
        "(2) -> Remove Book",
        "(3) -> Edit Book",
        "(4) -> Answer a Request",
        "(5) -> Search Book by ID",
        "(6) -> Search Book by Author",
        "(7) -> List Books",
        "(8) -> List Lent Books",
        "(9) -> List Requests",
        "(10) -> Log out"
    };

    return main_screen_for_admin;
}

Vector<std::string> Automation::MainScreenOptionsFor_User()
{
    Vector<std::string> main_screen_for_user = {
        "(1) -> Request Book",
        "(2) -> Return Book",
        "(3) -> Return All Books",
        "(4) -> List Requested Books",
        "(5) -> List Borrowed Books",
        "(6) -> List All Books In Library",
        "(7) -> Logout",
    };

    return main_screen_for_user;
}

void Automation::delete_request_from_requests_by_id(const std::string& id)
{
    RequestStream stream;
    std::fstream file("Data/Requests.txt", std::ios::out);

    for (const std::pair<Book, std::string>& pair: stream.getRequestedBooks())
        if (pair.first.getId() != id)
            file << pair.second << " " << pair.first.getId() << std::endl; 
}

std::string Automation::get_requester_by_id(const std::string& id)
{
    RequestStream stream;

    if (stream.getRequestedBookById(id).getName().size() > 0)
        return stream.getRequestedBooks().Get(stream.indexForRequestedBook(id)).second;
    
    else
        return std::string();
}

bool Automation::is_username_unique(const std::string& username)
{
    std::fstream file("Data/Accounts.txt", std::ios::in);
    std::string data;
    int pos = 0;

    while (!file.eof())
    {
        std::getline(file, data);
        pos++;

        if (data == username && pos % 2 != 0)
        {   
            file.close(); 
            return false;
        }
    }

    file.close();

    return true;
}

int Automation::is_password_appropriate(const std::string& password)
{
    if (password.size() >= 8 && password.size() <= 20)
    {
        if (std::any_of(password.begin(), password.end(), isupper))
        {
            if (std::any_of(password.begin(), password.end(), isdigit))
                return 1;
            else
                return 0;
        }
        else 
            return -1;   
    }
    else 
        return -2;
}

std::string Automation::string_lower(const std::string& str)
{
    std::string temp = str;

    for (char& letter: temp)
        letter = tolower(letter);
    
    return temp;
}
#ifndef AUTOMATION_HPP
#define AUTOMATION_HPP

#include "Library.hpp"
#include "RequestStream.hpp"

class Automation
{
    public:
        static void Begin();
    private:
        static void FirstScreen();
        static void MainScreenAdmin();
        static void MainScreenUser();
        static void SignIn();
        static void SignUp();
        static void Exit();
        static void AddBook();
        static void RemoveBook();
        static void EditBook();
        static void Answer();
        static void SearchById();
        static void SearchByAuthor();
        static void ListBooks();
        static void ListRequests();
        static void ListLentBooks();
        static void RequestBook();
        static void ReturnBook();
        static void ReturnAllBooks();
        static void ListRequestedBooks();
        static void ListBorrowedBooks();
        static void ListLibrary();
        static void LogOut();
        static void AlterStateAs(const std::string& state);
        static void SetCurrentUser(const std::string& username);
        static std::string GetCurrentState();
        static std::string GetCurrentUser();
        static Vector<std::string> FirstScreenOptions();
        static Vector<std::string> MainScreenOptionsFor_Admin();
        static Vector<std::string> MainScreenOptionsFor_User();
    private:
        static void delete_request_from_requests_by_id(const std::string& id);
        static std::string get_requester_by_id(const std::string& id);
        static bool is_username_unique(const std::string& username);
        static int is_password_appropriate(const std::string& password);
        static std::string string_lower(const std::string& str);
};

#endif 
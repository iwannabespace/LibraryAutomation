#ifndef DATE_HPP
#define DATE_HPP

#include <iostream>
#include <algorithm>
#include <ctime>

class Date
{
    private:
        std::string date;
    public:
        Date();
        Date(const std::string& date);
        Date(const Date& date);
        void setDate(const std::string& date);
        std::string getDay() const;
        std::string getMonth() const;
        std::string getYear() const;
        std::string asString() const;
        bool operator==(const Date& date) const;
        static std::string Now();
    public:
        friend std::ostream& operator<<(std::ostream& os, const Date& date);
};

#endif
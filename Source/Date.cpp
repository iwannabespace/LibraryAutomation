#include "Date.hpp"

Date::Date()
    :date("") {}

Date::Date(const std::string& date)
    :date(date) {}

Date::Date(const Date& date)
{
    this->date = date.getDay() + "." + date.getMonth() + "." + date.getYear();
}

void Date::setDate(const std::string& date)
{
    this->date = date;
}

std::string Date::getDay() const
{
    std::string day;
    day += date[0];
    day += date[1];

    return day;
}

std::string Date::getMonth() const
{
    std::string month;
    month += date[3];
    month += date[4];

    return month;
}

std::string Date::getYear() const
{
    std::string year;
    year += date[6];
    year += date[7];
    year += date[8];
    year += date[9];

    return year;
}

std::string Date::asString() const
{
    return date;
}

bool Date::operator==(const Date& date) const
{
    return this->date == date.asString();
}

std::string Date::Now()
{
    std::time_t now_time = std::time(0);
    std::tm* now = std::localtime(&now_time);
    std::string actual_now;

    if (std::to_string(now->tm_mday).size() < 2)
        actual_now += "0" + std::to_string(now->tm_mday) + ".";
    else actual_now += std::to_string(now->tm_mday) + ".";

    if (std::to_string(now->tm_mon + 1).size() < 2)
        actual_now += "0" + std::to_string(now->tm_mon + 1) + ".";
    else actual_now += std::to_string(now->tm_mon + 1) + ".";

    actual_now += std::to_string(now->tm_year + 1900);

    return actual_now;
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << date.date;

    return os;
}
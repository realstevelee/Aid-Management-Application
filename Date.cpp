// Workshop <Milestone 05>
// Name: <Sooyong Lee>
// Student #: <146074174>
// Course: OOP244 Winter 2019
// File: <Date.cpp>
#include <iostream>
#include <cstring>
#include "Date.h"

namespace ama {
	int Date::mdays(int year, int mon) const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	Date::Date() {
		year = 0;
		month = 0;
		day = 0;
		statusVar = no_error;
	}

	Date::Date(int _year, int _month, int _day) {
		if (_year >= min_year && _year <= max_year) {
			if (_month >= 1 && _month <= 12) {
				if (_day >= 1 && _day <= mdays(_year, _month)) {
					year = _year;
					month = _month;
					day = _day;
					statusVar = no_error;
				}
				else {
					*this = Date();
					statusVar = error_day;
				}
			}
			else {
				*this = Date();
				statusVar = error_mon;
			}
		}
		else {
			*this = Date();
			statusVar = error_year;
		}
	}

	void Date::status(int newStatus) {
		statusVar = newStatus;
	}

	int Date::status() {
		return statusVar;
	}

	void Date::clearError() {
		statusVar = no_error;
	}

	bool Date::isGood() {
		bool valid = false;
		if (statusVar == no_error && year != 0 && month !=0 && day != 0)
			valid = true;
		else
			valid = false;

		return valid;
	}

	Date& Date::operator+=(int days) {
		if (statusVar != 0 || (year == 0 && month == 0 && day == 0)) {
			statusVar = error_invalid_operation;
		}
		else {
			day = day + days;
			if (day > mdays(year, month) || day < 1) {
				day = day - days;
				statusVar = error_invalid_operation;
			}
		}

		return *this;
	}

	Date& Date::operator++() {
		if (statusVar != 0 || (year == 0 && month == 0 && day == 0)) {
			statusVar = error_invalid_operation;
		}
		else {
			day = day + 1;
			if (day > mdays(year, month) || day < 1) {
				day = day - 1;
				statusVar = error_invalid_operation;
			}
		}
		return *this;
	}

	Date Date::operator++(int days) {
		Date* tmpDate;
		tmpDate = new Date();
		*tmpDate = *this;
		days = day + 1;

		if (!isGood()) { 
			status(error_invalid_operation);
		}

		else if (days > mdays(year, month)) {
			status(error_invalid_operation);
		}

		else {
			day = day + 1;
		}
		return *tmpDate;
	}

	Date Date::operator+(int days) {
		Date* tmpDate;
		tmpDate = new Date();
		*tmpDate = *this;

		int adding = day + days;
		if (!isGood()) {
			status(error_invalid_operation);
		}
		else if (adding > mdays(year, month)) {
			status(error_invalid_operation);
		}
		else { day = adding; }

		return *tmpDate;
	}

	bool Date::operator==(const Date& rhs) {
		return day == rhs.day;
	}

	bool Date::operator!=(const Date& rhs) {
		return day != rhs.day;
	}

	bool Date::operator<(const Date& rhs) {
		return day < rhs.day;
	}

	bool Date::operator>(const Date& rhs) {
		return day > rhs.day;
	}

	bool Date::operator<=(const Date& rhs) {
		return day <= rhs.day;
	}

	bool Date::operator>=(const Date& rhs) {
		return day >= rhs.day;
	}

	std::istream& Date::read(std::istream& is) {
		char token;
		clearError();
		is.clear();
		is >> year >> token >> month >> token >> day;

		if (is.fail()) {
			*this = Date();
			status(error_input);
		}
		else if (year > max_year || year < min_year) {
			*this = Date();
			status(error_year);
		}
		else if (month > 12 || month < 1) {
			*this = Date();
			status(error_mon);
		}
		else if (day > mdays(year, month) || day < 1) {
			*this = Date();
			status(error_day);
		}


		return is;
	}

	std::ostream& Date::write(std::ostream& os) const{
		char token = '/';
		os.fill('0');
		os.width(4);
		os << year << token;
		if (month < 10) {
			os << 0;
		}
		os << month << token;

		if (day < 10) {
			os << 0;
		}
		os << day;

		os.fill(' ');
		return os;
	}

	std::istream& operator>>(std::istream& is, Date& d) {
		d.read(is);
		return is;
	}

	std::ostream& operator<<(std::ostream& os, const Date& d) {
		d.write(os);
		return os;
	}

}
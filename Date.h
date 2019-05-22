// Workshop <Milestone 05>
// Name: <Sooyong Lee>
// Student #: <146074174>
// Course: OOP244 Winter 2019
// File: <Date.h>
#include <iostream>

#ifndef AMA_DATE_H
#define AMA_DATE_H

namespace ama {
	const int min_year = 2019;
	const int max_year = 2028;
	const int no_error = 0;
	const int error_year = 1;
	const int error_mon = 2;
	const int error_day = 3;
	const int error_invalid_operation = 4;
	const int error_input = 5;

	class Date {
		int year;
		int month;
		int day;
		int statusVar;
		void status(int);
		int mdays(int, int) const;
	public:
		Date();
		Date(int _year, int _month, int _day);
		int status();
		void clearError();
		bool isGood();
		Date& operator+=(int);
		Date& operator++();
		Date operator++(int);
		Date operator+(int);
		bool operator==(const Date& rhs);
		bool operator!=(const Date& rhs);
		bool operator<(const Date& rhs);
		bool operator>(const Date& rhs);
		bool operator<=(const Date& rhs);
		bool operator>=(const Date& rhs);
		std::istream& read(std::istream& is);
		std::ostream& write(std::ostream& os) const;
	};

	std::istream& operator>>(std::istream& is, Date& d);
	std::ostream& operator<<(std::ostream& os, const Date& d);
}

#endif
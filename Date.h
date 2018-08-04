/* 
Final Project - Milestone 5
Date.h
Name: Crystal Ding
Section : AB
Student ID : 100414176
Date : 04 / 10 / 2018
Comment: Declare namespace AMA and define the Date class
*/

#ifndef AMA_DATE_H
#define AMA_DATE_H

#include <iostream>

#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4

namespace AMA {

	const int min_year = 2000;
	const int max_year = 2030;

	class Date {
		int year;
		int month;
		int day;
		int comparator;
		int errState;
		int mdays(int, int) const;
		void errCode(int);

	public:
		Date();
		Date(int, int, int);
		~Date();
		bool notEmpty(const Date&) const;
		bool operator==(const Date&) const;
		bool operator!=(const Date&) const;
		bool operator<(const Date&) const;
		bool operator>(const Date&) const;
		bool operator<=(const Date&) const;
		bool operator>=(const Date&) const;
		int errCode() const;
		bool bad() const;
		std::istream& read(std::istream&);
		std::ostream& write(std::ostream&) const;
	};

	std::ostream& operator << (std::ostream&, const Date&);
	std::istream& operator >> (std::istream&, Date&);
}

#endif
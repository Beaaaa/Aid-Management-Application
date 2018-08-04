/*
Final Project - Milestone 5
ErrorState.h
Name: Crystal Ding
Section : AB
Student ID : 100414176
Date : 04 / 10 / 2018
Comment: Declare namespace AMA and define the ErrorState class
*/

#ifndef AMA_ERRORSTATE_H
#define AMA_ERRORSTATE_H

#include <iostream>

namespace AMA {

	class ErrorState {

		char* errMessage;

	public:
		explicit ErrorState(const char* = nullptr);
		ErrorState(const ErrorState&) = delete;
		ErrorState& operator=(const ErrorState&) = delete;
		virtual ~ErrorState();
		void clear();
		bool isClear() const;
		void message(const char*);
		const char* message() const;
	};

	std::ostream& operator<<(std::ostream&, const ErrorState&);
}

#endif
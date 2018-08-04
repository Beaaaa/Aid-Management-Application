/*
Final Project - Milestone 5
ErrorState.cpp
Name: Crystal Ding
Section : AB
Student ID : 100414176
Date : 04 / 10 / 2018
Comment: Define all the functions which have been declared in ErrorState.h
*/

#include <cstring> 
#include "ErrorState.h"

namespace AMA {

	//one default argument constructor checks if the receiving data is valid, then stores it or sets the 
	//current object to a safe empty state accordingly
	ErrorState::ErrorState(const char* errMsg) {
		clear();
		if (errMsg != nullptr && errMsg[0] != '\0') {
			message(errMsg);
		}
	}

	//virtual destructor
	ErrorState::~ErrorState() {
		delete[] errMessage;
	}

	//clear clears any message stored by the current object and initializes the object to a safe empty state
	void ErrorState::clear() {
		errMessage = nullptr;
	}

	//isClear returns true if the current object is in a safe empty state
	bool ErrorState::isClear() const {
		return errMessage == nullptr || errMessage[0] == '\0';
	}

	//message makes a deep copy of the receiving string
	void ErrorState::message(const char* str) {
		delete[] errMessage;
		errMessage = new char[strlen(str) + 1];
		strncpy(errMessage, str, strlen(str));
		errMessage[strlen(str)] = '\0';
	}

	//message() returns the address of the message stored in the current object
	const char* ErrorState::message() const {
		return errMessage;
	}

	//operator<< outputs the ErrorState message if it exits, this operator does nothing otherwise
	std::ostream& operator<<(std::ostream& os, const ErrorState& errMsg) {
		if (!errMsg.isClear()) {
			os << errMsg.message();
		}
		return os;
	}
}
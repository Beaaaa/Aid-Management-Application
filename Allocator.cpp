/*
Final Project - Milestone 5
Allocator.cpp
Name: Crystal Ding
Section : AB
Student ID : 100414176
Date : 04 / 10 / 2018
Comment: Define CreateProduct and CreatePerishable which have been declared in iProduct.h
*/

#include "Product.h"
#include "Perishable.h"

namespace AMA {

	// creates an empty product
	//
	iProduct* CreateProduct() {
		return new Product();
	}

	// creates an empty perishable product
	//
	iProduct* CreatePerishable() {
		return new Perishable();
	}
}
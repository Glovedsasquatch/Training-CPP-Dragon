#pragma once
#ifndef LVALUE_RVALUE_SEMANTICS_H__
#define LVALUE_RVALUE_SEMANTICS_H__

#include <iostream>
#include <string>

namespace semanticslvaluervalue
{

//A function with an lvalue argument and returns an rvalue: To check RULE 1
int getValue(int value)
{
	return value;
}

//function that returns an lvalue (reference to a memory): To check RULE 1 and 2
int& getRefValue()
{
	static int value = 10;
	return value;
}

//A function with a non-const lvalue reference as an argument: To check RULE 3
void printValue(int& value)
{
	std::cout << "Value = " << value << std::endl;
}

//A function with a const lvalue reference as an argument: To check RULE 4
void printValueWithConstRef(const int& value)
{
	std::cout << "Value = " << value << std::endl;	
}

//A function with a rvalue reference as an argument: To check RULE 5
void printValueWithRvalueRef(int&& value)
{
	std::cout << "Value = " << value << std::endl;	
}

//A function with an lvalue argument: To check RULE 1
void printName(std::string name)
{
	std::cout << name << std::endl;
}

//A function with a non-const lvalue reference argument: To check RULE 3
void printNameWithRef(std::string& name)
{
	std::cout << name << std::endl;
}

//A function with a const lvalue reference argument: To check RULE 4
void printNameWithConstRef(const std::string& name)
{
	std::cout << name << std::endl;
}

//A function with a rvalue reference argument (only accepts temporary objects): To check RULE 5
void printNameWithRvalueRef(std::string&& name)
{
	std::cout << name << std::endl;
}



void runLvalueRvalueSemantics()
{
	//RULE 1: an lvalue can take lvalue or rvalue as input
	int value_1 = 10;	/* Here, "value_1" is the lvalue(something that has a memory location attached to it; in some sense permanent)
						   10 is rvalue (a literal that is temporary, in that sense, does not have a memory attached to it) */
						//OK! RULE 1
	int value_2 = value_1; //OK! RULE 1
	getValue(value_1); //OK! RULE 1: a function with an lvalue argument can be called by passing an lvalue
	getValue(10); //OK! RULE 1: a function with an lvalue argument can be called by passing an rvalue

	/* RULE 2: 
	 * - rvalue is not modifiable(it is temporary) and therefore, does NOT take an lvalue
	 */ 
	//20 = value_1;		NOT OK! RULE 2
	//getValue(value_1) = value_2; NOT OK! RULE 2, the function returns an rvalue which cannot store an lvalue
	//getValue(value_2) = 5; NOT OK! RULE 2 because the functions returns a temporary rvalue which cannot store an rvalue

	getRefValue() = value_2; //OK! RULE 1: because storing an lvalue to another lvalue (reference to a memory)
	getRefValue() = 6; //OK! RULE 1: because a lvalue (reference to a memory location) into which an rvalue is stored

	/* RULE 3: 
	 * - A non-const lvalue reference takes lvalue and NOT rvalue 
	 */
	printValue(value_1); //OK! RULE 3
	//printValue(10); NOT OK! RULE 3

	/* (SPECIAL)RULE 4: 
	 * - A const lvalue reference can take both lvalue and rvalue
	 */ 
	//int& value_4 = 10; NOT_OK; RULE 3
	int& value_4 = value_2; //OK! RULE 3
	const int& const_value_3 = 10; //OK! RULE 4
	printValueWithConstRef(value_2); //OK! RULE 4
	printValueWithConstRef(10); //OK! RULE 4

	/* RULE 5: 
	 * An rvalue reference (written with double ampersand as: <datatype>&&) only accepts rvalue and NOT lvalue
	 */
	//printValueWithRvalueRef(value_1); NOT OK! RULE 5
	printValueWithRvalueRef(10); //OK! RULE 5

	//Other examples with std::string
	std::string first_name = "Prabha ";	//lvalue: first_name, last_name, full_name; rvalue = "Prabha ", "Shankar", first_name + last_name
	std::string last_name = "Shankar";	//OK! RULE 1: lvalue taking rvalue as an input
	std::string full_name = first_name + last_name; //OK! RULE 1: lvalue taking rvalue as an input

	printName(full_name); //OK! RULE 1
	printName(first_name + last_name); //OK! RULE 1

	printNameWithRef(full_name);	//OK: RULE 3
	//printNameWithRef(first_name + last_name);	NOT OK! RULE 3

	printNameWithConstRef(full_name);	//OK! RULE 4
	printNameWithConstRef(first_name + last_name); //OK! RULE 4

	
	//printNameWithRvalueRef(full_name);	NOT OK! The function only takes temporary values or rvalues
	printNameWithRvalueRef(first_name + last_name);
}
} //!namespace semanticslvaluervalue


#endif //LVALUE_RVALUE_SEMANTICS_H__

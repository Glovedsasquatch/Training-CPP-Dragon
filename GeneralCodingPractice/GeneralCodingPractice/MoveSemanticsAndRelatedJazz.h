#pragma once

#ifndef MOVE_SEMANTICS_AND_RELATED_JAZZ_H__
#define MOVE_SEMANTICS_AND_RELATED_JAZZ_H__

#include <iostream>
#include <string>

namespace movesemantics
{
class String
{
public:
	String() = default;
	String(const char* data)
	{
		std::cout << __FUNCTION__ << "(" << __LINE__ << "):: Created!" << std::endl;
		m_size = std::strlen(data) + 1;	//determines the length of the string without the terminating null character "\0"
		m_data = new char[m_size];
		memcpy(m_data, data, m_size);
	}

	//Copy constructor
	String(const String& other)
	{
		std::cout << __FUNCTION__ << "(" << __LINE__ << "):: Copied!" << std::endl;
		m_size = std::strlen(other.m_data) + 1;	//determines the length of the string without the terminating null character "\0"
		m_data = new char[m_size];
		memcpy(m_data, other.m_data, m_size);
	}

	//Move constructor
	String(String&& other)
	{
		std::cout << __FUNCTION__ << "(" << __LINE__ << "):: Moved!" << std::endl;
		//This is a shallow copy
		m_size = other.m_size;
		m_data = other.m_data;

		/*IMPORTANT: Since String instances, namely "other" and "this", point to the same memory,
		* when "other" goes out of scope (and is destroyed), the data is lost for "this as well".
		* Hence, a move constructor must have the following lines to create a "hollow object"
		*/
		other.m_size = 0;
		other.m_data = nullptr; 
	}

	void printData() const
	{
		std::cout << __FUNCTION__ << "(" << __LINE__ << "):: The data stored is: " << m_data << std::endl;
	}

	~String()
	{
		std::cout << __FUNCTION__ << "(" << __LINE__ << "):: Destroyed!" << std::endl;		
		delete[] m_data;
	}

private:
	uint32_t m_size;
	char* m_data;
};

class Entity
{
public:
	Entity(const String& name)
		: m_name(name)
	{
	}

	Entity(String&& name)
		:m_name(std::move(name))	/* Remarks: 1. alternatively, one could write: m_name((String&&)name); std::move does the same thing
										 *			2. std::move usage, as shown in the code, (or typecasting to String&&) forces the code to
										 *			   use the move constructor and NOT the copy constructor
										 */
	{
	}

	void printName() const
	{
		m_name.printData();
	}

private:
	String m_name;
};

void runMoveIntroduction();

} //!namespace movesemantics

#endif //MOVE_SEMANTICS_AND_RELATED_JAZZ_H__

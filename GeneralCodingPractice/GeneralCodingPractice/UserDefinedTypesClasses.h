#pragma once

#ifndef USER_DEFINED_TYPES_CLASSES_H__
#define USER_DEFINED_TYPES_CLASSES_H__

#include <iostream>
#include <string>

/* PART 1:
 * This part of the code is to understand how VIRTUAL FUNCTIONS actually work
 */
struct Base
{
	virtual void f()
	{
		std::cout << "Called from BASE class" << std::endl;
	}
};

struct Derived : Base
{
	void f()
	{
		std::cout << "Called from DERIVED class" << std::endl;
	}
};

void howVirtualFunctionsWork();
//===============================================================================================

/* PART 2:
 * To demonstrate the usage of dynamic casting
 * Use case: It is an operator that casts one data type into another data type
 * a) Safely downcasting: casts a base class pointer (or reference) to a derived class (or reference) 
 * b) Upcasting: can also cast a derived class pointer (or reference) to a base class pointer (or reference)
 * 
 * => SPEED: static_cast > dynamic_cast; BECAUSE dynamic_cast does a runtime consistency check
 * 
 * IMPORTANT CONDITION FOR dynamic_cast to work:
 * at least one function inside the base class must be virtual
 */ 
namespace usage_dynamic_casting
{
class Shape
{
public:
	Shape(std::string shape_name) : m_shape_name(shape_name)
	{
	}

	virtual void getInfo() const
	{
		std::cout << "Shape is: " << m_shape_name << std::endl;
	}

private:
	std::string m_shape_name;
};

class Square : public Shape
{
public:
	Square(const std::string& shape_name, int side_length)
		: Shape(shape_name)
		, m_side_length(side_length)
	{
	}

	void getInfo() const
	{
		std::cout << "Area of the square with length " << m_side_length << " is: " << m_side_length * m_side_length << std::endl;
	}

private:
	int m_side_length;
};

class Rectangle : public Shape
{
public:
	Rectangle(const std::string& shape_name, int length, int width)
		: Shape(shape_name)
		, m_length(length)
		, m_width(width)
	{
	}

	void getInfo() const
	{
		std::cout	<< "Area of the rectangle with length " << m_length 
					<< " and width " << m_width << " is: " << m_length * m_width << std::endl;

	}

private:
	int m_length;
	int m_width;
};

Shape* createSquare(const std::string& shape_name, int side_length);
Rectangle* createRectangle(const std::string& shape_name, int length, int width);
void howDynamicCastWorks();

} //!namespace usage_dynamic_casting
//===============================================================================================


#endif //USER_DEFINED_TYPES_CLASSES_H__

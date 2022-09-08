#include "UserDefinedTypesClasses.h"

void howVirtualFunctionsWork()
{
	Base obj_base;
	Derived obj_derived;
	std::cout << "1) Reference to base object = " << &obj_base << ", reference to derived object = " << &obj_derived << std::endl;

	//Virtual function call through reference
	Base& base_ref = obj_base;			//reference to base class pointing to a base object
	Base& derived_ref = obj_derived;	//reference to base class pointing to a derived object
	std::cout	<< "2) Comparison with 1:\n Base class reference to base object  = " << &base_ref
				<< ", base class reference to derived object = " << &derived_ref << std::endl << std::endl;

	std::cout << "3) Calling functions on REFERENCE types: " << std::endl;
	base_ref.f();
	derived_ref.f();

	Derived* base_ptr;
	//base_ptr = &obj_base; DOES NOT WORK, hence the use of static_cast
	Derived* derived_ptr;
	base_ptr = static_cast<Derived*>(&obj_base);
	derived_ptr = &obj_derived;

	
	std::cout << std::endl << "4) Calling functions on POINTER types: " << std::endl;
	base_ptr->f();
	derived_ptr->f();
}

namespace usage_dynamic_casting
{
Shape* createSquare(const std::string& shape_name, int side_length)
{
	return new Square(shape_name, side_length);
}

Rectangle* createRectangle(const std::string& shape_name, int length, int width)
{
	return new Rectangle(shape_name, length, width);
}

void howDynamicCastWorks()
{
	//Implicit upcasting; virtual functions are invoked due to the usage of pointers to the class
	Shape* quad = createSquare("quadrilateral", 10);
	std::cout << "Call getInfo() on a pointer to Shape storing a pointer to Square: "; 
	quad->getInfo(); //will call Square::getInfo() because quad stores a pointer to Square

	//Implicit upcasting; BUT virtual functions are NOT invoked since using instance of the base and derived classes
	Shape quad_1 = *(createSquare("quad", 20));
	std::cout << "Call getInfo() on a object of type Shape storing a object of type Square: ";
	quad_1.getInfo(); //will call Shape::getInfo() and NOT Square::getInfo() because quad_1 stores an instance of Square and hence virtual functions are not invoked

	//Implicit upcasting; virtual functions are invoked due to the usage of reference to the class
	Shape& quad_2 = *(createSquare("quad", 30));
	std::cout << "Call getInfo() on a reference of type Shape storing a object of type Square: ";
	quad_2.getInfo(); //will call Square::getInfo() because quad_2 is a reference to an object of type Square

	//Attempting downcasting of the parent pointer to the child pointer
	Square* square = dynamic_cast<Square*>(quad); //if dynamic_cast was not successful, the program returns a nullptr
	if (square)
	{
		std::cout << __FUNCTION__ << "(" << __LINE__ << "):: After successful attempt to dynamically cast Shape* to Square*: ";
		square->getInfo();
	}

	Rectangle* rectangle = createRectangle("quadrilateral", 30, 50);
	
	//Attempting a upcasting from Rectangle* to Shape*
	Shape* quad_3 = dynamic_cast<Shape*>(rectangle);
	if (quad_3)
	{
		std::cout << __FUNCTION__ << "(" << __LINE__ << "):: After successful attempt to dynamically cast Rectangle* to Shape*: ";
		quad_3->getInfo();
	}

	//Attempting to downcast Shape* (obtained by upcasting from a another derived class, namely, Rectangle*) to Square*
	Square* square_1 = dynamic_cast<Square*>(quad_3);
	if (square_1 == nullptr)
	{
		std::cout << "Attempt to downcast Shape* (obtained by upcasting from a another derived class, namely, Rectangle*) to Square* failed: \r\n"
			"INVALID CASTING!" << std::endl;
	}
}
}

#include <iostream>
#include "UserDefinedTypesClasses.h"
#include "LvalueRvalueSemantics.h"
#include "MoveSemanticsAndRelatedJazz.h"

int main(int* argc, char* argv[])
{
	howVirtualFunctionsWork();
	usage_dynamic_casting::howDynamicCastWorks();
	semanticslvaluervalue::runLvalueRvalueSemantics(); //Read up the file LvalueRvalueSemantics.h to understand the concept thoroughly
	movesemantics::runMoveIntroduction();

	return 0;
}
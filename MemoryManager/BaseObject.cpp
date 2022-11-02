#include "BaseObject.h"

#include <iostream>

using namespace std;

BaseObject::BaseObject()
{
	cout << "BaseObject :: constructor \n";
}

BaseObject::~BaseObject()
{
	cout << "BaseObject :: destructor \n";
}

void BaseObject::aMethod()
{
	cout << "BaseObject :: aMethod \n";
}
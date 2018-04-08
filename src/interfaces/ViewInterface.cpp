#include "ViewInterface.h"

std::string ViewInterface::getName()
{
    return name;
}

void ViewInterface::setName(std::string _name)
{
    name = _name;
}

ViewInterface::ViewInterface()
{
}

ViewInterface::~ViewInterface()
{
}
#include "ecs/component.h"
#include <iostream>

Component::Component()
{
    std::cout << "Component created" << std::endl;
}

Component::~Component()
{
}

void Component::Init()
{
}

void Component::Update()
{
    std::cout << "Component::Update()" << std::endl;
}

void Component::Destroy()
{
}
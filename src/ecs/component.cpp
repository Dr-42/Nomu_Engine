#include "ecs/component.h"
#include <iostream>

Component::Component()
{
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
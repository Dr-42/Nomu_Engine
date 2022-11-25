#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <string>
#include <vector>
#include <iostream>
#include <map>

//#include "ecs/entity.h"

struct Entity_Data{
    std::string name;
    std::vector<std::string> components;
    std::string clone_source;
    std::string parent;
};

struct Component_Data{
    std::string type;
    std::string entity;
    std::map<std::string, std::string> properties;
};

struct Asset_Data{
    std::string type;
    std::string name;
    std::string path;
};

struct Node
{
	std::string name;
	std::vector<Node *> children;
	Node *parent;

	Node(const std::string &name) : name(name) {}
	~Node()
	{
		for (auto child : children)
			delete child;
	}

	void AddChild(Node *child)
	{
		children.push_back(child);
		child->parent = this;
	}

	void Print(int depth = 0)
	{
		for (int i = 0; i < depth; i++)
			std::cout << "  ";
		std::cout << name << std::endl;
		for (auto child : children)
			child->Print(depth + 1);
	}
};

class SceneManager
{
public:
//    static Entity* LoadScene(std::string path);
    std::vector<Entity_Data> entities;
    std::vector<Component_Data> components;
    std::vector<Asset_Data> assets;

    std::vector<std::string> lines;

    void ParseScene(std::string path);
    void ParseAssets();
    void ParseEntities();

private:
    int GetEntityIndex(std::string name);
    Node* Tokenize(int start, int end, std::vector<std::string> lines);
};


#endif
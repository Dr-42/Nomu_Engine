#pragma once
#include "defines.h"
#include "core/app.h"

#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "ecs/entity.h"
namespace Nomu
{
	struct Component_Data
	{
		std::string type;
		std::string entity;
		std::map<std::string, std::string> properties;
	};

	struct Entity_Data
	{
		std::string name;
		std::vector<Component_Data*> components;
		std::vector<Entity_Data*> children;
		std::string clone_source;
		std::string parent;
	};

	struct Asset_Data
	{
		std::string type;
		std::string name;
		std::string path;
	};

	struct Node
	{
		std::string name;
		std::vector<Node*> children;
		Node *parent;

		Node(const std::string &name) : name(name) {}
		~Node()
		{
			for (auto child : children)
				delete child;
		}

		void AddChild(Node* child)
		{
			children.push_back(child);
			child->parent = this;
		}

		void Print(i32 depth = 0)
		{
			for (i32 i = 0; i < depth; i++)
				std::cout << "  ";
			std::cout << name << std::endl;
			for (auto child : children)
				child->Print(depth + 1);
		}
	};

	class N_API SceneManager
	{
	public:
		SceneManager(App* app);
		Entity* LoadScene(std::string path);
		std::vector<Entity_Data> entities;
		std::vector<Asset_Data> assets;

		std::vector<std::string> lines;

		void ParseScene(std::string path);
		void ParseAssets();
		void ParseEntities();

	private:
		Node *Tokenize(i32 start, i32 end, std::vector<std::string> lines);
		Entity_Data *ParseEntity(Node *entity);
		Component_Data *ParseComponent(Node *component);
		void LoadResources(std::vector<Asset_Data> assets);
		void ParseShaderPath(std::string comb_path, std::string &vshader_path, std::string &fshader_path);

		Entity *CreateEntity(Entity_Data* entity_data, Entity* parent);
		Component *CreateComponent(Component_Data *component_data, Entity *entity);

		glm::vec4 ParseVec4(std::string value);
		glm::vec2 ParseVec2(std::string value);
		float ParseFloat(std::string value);
		i32 ParseInt(std::string value);
		bool ParseBool(std::string value);
		std::string ParseString(std::string value);

		Entity *root_en;
		App* m_app;
	};
}
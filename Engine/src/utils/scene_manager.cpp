#include "utils/scene_manager.h"

#include "components/everything.h"

#include <fstream>
#include <cctype>
#include <algorithm>
#include <iterator>

Nomu::SceneManager::SceneManager(App* app)
{
	m_app = app;
}


void Nomu::SceneManager::ParseScene(std::string path)
{
	// Load the file
	std::ifstream file;
	file.open(path, std::ios::in);

	// Check if the file is open
	if (!file.is_open())
	{
		std::cout << "Failed to open file: " << path << std::endl;
		return;
	}

	// Read the file line by line
	std::string line;
	while (std::getline(file, line))
	{
		lines.push_back(line);
	}

	// Close the file
	file.close();

	ParseAssets();
	ParseEntities();
}

// Structure in scene file:
// Assets:
//	[asset_type]
//		asset_name: asset_path
//		...
//
// Entities:
//	"entity_name" {entity clone source name if any}
//		[component_type]
//			component_property: component_property_value
//			...

// The entire structure is parsed by a tokeniser which 
// creates a Node based tree based on tabbing level

void Nomu::SceneManager::ParseAssets()
{
	// Find the start of the assets
	int start = 0;
	for (u64 i = 0; i < lines.size(); i++)
	{
		if (lines[i] == "Assets:")
		{
			start = i;
			break;
		}
	}

	// Find the end of the assets
	int end = 0;
	for (u64 i = start; i < lines.size(); i++)
	{
		if (lines[i] == "Entities:")
		{
			end = i;
			break;
		}
	}

	Node* asset_tree;
	asset_tree = Tokenize(start, end, lines);	

	// Parse the asset tree
	for (u64 i = 0; i < asset_tree->children.size(); i++)
	{
		Node* asset_type = asset_tree->children[i];

		// Parse the asset type
		for (u64 j = 0; j < asset_type->children.size(); j++)
		{
			Node* asset = asset_type->children[j];

			// Parse the asset
			Asset_Data asset_data;
			asset_data.type = asset_type->name;
			asset_data.name = asset->name.substr(0, asset->name.find(":"));
			asset_data.path = asset->name.substr(asset->name.find(":") + 2, asset->name.size());

			assets.push_back(asset_data);
		}
	}
}

void Nomu::SceneManager::ParseEntities()
{
	// Find the start of the entities
	int start = 0;
	for (u64 i = 0; i < lines.size(); i++)
	{
		if (lines[i] == "Entities:")
		{
			start = i;
			break;
		}
	}
	int end = lines.size();

	Node* entity_tree = new Node("");
	entity_tree = Tokenize(start, end, lines);

	// Parse the entity tree
	for (u64 i = 0; i < entity_tree->children.size(); i++)
	{
		if(entity_tree->children[i]->name[0] == '[')
			continue;
		else
		{
			Entity_Data* entity_data = ParseEntity(entity_tree->children[i]);
			entities.push_back(*entity_data);
		}
	}
}

Nomu::Entity_Data* Nomu::SceneManager::ParseEntity(Node *entity)
{
	// Parse the entity
	Entity_Data* entity_data = new Entity_Data();
	entity_data->name = entity->name.substr(0, entity->name.find(":"));
	if (entity->name.find(":") != entity->name.size() - 1)
		entity_data->clone_source = entity->name.substr(
			entity->name.find("(") + 1,
			entity->name.find(")") - entity->name.find("(") - 1);
	else
		entity_data->clone_source = "";

	entity_data->parent = entity->parent->name;

	// Parse the components
	for (u64 i = 0; i < entity->children.size(); i++)
	{
		if(entity->children[i]->name[0] == '[')
		{
			Component_Data* component_data = ParseComponent(entity->children[i]);
			entity_data->components.push_back(component_data);
		}
		else{
			entity_data->children.push_back(this->ParseEntity(entity->children[i]));
		}
	}

	return entity_data;
}

Nomu::Component_Data* Nomu::SceneManager::ParseComponent(Node *component)
{
	// Parse the component
	Component_Data* component_data = new Component_Data();
	component_data->type = component->name;
	component_data->entity = component->parent->name;

	// Parse the component properties
	for (u64 k = 0; k < component->children.size(); k++)
	{
		Node* property = component->children[k];

		// Parse the property
		std::string property_name = property->name.substr(0, property->name.find(":"));
		std::string property_value = property->name.substr(property->name.find(":") + 2, property->name.size());

		component_data->properties[property_name] = property_value;
	}

	return component_data;
}

Nomu::Node *Nomu::SceneManager::Tokenize(int start, int end, std::vector<std::string> lines)
{
	// Tokenise the lines into tokens based on tabs
	Node *root = new Node("root");
	int depth = 0;
	Node *current = root;

	for (int i = start + 1; i < end; i++)
	{
		std::string line = lines[i];
		if (line == "" || line[0] == '#' || line == "\n")
		{
			continue;
		}
		else
		{
			// Check if this line has 0 or 1 tab more than the previous line
			int tabs = 0;
			for (u64 j = 0; j < line.length(); j++)
			{
				if (line[j] == '\t')
				{
					tabs++;
				}
				else
				{
					break;
				}
			}

			// If this line has 0 or 1 tab more than the previous line
			if (tabs == depth || tabs == depth + 1)
			{
				// If this line has 1 tab more than the previous line
				if (tabs == depth + 1)
				{
					depth++;
				}
				// If this line has 0 tabs more than the previous line
				else if (tabs == depth)
				{
					// Go up a level
					current = current->parent;
				}

				// Create a new node
				std::string name = line.substr(tabs, line.length());
				Node *node = new Node(name);
				current->AddChild(node);
				current = node;
			}

			// If this line has more than 1 tab more than the previous line
			else if (tabs > depth + 1)
			{
				std::cout << "Error: Invalid scene file" << std::endl;
				exit(1);
			}

			// If this line has less tabs than the previous line
			else if (tabs < depth)
			{
				// Go up the tree
				for (int j = 0; j <= depth - tabs; j++)
				{
					current = current->parent;
				}
				depth = tabs;

				// Create a new node
				std::string name = line.substr(tabs, line.length());
				Node *node = new Node(name);
				current->AddChild(node);
				current = node;
			}
		}
	}
	return root;
}

void Nomu::SceneManager::LoadResources(std::vector<Asset_Data> assets){
	for(u64 i = 0; i < assets.size(); i++){
		Asset_Data* asset_data = &assets[i];
		if(asset_data->type == "[Texture]"){
			ResourceManager::LoadTexture(asset_data->path,true, asset_data->name);
		}
		else if(asset_data->type == "[Shader]"){
			std::string vshader_path, fshader_path;
			ParseShaderPath(asset_data->path, vshader_path, fshader_path);
			ResourceManager::LoadShader(vshader_path, fshader_path, "", asset_data->name);
		}
		else if (asset_data->type == "[Font]"){
			ResourceManager::LoadFont(asset_data->name, asset_data->path);
		}
	}
}



void Nomu::SceneManager::ParseShaderPath(std::string comb_path, std::string &vshader_path, std::string &fshader_path){
	int index = comb_path.find(",");
	vshader_path = comb_path.substr(0, index);
	fshader_path = comb_path.substr(index + 2, comb_path.size());
}


Nomu::Entity* Nomu::SceneManager::CreateEntity(Entity_Data* entity_data, Nomu::Entity* parent){
	Entity* entity = new Entity(entity_data->name);
	entity->SetParent(parent);
	for(u64 i = 0; i < entity_data->components.size(); i++){
		Component_Data* component_data = entity_data->components[i];
		Component* component = CreateComponent(component_data, entity);
		if(component->GetName() == "Transform"){
			continue;
		}
		else{
			entity->AddComponent(component);
		}
	}
	if(entity_data->children.size() > 0){
		for(u64 i = 0; i < entity_data->children.size(); i++){
			Entity* child = CreateEntity(entity_data->children[i], entity);
			entity->AddChild(child);
		}
	}
	return entity;
}

glm::vec4 Nomu::SceneManager::ParseVec4(std::string value){
	std::string x = value.substr(0, value.find(","));
	value = value.substr(value.find(",") + 1, value.size());
	std::string y = value.substr(0, value.find(","));
	value = value.substr(value.find(",") + 1, value.size());
	std::string z = value.substr(0, value.find(","));
	value = value.substr(value.find(",") + 1, value.size());
	std::string w = value.substr(0, value.find(","));
	return glm::vec4(std::stof(x), std::stof(y), std::stof(z), std::stof(w));
}

glm::vec2 Nomu::SceneManager::ParseVec2(std::string value){
	std::string x = value.substr(0, value.find(","));
	std::string y = value.substr(value.find(",") + 1, value.size());
	return glm::vec2(std::stof(x), std::stof(y));
}

float Nomu::SceneManager::ParseFloat(std::string value){
	return std::stof(value);
}

int Nomu::SceneManager::ParseInt(std::string value){
	return std::stoi(value);
}

bl Nomu::SceneManager::ParseBool(std::string value){
	return value == "true";
}

std::string Nomu::SceneManager::ParseString(std::string value){
	return value;
}

Nomu::Component* Nomu::SceneManager::CreateComponent(Component_Data* component_data, Entity* entity){
	Component* component = NULL;
	std::map<std::string, std::string>::iterator it;
	if(component_data->type == "[Transform]"){
		Transform* transform = entity->GetComponent<Transform>();
		for(it = component_data->properties.begin(); it != component_data->properties.end(); it++){
			if(it->first == "position"){
				transform->SetPosition(ParseVec2(it->second));
			}
			else if(it->first == "rotation"){
				transform->SetRotation(ParseFloat(it->second));
			}
			else if(it->first == "scale"){
				transform->SetScale(ParseVec2(it->second));
			}
			else if(it->first == "active"){
				transform->active = ParseBool(it->second);
			}
		}
		component = transform;	
	}
	else if(component_data->type == "[UISprite]"){
		Texture2D* texture;
		glm::vec4 color;
		Shader* shader;
		bl active;
		for(it = component_data->properties.begin(); it != component_data->properties.end(); it++){
			if(it->first == "texture"){
				texture = ResourceManager::GetTexture(it->second);
			}
			else if(it->first == "color"){
				color = ParseVec4(it->second);
			}
			else if(it->first == "shader"){
				shader = ResourceManager::GetShader(it->second);
			}
			else if(it->first == "active"){
				active = ParseBool(it->second);
			}
		}
		UI_Sprite* sprite = new UI_Sprite(texture, color, shader, m_app);
		sprite->active = active;
		component = sprite;
	}
	else if(component_data->type == "[Text]"){
		std::string text;
		glm::vec4 color;
		Shader* shader;
		std::string font_path;
		int font_size;
		bl active;

		for(it = component_data->properties.begin(); it != component_data->properties.end(); it++){
			if(it->first == "text"){
				text = it->second;
			}
			else if(it->first == "color"){
				color = ParseVec4(it->second);
			}
			else if(it->first == "shader"){
				shader = ResourceManager::GetShader(it->second);
			}
			else if(it->first == "font"){
				font_path = ResourceManager::GetFont(it->second);
			}
			else if(it->first == "size"){
				font_size = ParseInt(it->second);
			}
			else if(it->first == "active"){
				active = ParseBool(it->second);
			}
		}
		Text* text_comp = new Text(text, font_path, shader, font_size, m_app);
		text_comp->SetColor(color);
		text_comp->active = active;
		component = text_comp;
	}
	else if(component_data->type == "[Event_listener]"){
		bl active;
		for(it = component_data->properties.begin(); it != component_data->properties.end(); it++){
			if(it->first == "active"){
				active = ParseBool(it->second);
			}
		}

    	EventListener* evl = new EventListener(m_app);
		evl->active = active;
		component = evl;
	}
	else if(component_data->type == "[Script]"){
		std::string script_name;
		bl active;
		for(it = component_data->properties.begin(); it != component_data->properties.end(); it++){
			if(it->first == "script"){
				script_name = it->second;
			}
			else if(it->first == "active"){
				active = ParseBool(it->second);
			}
		}
		Script* script = Script::Create(script_name);
		script->active = active;
		component = dynamic_cast<Component*>(script);
	}

	else{
		std::cout << "Component type not found: " << component_data->type << std::endl;
		exit(1);
	}

	return component;
}

Nomu::Entity* Nomu::SceneManager::LoadScene(std::string path){
	ParseScene(path);

	LoadResources(assets);

	root_en = new Entity("root");
	// Create the entities
	for(u64 i = 0; i < entities.size(); i++){
		Entity_Data* entity_data = &entities[i];
		root_en->AddChild(CreateEntity(entity_data, root_en));
	}

	return root_en;
}
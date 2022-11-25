#include "utils/scene_manager.h"

#include <fstream>
#include <cctype>
#include <algorithm>

void SceneManager::ParseScene(std::string path)
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

void SceneManager::ParseAssets()
{
	// Find the start of the assets
	int start = 0;
	for (int i = 0; i < lines.size(); i++)
	{
		if (lines[i] == "Assets:")
		{
			start = i;
			break;
		}
	}

	// Find the end of the assets
	int end = 0;
	for (int i = start; i < lines.size(); i++)
	{
		if (lines[i] == "Entities:")
		{
			end = i;
			break;
		}
	}

	Asset_Data asset;
	// Parse the assets
	for (int i = start + 1; i < end; i++)
	{
		std::string line = lines[i];
		if (line == "")
		{
			continue;
		}
		else if (line == "\t[Shader]")
		{
			asset = Asset_Data();
			asset.type = "Shader";
		}
		else if (line == "\t[Texture]")
		{
			asset = Asset_Data();
			asset.type = "Texture";
		}
		else if (line == "\t[Font]")
		{
			asset = Asset_Data();
			asset.type = "Font";
		}
		else
		{
			std::string name = line.substr(2, line.find(":") - 2);
			std::string path = line.substr(line.find(":") + 2, line.length());
			asset.name = name;
			asset.path = path;
			asset_data.push_back(asset);
		}
	}
}

void SceneManager::ParseEntities()
{
	// Find the start of the entities
	int start = 0;
	for (int i = 0; i < lines.size(); i++)
	{
		if (lines[i] == "Entities:")
		{
			start = i;
			break;
		}
	}
	int end = lines.size();

	Node* entity_tree;
	entity_tree = Tokenize(start, end, lines);
	entity_tree->Print(6);
}

Node* SceneManager::Tokenize(int start, int end, std::vector<std::string> lines)
{
	// Tokenise the lines into tokens based on tabs
	Node* root = new Node("root");
	int depth = 0;
	Node *current = root;

	for (int i = start + 1; i < end; i++)
	{
		std::string line = lines[i];
		if (line == "")
		{
			continue;
		}
		else
		{
			// Check if this line has 0 or 1 tab more than the previous line
			int tabs = 0;
			for (int j = 0; j < line.length(); j++)
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

int SceneManager::GetEntityIndex(std::string name)
{
	for (int i = 0; i < entity_data.size(); i++)
	{
		if (entity_data[i].name == name)
		{
			return i;
		}
	}
	return -1;
}

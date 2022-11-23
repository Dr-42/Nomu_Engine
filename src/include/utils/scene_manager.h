#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>

struct Scene{
    std::string name;
    std::string path;
    std::vector<std::string> entities;
};

struct Entity_Data{
    std::string name;
    std::vector<std::string> components;
};

struct Component_Data{
    std::string type;
    std::string entity;
    std::map<std::string, std::string> properties;
};

struct Asset_Data{
    std::string type;
    std::string path;
};

class SceneLoader
{
public:
    static void LoadScene(std::string path);
private:
    std::vector<Scene> scene_data;
    std::vector<Entity_Data> entity_data;
    std::vector<Component_Data> component_data;
    std::vector<Asset_Data> asset_data;

    static void ParseScene(std::string path);
};


#endif
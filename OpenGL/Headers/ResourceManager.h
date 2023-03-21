#pragma once
#include <iostream>
#include <unordered_map>
#include "IResource.h"
#include "Debug.h"

namespace Resources
{
	static class ResourceManager
    {
    public:
        ~ResourceManager() {}
        static void DeleteMap()
        {
            for (std::pair<std::string, IResource*> resource : resources)
            {
                delete resource.second;
            }
        }

        template <class T>
        static T* Create(const std::string& name, const std::string& path)
        {
            bool IsInherit = std::is_base_of<IResource, T>::value;
            Assert(!IsInherit);

            IResource* resource_base = (IResource*)(new T);
            
            if (resources.find(name) == resources.end()) //Create new resource
            {              
                resource_base->SetResourceId(resources.size());
                resource_base->SetResourcePath(path);
                resource_base->LoadResource();
                resources.emplace(name, resource_base);
                return (T*)resource_base;
            }
            else //Replace resource
            {
                resource_base->SetResourcePath(path);
                resource_base->LoadResource();
                resources.at(name) = resource_base;
                return (T*)resource_base;
            }
            
        }

        static Model* CustomCreate(const std::string& name, std::vector<Vertex> _vertexBuffer)
        {
            Model* resource_base = new Model;

            bool existsAlready;
            int index = 0;
            for (Vertex v : _vertexBuffer)
            {
                existsAlready = false;
                for (unsigned int i = 0; i < resource_base->vertexBuffer.size(); i++)
                {
                    if (v.position == resource_base->vertexBuffer[i].position && v.normal == resource_base->vertexBuffer[i].normal && v.textureUV == resource_base->vertexBuffer[i].textureUV)
                    {
                        resource_base->indexBuffer.push_back(i);
                        existsAlready = true;
                        break;
                    }
                }
                if (!existsAlready)
                {
                    resource_base->vertexBuffer.push_back(v);
                    resource_base->indexBuffer.push_back(index);
                    index++;
                }
            }

            if (resources.find(name) == resources.end()) //Create new resource
            {
                resource_base->SetResourceId(resources.size());
                resources.emplace(name, resource_base);
                return resource_base;
            }
            else //Replace resource
            {
                resources.at(name) = resource_base;
                return resource_base;
            }

        }

        template <typename T>
        static T* Get(const std::string& name)
        {
            return (T*)(resources.find(name)->second);
        }

    private:
        ResourceManager() {};
        static std::unordered_map<std::string, IResource*> resources;
        

    };
} 
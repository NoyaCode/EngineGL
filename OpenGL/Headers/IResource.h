#pragma once
#include <iostream>
#include <vector>
#include <filesystem>
#include "MyMaths.h"

using namespace Core::Maths;

namespace Resources
{
    class  IResource
    {
    public:
        IResource() 
        {
            resourceId = NULL;
        }
        virtual ~IResource() {}

        virtual void LoadResource() = 0;
        virtual void UnloadResource() = 0;

        void SetResourceId(unsigned int id);
        unsigned int GetResourceId() const;

        void SetResourcePath(const std::string& path);
        std::string GetResourcePath() const;

    protected:
        unsigned int resourceId;
        std::string resourcePath;

    };


    class Model : public IResource
    {
    public:
        Model();
        ~Model();
        void LoadResource();
        void UnloadResource();
    
        std::vector<Vertex> vertexBuffer;
        std::vector<uint32_t> indexBuffer;

        void SetBuffersAndVAO();
        unsigned int GetVAO();
    private:
        unsigned int VBO, VAO, EBO;
    };

    class Texture : public IResource
    {
    public:
        ~Texture();
        void LoadResource();
        void UnloadResource();
        unsigned int texKey;
    };

    class Shader : public IResource
    {
    public:
        Shader() 
        {
            vertexShader = fragmentShader = shaderProgram = NULL;
        }
        ~Shader() {};
        void LoadResource();
        void UnloadResource();

        bool SetVertexShader(std::string const& filename);
        bool SetFragmentShader(std::string const& filename);
        bool Link();
        void SetShaders(std::string const& vertexPath, std::string const& fragPath);

        int GetProgram();

    private:
        int vertexShader;
        int fragmentShader;
        int shaderProgram;
    };
}
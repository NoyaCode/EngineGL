#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "IResource.h"
#include "Debug.h"
#include <unordered_map>
#include "ResourceManager.h"
#include "IResource.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <STB_Image/stb_image.h>

using namespace Resources;
std::unordered_map<std::string, IResource*> ResourceManager::resources;

#pragma region IResource

void IResource::SetResourceId(unsigned int id)
{
	resourceId = id;
}
unsigned int IResource::GetResourceId() const
{
	return resourceId;
}

void IResource::SetResourcePath(const std::string& path)
{
	resourcePath = path;
}

std::string IResource::GetResourcePath() const
{
	return resourcePath;
}

#pragma endregion



#pragma region Model

Model::Model()
{
	vertexBuffer = {};
	indexBuffer = {};
}

Model::~Model()
{
	vertexBuffer.clear();
	indexBuffer.clear();

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Model::LoadResource()
{
	std::ifstream obj;
	obj.open(resourcePath);
	if (!obj.is_open()) 
		DEBUG_LOG("|| WARNING || Could not open \"%s\" file", resourcePath.c_str());

	std::vector<Vector3> v;
	std::vector<Vector3> vn;
	std::vector<Vector2> vt;
	unsigned int index = 0;

	bool normalsGave = false;

	Vector3 pos;
	Vector3 normal;
	Vector2 texture;
	
	char slash;
	unsigned int indexPos, indexTexture, indexNormal;
	Vertex newVertex;
	bool existsAlready;
	
	std::string line;
	while (std::getline(obj, line)) 
	{
		if (line[0] == 'v')
		{
			if (line[1] == ' ')
			{
				std::stringstream ss;
				ss.str(line.substr(2));
				ss >> pos.x >> pos.y >> pos.z;
				v.push_back(pos);
				
				
			}
			else if (line[1] == 't')
			{
				std::stringstream ss;
				ss.str(line.substr(3));
				ss >> texture.x >> texture.y;
				vt.push_back(texture);
			}
			else
			{
				std::stringstream ss;
				ss.str(line.substr(2));
				ss >> normal.x >> normal.y >> normal.z;
				vn.push_back(normal);
			}
		}
		else if(line[0] == 'f')
		{
			line = line.substr(2);
			std::stringstream ss;
			ss.str(line);

			for (int i = 0; i < 3; i++)
			{
				ss >> indexPos >> slash >> indexTexture >> slash >> indexNormal;
				if (indexNormal)
				{
					newVertex = { v[indexPos - 1], vn[indexNormal - 1], vt[indexTexture - 1] };
				}
				else
				{
					newVertex = { v[indexPos - 1], Vector3(0, 0, 0), vt[indexTexture - 1] };
				}
				

				existsAlready = false;
				for (unsigned int i = 0; i < vertexBuffer.size(); i++)
				{
					if (newVertex.position == vertexBuffer[i].position && newVertex.normal == vertexBuffer[i].normal && newVertex.textureUV == vertexBuffer[i].textureUV)
					{
						indexBuffer.push_back(i);
						existsAlready = true;
						break;
					}
				}
				if (!existsAlready)
				{
					vertexBuffer.push_back(newVertex);
					indexBuffer.push_back(index);
					index++;
				}
			}
		
		}
	}
	obj.close();	
}

void Model::UnloadResource()
{
}

void Model::SetBuffersAndVAO()
{
	glGenBuffers(1, &VBO);

	glGenBuffers(1, &EBO);

	glGenVertexArrays(1, &VAO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	//glNamedBufferData(VBO, sizeof(vertexBuffer), &vertexBuffer, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexBuffer.size(), &vertexBuffer[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indexBuffer.size(), &indexBuffer[0], GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

unsigned int Model::GetVAO()
{
	if (VAO)
		return VAO;
	return NULL;
}

#pragma endregion



#pragma region Texture

Texture::~Texture()
{
	UnloadResource();
}

void Texture::LoadResource()
{
	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(resourcePath.c_str(), &width, &height, &nrChannels, 0);

	glGenTextures(1, &texKey);
	glBindTexture(GL_TEXTURE_2D, texKey);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	glBindTextureUnit(resourceId, texKey);
}


void Texture::UnloadResource()
{
	glDeleteTextures(1, &resourceId);
}

#pragma endregion



#pragma region Shader


void Shader::LoadResource()
{
}


void Shader::UnloadResource()
{
}

bool Shader::SetVertexShader(std::string const& filename)
{
	std::ifstream shaderFile;
	shaderFile.open(filename);
	if (!shaderFile.is_open())
		DEBUG_LOG("|| WARNING || Could not open \"%s\" file", filename.c_str());

	std::string shaderStr;
	std::string line;
	while (std::getline(shaderFile, line))
	{
		shaderStr += '\n' + line;
	}
	shaderFile.close();
	const char* shaderSource = shaderStr.c_str();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &shaderSource, NULL);
	glCompileShader(vertexShader);
	int success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		DEBUG_LOG("ERROR::SHADER::VERTEX::COMPILATION_FAILED", filename.c_str())
		return false;
	}
	return true;
}

bool Shader::SetFragmentShader(std::string const& filename)
{
	std::ifstream shaderFile;
	shaderFile.open(filename);
	if (!shaderFile.is_open())
		DEBUG_LOG("|| WARNING || Could not open \"%s\" file", filename.c_str());

	std::string shaderStr;
	std::string line;
	while (std::getline(shaderFile, line))
	{
		shaderStr += '\n' + line;
	}
	shaderFile.close();
	const char* shaderSource = shaderStr.c_str();

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &shaderSource, NULL);
	glCompileShader(fragmentShader);
	int success;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		DEBUG_LOG("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED")
		return false;
	}
	return true;
}

bool Shader::Link()
{
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	int success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) 
	{
		DEBUG_LOG("ERROR::SHADER::PROGRAM::LINKING_FAILED")
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return false;
}

int Shader::GetProgram()
{
	if(shaderProgram)
		return shaderProgram;
	return NULL;
}
void Shader::SetShaders(std::string const& vertexPath, std::string const& fragPath)
{
	SetVertexShader(vertexPath);
	SetFragmentShader(fragPath);
	Link();
}
#pragma endregion
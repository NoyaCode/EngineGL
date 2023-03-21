#include "Renderer.h"

void Renderer::RenderMesh(Mesh* mesh)
{
	if (!mesh->IsActive())
		return;

	int program = mesh->shader->GetProgram();
	glUseProgram(program);

	glUniform1i(glGetUniformLocation(program, "texture1"), mesh->texture->GetResourceId());

	bool isActive;
	int index = 0;

	shader.SetInt(program, "maxDirLights", currentDirectionalLights.size());
	for (DirectionalLight* light : currentDirectionalLights)
	{
		std::string number = std::to_string(index);

		isActive = light->IsActive();
		shader.SetInt(program, ("dirLights[" + number + "].isActive").c_str(), isActive);
		if (isActive)
		{
			shader.SetVec3(program, ("dirLights[" + number + "].direction").c_str(), light->direction);
			shader.SetVec3(program, ("dirLights[" + number + "].ambient").c_str(), light->ambientColor * 0.2f);
			shader.SetVec3(program, ("dirLights[" + number + "].diffuse").c_str(), light->diffuseColor * 0.5f);
			shader.SetVec3(program, ("dirLights[" + number + "].specular").c_str(), light->specularColor);
		}
	}
	
	index = 0;
	shader.SetInt(program, "maxPointLights", currentPointLights.size());
	for (PointLight *light : currentPointLights)
	{
		std::string number = std::to_string(index);

		isActive = light->IsActive();
		shader.SetInt(program, ("pointLights[" + number + "].isActive").c_str(), isActive);
		if (isActive)
		{
			shader.SetVec3(program, ("pointLights[" + number + "].position").c_str(), light->gameObject->transform.position);
			shader.SetVec3(program, ("pointLights[" + number + "].ambient").c_str(), light->ambientColor * 0.3f);
			shader.SetVec3(program, ("pointLights[" + number + "].diffuse").c_str(), light->diffuseColor * 0.7f);
			shader.SetVec3(program, ("pointLights[" + number + "].specular").c_str(), light->specularColor);
			shader.SetFloat(program, ("pointLights[" + number + "].constant").c_str(), 1.0f);
			shader.SetFloat(program, ("pointLights[" + number + "].linear").c_str(), 0.09f);
			shader.SetFloat(program, ("pointLights[" + number + "].quadratic").c_str(), 0.032f);
		}
		index++;
	}

	index = 0;
	shader.SetInt(program, "maxSpotLights", currentSpotLights.size());
	for (SpotLight* light : currentSpotLights)
	{
		std::string number = std::to_string(index);

		isActive = light->IsActive();
		shader.SetInt(program, ("spotLights[" + number + "].isActive").c_str(), isActive);
		if (isActive)
		{
			shader.SetVec3(program, ("spotLights[" + number + "].direction").c_str(), light->direction);
			shader.SetVec3(program, ("spotLights[" + number + "].position").c_str(), light->gameObject->transform.position);
			shader.SetFloat(program, ("spotLights[" + number + "].cutOff").c_str(), cosf(light->angle * DEG2RAD));
			shader.SetFloat(program, ("spotLights[" + number + "].outerCutOff").c_str(), cosf(light->angle * 1.4 * DEG2RAD));
			shader.SetVec3(program, ("spotLights[" + number + "].ambient").c_str(), light->ambientColor * 0.1f);
			shader.SetVec3(program, ("spotLights[" + number + "].diffuse").c_str(), light->diffuseColor * 0.7f);
			shader.SetVec3(program, ("spotLights[" + number + "].specular").c_str(), light->specularColor);
			shader.SetFloat(program, ("spotLights[" + number + "].constant").c_str(), 1.0f);
			shader.SetFloat(program, ("spotLights[" + number + "].linear").c_str(), 0.09f);
			shader.SetFloat(program, ("spotLights[" + number + "].quadratic").c_str(), 0.032f);
		}
	}	
	
	shader.SetVec3(program, "viewPos", *currentViewPos);

	shader.SetMat4(program, "model", mesh->gameObject->GetWorldModel());

	shader.SetMat4(program, "mvp", mesh->gameObject->MVP);

	glBindVertexArray(mesh->data->GetVAO()); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, mesh->data->indexBuffer.size(), GL_UNSIGNED_INT, 0);

	// glBindVertexArray(0); // no need to unbind it every time
}

using namespace Physics;

void LowRenderer::Renderer::RenderColliders()
{
	//glClear(GL_DEPTH_BUFFER_BIT);

	int program = ResourceManager::Get<Shader>("colliderShader")->GetProgram();
	glUseProgram(program);

	for (Collider* c : Collision::currentColliders) 
	{
		if (c->show && c->IsActive(true))
			c->ShowCollider(program);
	}
}


void Renderer::SendToShader::SetInt(int shaderProgram, const char* name, int value)
{
	glUniform1iv(glGetUniformLocation(shaderProgram, name), 1, &value);
}
void Renderer::SendToShader::SetFloat(int shaderProgram, const char* name, float value)
{
	glUniform1fv(glGetUniformLocation(shaderProgram, name), 1, &value);
}
void Renderer::SendToShader::SetVec3(int shaderProgram, const char* name, Vector3 value)
{
	glUniform3fv(glGetUniformLocation(shaderProgram, name), 1, &value.x);
}
void Renderer::SendToShader::SetVec4(int shaderProgram, const char* name, Vector4 value)
{
	glUniform4fv(glGetUniformLocation(shaderProgram, name), 1, &value.x);
}
void Renderer::SendToShader::SetMat4(int shaderProgram, const char* name, Matrix4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, GL_TRUE, value.ptr());
}
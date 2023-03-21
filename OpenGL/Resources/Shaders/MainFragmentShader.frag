#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
uniform sampler2D texture1;
uniform vec3 viewPos;

// Structs

struct DirLight {
    int isActive;
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

#define MAX_DIR_LIGHTS 2
uniform DirLight dirLights[MAX_DIR_LIGHTS];
uniform int maxDirLights;

struct PointLight {
    int isActive;
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
#define MAX_POINT_LIGHTS 3 
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int maxPointLights;

struct SpotLight { 
    int isActive;
    vec3  position;
    vec3  direction;

    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
}; 

#define MAX_SPOT_LIGHTS 2
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform int maxSpotLights;

// Fuctions

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    vec3 ambient  = light.ambient;
    vec3 diffuse  = light.diffuse  * diff;
    vec3 specular = light.specular * spec;
    return (ambient + diffuse + specular);
}  

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = light.ambient;
    vec3 diffuse = light.diffuse * diff;
    vec3 specular = light.specular * spec;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight spotLight, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    
    vec3 lightDir = normalize(spotLight.position - fragPos);
    float theta = dot(lightDir, normalize(-spotLight.direction)); 
    float epsilon = spotLight.cutOff - spotLight.outerCutOff;
    float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
    
    if(theta > spotLight.outerCutOff) 
    {   
        float diff = max(dot(normal, lightDir), 0.0);

        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

        float distance = length(spotLight.position - fragPos);
        float attenuation = 1.0 / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));

        vec3 diffuse  = spotLight.diffuse  * diff * intensity * attenuation;
        vec3 specular  = spotLight.specular * spec * intensity * attenuation;

        return (spotLight.ambient + diffuse + specular);  
    }
    return spotLight.ambient;
}

// Main

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec4 TextureColor = texture(texture1, TexCoord);

    vec3 result;
    bool lightActive = false;

    //directional light
    for(int i = 0; i < maxDirLights; i++)
    {
        if(dirLights[i].isActive == 1)
        {
            result = CalcDirLight(dirLights[i], norm, viewDir);
            lightActive = true;
        }
    }

    //point lights
    for(int i = 0; i < maxPointLights; i++)
    {
        if(pointLights[i].isActive == 1)
        {
            result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
            lightActive = true;
        }
    }

    //spot light
    for(int i = 0; i < maxSpotLights; i++)
    {
        if(spotLights[i].isActive == 1)
        {
            result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);
            lightActive = true;
        }
    }

    if(lightActive)
        FragColor = vec4(result, 1.0) * TextureColor;
    else
        FragColor = TextureColor;
}

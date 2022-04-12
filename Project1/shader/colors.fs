#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform float emission_light;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
}; 
  
uniform Material material;

struct Light {
    vec3 position;
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Light light; 

void main()
{
    //vec3 lightDir = normalize(-light.direction);

    vec3 lightDir = normalize(light.position - FragPos);
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 

    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    ambient *= attenuation;

	// diffuse 
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    diffuse *= attenuation;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    specular *= attenuation;

    // emission
    vec3 emission = vec3(0.0);
    if (texture(material.specular, TexCoords).r == 0.0)
    {    
        emission = emission_light * vec3(texture(material.emission, TexCoords));
    }

	vec3 result = ambient + diffuse + specular + emission;
	FragColor = vec4(result, 1.0);
}
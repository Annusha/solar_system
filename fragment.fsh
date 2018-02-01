#version 400
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material {
    sampler2D texture_diffuse;
    sampler2D texture_specular;
//    sampler2D texture_height;
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;

    float shininess;
};

struct Light {
    vec3 position;

    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
};

uniform vec3 viewPos;
uniform Light light;
uniform Material material;
uniform sampler2D texture_diffuse1;

void main()
{
//    FragColor = texture2D(texture_diffuse1, TexCoords);
    // ambient
    vec3 ambient = material.ambient * texture2D(material.texture_diffuse, TexCoords).rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = material.diffuse * diff * texture2D(material.texture_diffuse, TexCoords).rgb;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec * texture2D(material.texture_specular, TexCoords).rgb;

    vec3 result = ambient + diffuse + specular;
//    vec3 result = ambient + diffuse;
    FragColor = vec4(result, 1.0);
}

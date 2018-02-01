#ifndef MATERIAL
#define MATERIAL

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "shader.h"
#include "texture.h"


class Material {
public:
    Shader* shader;

    glm::vec3 ambient;      // mtl file: Ka
    glm::vec3 diffuse;      // mtl file: Kd
    glm::vec3 specular;     // mtl file: Ks

    float shininess;        // mtl file: Ns

    bool is_sun = false;    // the sun is shaded differently

    std::vector<Texture*> textures;

    Material() {};
    Material(std::vector<Texture*> textures,
             glm::vec3 ambient,
             glm::vec3 diffuse,
             glm::vec3 specular,
             float shininess);
    ~Material() {};

    void activateTextures(Shader shader);
    void updateMaterialUniforms(Shader shader);
};


#endif // MATERIAL


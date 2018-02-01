#include "material.h"

Material::Material(std::vector<Texture *> textures, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
{
    this->textures = textures;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->shininess = shininess;
}

void Material::updateMaterialUniforms(Shader shader)
{
    shader.setVec3("material.ambient", ambient);
    shader.setVec3("material.diffuse", diffuse);
    shader.setVec3("material.specular", specular);
    shader.setFloat( "material.shininess", shininess);
}

void Material::activateTextures(Shader shader)
{
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i]->type;
//        if(name == "texture_diffuse")
//            number = std::to_string(diffuseNr++);
//        else if(name == "texture_specular")
//            number = std::to_string(specularNr++); // transfer unsigned int to stream
//        else if(name == "texture_normal")
//            number = std::to_string(normalNr++); // transfer unsigned int to stream
//        else if(name == "texture_height")
//            number = std::to_string(heightNr++); // transfer unsigned int to stream

        textures.at(i)->use(shader.ID, ("material." + name).c_str(), i);
    }

}



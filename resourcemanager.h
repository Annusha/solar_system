#ifndef RESOURCEMANAGER
#define RESOURCEMANAGER

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "material.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

class ResourceManager {
private:
    std::ifstream open_file(std::string path);
    void getDirectoryAndFilename(std::string path, std::string& directory, std::string& filename);

    bool getSimilarVertex(Vertex vertex, std::vector<Vertex>& vertices, GLuint& index);
    void processVertices(GLuint vertexIndex, GLuint normalIndex, GLuint texIndex, std::vector<glm::vec3> &positions,std::vector<glm::vec3> &normals,std::vector<glm::vec2> &texCoords,std::vector<Vertex> &vertices,std::vector<GLuint> &indices);

public:
    Mesh *load_obj(std::string directory, std::string filename);
    Material *load_mtl(std::string directory, std::string filename);
    Texture* load_texture(std::string directory, std::string filename, std::string type);
    Shader* load_shader(const char *vertexfile, const char *fragmentfile, const char *geometryfile = 0);

    void load(std::string path, Mesh* mesh, Material* material, string mtlFile);
    void draw(Shader shader, Mesh &mesh, Material &material);

    std::vector<Texture*> textures_loaded;
    std::vector<Mesh*> meshes_loaded;
    std::vector<Shader*> shaders_loaded;

    void addTexture(Texture* texture);
    void addMesh(Mesh* mesh);
    void addShader(Shader* shader);

    Texture* checkTexture(std::string path);
    Mesh* checkMesh(std::string path);
    Shader* checkShader(std::string path);

    ~ResourceManager();

    template <class T>
    void deleteRescource(T objectArray);
};

template <class T>
void ResourceManager::deleteRescource(T objectArray){
    for (typename T::iterator it = objectArray.begin(); it != objectArray.end(); it++){
        delete *it;
    }
}

#endif // RESOURCEMANAGER


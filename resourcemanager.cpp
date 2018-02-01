#include "resourcemanager.h"

std::ifstream ResourceManager::open_file(std::string path){
    std::ifstream inputFileStream(path.c_str(), std::ios::in);

    if (!inputFileStream.is_open()) {
        throw std::runtime_error(std::string("Cannot open ") + path);
    }
    return inputFileStream;
}

void ResourceManager::getDirectoryAndFilename(std::string path, std::string& directory, std::string& filename) {
    directory = path.substr(0, path.find_last_of('/'));
    filename = path.substr(path.find_last_of('/')+1);
}

Material* ResourceManager::load_mtl(std::string directory, std::string filename) {
    std::string path = directory + "/" + filename;
    std::ifstream inputFileStream = open_file(path);
    std::string line;

    std::vector<Texture*> textures;

    glm::vec3 ambient = glm::vec3(1);
    glm::vec3 diffuse = glm::vec3(1);
    glm::vec3 specular = glm::vec3(1);
    float shininess = 1.0f;

    while (getline(inputFileStream, line)) {
        if (line.substr(0, 2) == "Ns") {
            std::istringstream s(line.substr(2));
            s >> shininess;
        }
        else if (line.substr(0, 2) == "Ka") {
            std::istringstream s(line.substr(2));
            s >> ambient.x; s >> ambient.y; s >> ambient.z;
        }
        else if (line.substr(0, 2) == "Kd") {
            std::istringstream s(line.substr(2));
            s >> diffuse.x; s >> diffuse.y; s >> diffuse.z;
        }
        else if (line.substr(0, 2) == "Ks") {
            std::istringstream s(line.substr(2));
            s >> specular.x; s >> specular.y; s >> specular.z;
        }
        else if (line.substr(0, 6) == "map_Kd") {
            std::istringstream s(line.substr(6));
            std::string mtlFilename;
            s >> mtlFilename;
            Texture* texture = load_texture(directory, mtlFilename, "texture_diffuse");
            textures.push_back(texture);
        }
        else if (line.substr(0, 6) == "map_Ks") {
            std::istringstream s(line.substr(6));
            std::string mtlFilename;
            s >> mtlFilename;
            Texture* texture = load_texture(directory, mtlFilename, "texture_specular");
            textures.push_back(texture);
        }
        else if (line.substr(0, 6) == "map_Ka") {
            std::istringstream s(line.substr(6));
            std::string mtlFilename;
            s >> mtlFilename;
            Texture* texture = load_texture(directory, mtlFilename, "texture_ambient");
            textures.push_back(texture);
        }
    }
    inputFileStream.close();
    Material* material = new Material(textures, ambient, diffuse, specular, shininess);
    return material;
}

Texture* ResourceManager::load_texture(std::string directory, std::string filename, std::string type) {
    std::string path = directory + "/" + filename;

    Texture* texture = checkTexture(path);

    if(texture){
        return texture;
    }

    texture = new Texture(path);
    texture->type = type;
    addTexture(texture);
    return texture;
}

void ResourceManager::load(std::string path, Mesh *mesh, Material *material, std::string mtlFile) {
    std::string directory;
    std::string filename;
//    std::string mtlFile;

    getDirectoryAndFilename(path, directory, filename);

    *mesh = *load_obj(directory, filename);

    if (mtlFile.compare("") != 0){
        *material = *load_mtl(directory, mtlFile);
    }
}

void ResourceManager::draw(Shader shader, Mesh& mesh, Material& material)
{
    material.activateTextures(shader);
    material.updateMaterialUniforms(shader);
    mesh.Draw(shader);
//    for(unsigned int i = 0; i < meshes.size(); i++)
//        meshes[i].Draw(shader, material);
}

Mesh* ResourceManager::load_obj(std::string directory, std::string filename) {
    std::string path = directory + "/" + filename;

    Mesh* mesh = checkMesh(path);

    if(mesh){
        return mesh;
    }

    std::ifstream inputFileStream = open_file(path);

    std::string line;
    glm::vec3 vec;
    glm::vec2 tex;

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;

    std::vector<GLuint> indices;

    std::vector<Vertex> vertices;

    while (getline(inputFileStream, line)) {
        if (line.substr(0, 2) == "v ") {
            std::istringstream s(line.substr(2));
            s >> vec.x; s >> vec.y; s >> vec.z;
            positions.push_back(vec);
        }
        else if (line.substr(0, 2) == "vn") {
            std::istringstream s(line.substr(2));
            s >> vec.x; s >> vec.y; s >> vec.z;
            normals.push_back(vec);
        }
        else if (line.substr(0, 2) == "vt") {
            std::istringstream s(line.substr(2));
            s >> tex.x; s >> tex.y;
            texCoords.push_back(tex);
        }
        else if (line.substr(0, 2) == "f ") {
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = sscanf(line.substr(2).c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9){
                matches = sscanf(line.substr(2).c_str(), "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
                if (matches != 6) {
                    matches = sscanf(line.substr(2).c_str(), "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
                    if (matches != 6) {
                        matches = sscanf(line.substr(2).c_str(), "%d %d %d\n", &vertexIndex[0], &vertexIndex[1],
                                &vertexIndex[2]);
                        if (matches != 3) {
                            printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                            return nullptr;
                        }
                    }
                }
            }

            processVertices(vertexIndex[0]-1, normalIndex[0]-1, uvIndex[0]-1, positions, normals, texCoords, vertices, indices);
            processVertices(vertexIndex[1]-1, normalIndex[1]-1, uvIndex[1]-1, positions, normals, texCoords, vertices, indices);
            processVertices(vertexIndex[2]-1, normalIndex[2]-1, uvIndex[2]-1, positions, normals, texCoords, vertices, indices);
        }
//        else if (line.substr(0, 6) == "mtllib") {
//            std::istringstream s(line.substr(6));
//            s >> mtlFile;
//        }
        else if (line[0] == '#') { /* ignoring this line */}
    }
    inputFileStream.close();
    mesh = new Mesh(vertices, indices);
    mesh->path = path;
    addMesh(mesh);
    return mesh;
}

bool ResourceManager::getSimilarVertex(Vertex vertex, std::vector<Vertex> &vertices, GLuint& index) {
    for(size_t i=0; i< vertices.size(); i++){
        Vertex currentVertex = vertices[i];
        if(vertex.position == currentVertex.position &&
                vertex.normal == currentVertex.normal &&
                vertex.texCoords == currentVertex.texCoords
                ){
            index = i;
            return 1;
        }
    }
    return 0;
}

void ResourceManager::processVertices(GLuint vertexIndex,
                                      GLuint normalIndex,
                                      GLuint texIndex,
                                      std::vector<glm::vec3>& positions,
                                      std::vector<glm::vec3> &normals,
                                      std::vector<glm::vec2> &texCoords,
                                      std::vector<Vertex> &vertices,
                                      std::vector<GLuint> &indices) {
    Vertex vertex;
    vertex.position = positions[vertexIndex];
    if(normals.size() > 0){
        vertex.normal = normals[normalIndex];
    }
    if(texCoords.size() > 0) {
        vertex.texCoords[0] = 1 - texCoords[texIndex][0];
        vertex.texCoords[1] = texCoords[texIndex][1];
    }
    GLuint index;
    bool match = getSimilarVertex(vertex, vertices, index);
    if(!match){
        index = vertices.size();
        vertices.push_back(vertex);
    }
    indices.push_back(index);
}

Shader* ResourceManager::load_shader(const char *vertexfile, const char *fragmentfile, const char *geometryfile) {
    std::string path = vertexfile;
    if(fragmentfile){
        path += fragmentfile;
    }
    if(geometryfile){
        path += geometryfile;
    }

    Shader* shader = checkShader(path);

    if(shader){
        return shader;
    }
    shader = new Shader(vertexfile, fragmentfile, geometryfile);
    shader->path = path;
    addShader(shader);
    return shader;
}

void ResourceManager::addTexture(Texture *texture) {
    textures_loaded.push_back(texture);
}

void ResourceManager::addMesh(Mesh *mesh) {
    meshes_loaded.push_back(mesh);
}

void ResourceManager::addShader(Shader *shader) {
    shaders_loaded.push_back(shader);
}

Texture *ResourceManager::checkTexture(std::string path) {
    Texture* texture  = nullptr;
    for (std::vector<Texture*>::iterator it = textures_loaded.begin(); it != textures_loaded.end(); it++){
        if(path == (*it)->path){
            std::cout << path << " Texture found in cache" << std::endl;
            texture = *it;
            break;
        }
    }
    return texture;
}

Mesh *ResourceManager::checkMesh(std::string path) {
    Mesh* mesh  = nullptr;
    for (std::vector<Mesh*>::iterator it = meshes_loaded.begin(); it != meshes_loaded.end(); it++){
        if(path == (*it)->path){
            std::cout << path << " Mesh found in cache" << std::endl;
            mesh = *it;
            break;
        }
    }
    return mesh;
}

Shader *ResourceManager::checkShader(std::string path) {
    Shader* shader  = nullptr;
    for (std::vector<Shader*>::iterator it = shaders_loaded.begin(); it != shaders_loaded.end(); it++){
        if(path == (*it)->path){
            std::cout << path << " Shader found in cache" << std::endl;
            shader = *it;
            break;
        }
    }
    return shader;
}

ResourceManager::~ResourceManager() {
    deleteRescource(meshes_loaded);
    deleteRescource(textures_loaded);
    deleteRescource(shaders_loaded);
    std::cout << "destroy ResourceManager: " << this << std::endl;
}

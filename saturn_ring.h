#ifndef SATURN_RING
#define SATURN_RING

#include <glm/glm.hpp>
#include <string.h>
#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "texture.h"

#define ToRadian(x) ((x) * M_PI / 180.0f)

GLuint VBO_r;
GLuint VAO_r;
GLuint EBO_r;
Texture* pTexture = NULL;
int triangles;

struct Textel {
    glm::vec3 pos;
//    glm::vec3 norm;
    glm::vec2 tex;

    Textel(glm::vec3 p, glm::vec2 t) {
        pos = p;
//        norm = glm::vec3(0);
        tex = t;
    }
};

//void CalculateNorms(std::vector<int>& pIndices, unsigned int IndexCount, std::vector<Textel>& pVertices, unsigned int VertexCount)
//{
//    for (unsigned int i = 0 ; i < IndexCount ; i += 3) {
//         unsigned int Index0 = pIndices.at(i);
//         unsigned int Index1 = pIndices.at(i + 1);
//         unsigned int Index2 = pIndices.at(i + 2);
//         glm::vec3 v1 = pVertices.at(Index1).pos - pVertices.at(Index0).pos;
//         glm::vec3 v2 = pVertices.at(Index2).pos - pVertices.at(Index0).pos;
//         glm::vec3 Normal = glm::cross(v2, v1);
//         Normal = glm::normalize(Normal);

//         pVertices.at(Index0).norm += Normal;
//         pVertices.at(Index1).norm += Normal;
//         pVertices.at(Index2).norm += Normal;
//     }

//     for (unsigned int i = 0 ; i < VertexCount ; i++) {
//             pVertices.at(i).norm = glm::normalize(pVertices.at(i).norm);
//     }
//}

static void vertexes_ring() {
    std::vector<Textel> vertices;
    float angle = 0;
    bool point = true;
    vertices.push_back(Textel(glm::vec3(0.0f, 0.0f, 0.0f),
                              glm::vec2(0.5f, 0.5f)));
    while(angle < 2*3.14159) {
//        float radians = glm::radians(angle);
//        float radians = ToRadian(angle);
        float radians = angle;
        vertices.push_back(Textel(glm::vec3(cos(radians), 0.0f, sin(radians)),
                                  glm::vec2(0.5f * (cos(radians) + 1.0f), 0.5f * (sin(radians) + 1.0f))));
        angle += 0.2;
    }

    std::vector<int> indexes;
    for(int i = 1; i < vertices.size() - 1; ++i) {
        indexes.push_back(0);
        indexes.push_back((i));
        indexes.push_back((i + 1));
    }
    indexes.push_back(0);
    indexes.push_back((vertices.size() - 1));
    indexes.push_back((1));
    triangles = (vertices.size() - 1) * 3;

//    CalculateNorms(indexes, triangles, vertices, vertices.size());

    glGenVertexArrays(1,  &VAO_r);
    glGenBuffers(1, &VBO_r);
    glGenBuffers(1, &EBO_r);

    glBindVertexArray(VAO_r);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_r);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_r);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Textel), &vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(int), &indexes[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Textel), 0);
    glEnableVertexAttribArray(0);

//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));
//    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Textel), (void*)(sizeof(glm::vec3)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // texture
    pTexture = new Texture("/home/annusha/Study/BasicLab/framework_10/resources/saturn_rings.png");
}

#endif // SATURN_RING


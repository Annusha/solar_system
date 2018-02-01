#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "shader.h"
#include "render.h"
//#include "model.h"
#include "resourcemanager.h"
#include "mesh.h"
#include "material.h"
#include "parametrs.h"
#include "saturn_ring.h"

float width = 1024;
float hight = 768;

extern Shader a_shader;
extern Shader sun_shader;
extern Shader ring_shader;
extern ResourceManager a_model;
std::vector<Mesh> meshes;
std::vector<Material> materiales;
//std::vector<std::string> mtlFiles;


using namespace std;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glEnable (GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutCreateWindow("suit");
//    glutSetCursor(GLUT_CURSOR_NONE);

    InitializeGlutCallbacks();

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
      fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
      return 1;
    }
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, hight);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    init_move();


    a_shader = *(new Shader("/home/annusha/Study/BasicLab/sheet10/suit/vertex.vsh",
                            "/home/annusha/Study/BasicLab/sheet10/suit/fragment.fsh"));

//    ring_shader = *(new Shader("/home/annusha/Study/BasicLab/sheet10/suit/vertex.vsh",
//                            "/home/annusha/Study/BasicLab/sheet10/suit/fragment_ring.fsh"));

    sun_shader = *(new Shader("/home/annusha/Study/BasicLab/sheet10/suit/sun.vsh",
                              "/home/annusha/Study/BasicLab/sheet10/suit/sun.fsh"));

//    a_model = *(new Model("/home/annusha/Study/BasicLab/sheet10/suit/nanosuit/nanosuit.obj"));
//    a_model = *(new Model("/home/annusha/Study/BasicLab/framework_10/resources/planet.obj"));
    Mesh mesh;
    Material material;
    std::string mtlFile;
    mtlFile = "sun.mtl";
    a_model.load("/home/annusha/Study/BasicLab/framework_10/resources/planet.obj", &mesh, &material, mtlFile);
    meshes.push_back(mesh);
    materiales.push_back(material);

    mtlFile = "earth.mtl";
    a_model.load("/home/annusha/Study/BasicLab/framework_10/resources/planet.obj", &mesh, &material, mtlFile);
    meshes.push_back(mesh);
    materiales.push_back(material);

    mtlFile = "moon.mtl";
    a_model.load("/home/annusha/Study/BasicLab/framework_10/resources/planet.obj", &mesh, &material, mtlFile);
    meshes.push_back(mesh);
    materiales.push_back(material);

    mtlFile = "mars.mtl";
    a_model.load("/home/annusha/Study/BasicLab/framework_10/resources/planet.obj", &mesh, &material, mtlFile);
    meshes.push_back(mesh);
    materiales.push_back(material);


    mtlFile = "saturn.mtl";
    a_model.load("/home/annusha/Study/BasicLab/framework_10/resources/planet.obj", &mesh, &material, mtlFile);
    meshes.push_back(mesh);
    materiales.push_back(material);

    vertexes_ring();

    glutMainLoop();

    return 0;
}

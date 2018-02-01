#ifndef RENDER
#define RENDER

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string.h>

#include "shader.h"
#include "camera.h"
#include "transformation.h"
//#include "model.h"
#include "resourcemanager.h"
#include "mesh.h"
#include "material.h"
#include "parametrs.h"

extern GLuint VAO;
extern GLuint lightVAO;
Shader a_shader;
Shader sun_shader;
ResourceManager a_model;
extern std::vector<Mesh> meshes;
extern std::vector<Material> materiales;

extern GLuint VAO_r;
extern Texture* pTexture;
extern int triangles;


Camera camera(glm::vec3(0.0, 0.0, 20.0), glm::vec3(0.0, 0.0, 0.0));


static void RenderScene() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.setWidthHeight(width, hight);
    camera.updateTime();

    a_shader.use();
    a_shader.setMat4("camera", camera.getCameraMatrix());
    a_shader.setVec3("light.position", glm::vec3(0));
    a_shader.setVec3("light.diffuse", materiales.at(0).diffuse);
    a_shader.setVec3("light.ambient", materiales.at(0).ambient);
    a_shader.setVec3("light.specular", materiales.at(0).specular);
    // others
    for(int i = 1; i < meshes.size(); ++i) {
        Pipeline trans;
        trans.Translate(moves.at(i)->init_pos);
        trans.Rotate(moves.at(i)->rotate);
        trans.Scale(scales[i]);

        a_shader.setMat4("transform", trans.GetTrans());

        a_model.draw(a_shader, meshes.at(i), materiales.at(i));

    }

    //sun
    sun_shader.use();
    sun_shader.setMat4("camera", camera.getCameraMatrix());

    Pipeline trans_sun;
    trans_sun.Translate(glm::vec3(0));
    trans_sun.Scale(scales[0]);

    sun_shader.setMat4("transform", trans_sun.GetTrans());

    a_model.draw(sun_shader, meshes.at(0), materiales.at(0));

    // saturn ring
    glBindVertexArray(VAO_r);
    Pipeline trans_ring;
    trans_ring.Translate(moves.at(meshes.size() - 1)->init_pos);
    trans_ring.Scale(glm::vec3(2));
    sun_shader.setMat4("transform", trans_ring.GetTrans());
    pTexture->use(sun_shader.ID, string("material.texture_diffuse"), 0);

    glDrawElements(GL_TRIANGLES, triangles, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    for(int i = 1; i < meshes.size(); ++i) {
        moves.at(i)->update();
    }


    glutSwapBuffers();
}

static void SpecialKeyboardCB(unsigned char Key, int x, int y){
    camera.movement(Key);
}

static void PassiveMouseCB(int x, int y)
{
     camera.onMouse(x, y);
}

static void InitializeGlutCallbacks() {
    glutDisplayFunc(RenderScene);
    glutIdleFunc(RenderScene);
    glutKeyboardFunc(SpecialKeyboardCB);
    glutPassiveMotionFunc(PassiveMouseCB);
}

#endif // RENDER


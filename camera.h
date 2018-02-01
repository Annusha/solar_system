#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>

#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / M_PI)

class Camera {
private:
    // view frustum specifications
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 target;
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 result;
    float fieldOfView, aspectRatio, nearClippingPlane, farClippingPlane;

    float radius = 20.0f;
    bool firstMouse = true;

    // view and projection matrices resulting from the view frustum
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    // mouse positions and window dimensions for trackball functionality
    glm::vec2 last, cur;
    int screenWidth, screenHeight;
    float mouseSensitivity = 0.1;
    float pitch, yaw;

    // animation (for a scene-independent movement speed)
    float deltaTime, lastFrame;
    float speed = 0.1f;

    // calculate 3D direciton from 2D window coordinates
    glm::vec3 getArcBallVector(int x, int y);

public:
    Camera(glm::vec3 pos, glm::vec3 target);
    ~Camera();

    glm::vec3 position;

    // mouse control
    void onMouse(int x, int y);

    // to be enabled when mouse is dragged inside window
    bool arcBallEnabled = false;

    // zoom
    void zoom(float offset);

    // movement speed
    void setSpeed(float speed);

    // w-a-s-d-movement
    bool movement(int Key);

    // arcball-functions
    void arcballUpdate(glm::mat4& modelMatrix);
    void setCurXY(int xpos, int ypos);
    void setLastXY(int xpos, int ypos);

    //general functions
    void setWidthHeight(int width, int height);
    void updateTime();
    void resetCamera();

    // functions for computing view and projection matrices
    void setTarget(glm::vec3 target);
    glm::mat4& getViewMatrix();
    glm::mat4& getProjectionMatrix();
    glm::mat4& getCameraMatrix();
};


#endif // CAMERA


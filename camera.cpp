
#include "camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 target) {
    this->position = position;
    this->target = target;
    front = glm::normalize(target - position);

    right = glm::normalize(glm::cross(worldUp, front));
    up = glm::normalize(glm::cross(front, right));

    deltaTime = 0.0f;
    fieldOfView = 45.0f;
    nearClippingPlane = 0.1f;
    farClippingPlane = 100.0f;

    pitch = 0;
    yaw = 0;
}

Camera::~Camera()
{

}

void Camera::onMouse(int x, int y)
{

    if(firstMouse)
        {
//            last.x = screenWidth / 2;
//            last.y = screenHeight / 2;
            last.x = x;
            last.y = y;
            glutWarpPointer(last.y, last.x);
            firstMouse = false;
        }

    glm::vec2 offset;
    offset.x = x - last.x;
    offset.y = last.y - y;

    last = glm::vec2((float)x, (float)y);

    offset *= mouseSensitivity;

    yaw += offset.x;
    pitch += offset.y;

    // limitations
    if(pitch > 89.0f)
      pitch =  89.0f;
    if(pitch < -89.0f)
      pitch = -89.0f;

    glm::vec3 camFront;
    camFront.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    camFront.y = sin(glm::radians(pitch));
    camFront.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    front = glm::normalize(camFront);
}

bool Camera::movement(int Key)
{
    bool Ret = false;
    switch (Key) {
    case 'q': {
        exit(0);
    } break;
    case 'w':{
        position += (front * speed);
        Ret = true;
    } break;
    case 's':{
        position -= (front * speed);
        Ret = true;
    } break;
    case 'a':{
        position += (glm::normalize(glm::cross(up, front)) * speed);
        Ret = true;
    } break;
    case 'd':{
        position += glm::normalize(glm::cross(front, up)) * speed;
        Ret = true;
    } break;
    }
    return Ret;
}

void Camera::setWidthHeight(int width, int height)
{
    screenWidth = width;
    screenHeight = height;

//    last.x = screenWidth / 2;
//    last.y = screenHeight / 2;

    aspectRatio = screenWidth * 1.0f / screenHeight;
}

void Camera::updateTime()
{
    deltaTime += 0.01;
    resetCamera();
}

void Camera::resetCamera()
{
//    position.x = sin(deltaTime) * radius;
//    position.z = cos(deltaTime) * radius;

    //    front = glm::normalize(position - target);
}


void Camera::setTarget(glm::vec3 target)
{
    this->target = target;
}

glm::mat4 &Camera::getViewMatrix()
{
//    viewMatrix = glm::lookAt(position, target, worldUp);
    viewMatrix = glm::lookAt(position, position + front, worldUp);

}

glm::mat4 &Camera::getProjectionMatrix()
{
    projectionMatrix = glm::perspective(fieldOfView, aspectRatio, nearClippingPlane, farClippingPlane);

}

glm::mat4 &Camera::getCameraMatrix()
{

    getProjectionMatrix();
    getViewMatrix();

    result = projectionMatrix * viewMatrix;
//    result =  * result;

    return result;
}

#ifndef TEXTURE
#define TEXTURE


#include <iostream>
#include <string>

#include <GL/glew.h>
#include <opencv2/opencv.hpp>

class Texture {
public:
    GLuint id; //texture id for gpu

    int width;  //width of image
    int height; //height of image

    std::string type; // diffuse, specular, ambient, bumpmap, opacity used as identifier in shader
    std::string path;   //used to identify the texture in rescource manager

    Texture(std::string path);
    Texture(cv::Mat image, int width, int height, std::string type, std::string path);
    ~Texture();

    void toGPU(cv::Mat image);

    // activate texture in shader, arguments are: shader program id, sampler uniform name, texture index
    void use(GLuint shaderProgramID, std::string uniformname, int i=0);
};

#endif // TEXTURE


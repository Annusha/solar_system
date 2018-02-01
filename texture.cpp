#include "texture.h"

Texture::Texture(std::string path) {
    int channels_in_file;
    cv::Mat image = cv::imread(path, CV_LOAD_IMAGE_UNCHANGED);
    width = image.cols;
    height = image.rows;
    channels_in_file = image.channels();
    if(channels_in_file == 4) {
        cv::cvtColor(image, image, CV_BGRA2RGBA);
    } else {
        cv::cvtColor(image, image, CV_BGR2RGB);
    }

    cv::flip(image, image, 0);

    if (!image.data) {
        throw std::runtime_error(std::string("loading image ") + path + std::string(" failed."));
    }
    if (channels_in_file != 3 && channels_in_file != 4) {
        throw std::runtime_error("number of channels in file is neither 3 nor 4. only RGB and RGBA images are supported.");
    }
    this->path = path;
    this->type = "default";
    this->toGPU(image);
}

Texture::Texture(cv::Mat image, int width, int height, std::string type, std::string path) {
    this->width = width;
    this->height = height;
    this->path = path;
    this->type = type;
    this->toGPU(image);
}

Texture::~Texture() {
    std::cout << "destroy Texture: " << this << std::endl;
}

void Texture::toGPU(cv::Mat image) {

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    int channels = image.channels();
    GLenum format;
    if (channels == 1)
        format = GL_RED;
    else if (channels == 3)
        format = GL_RGB;
    else if (channels == 4)
        format = GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image.ptr());

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::use(GLuint shaderProgramID, std::string uniformname, int i) {
    glUniform1i(glGetUniformLocation(shaderProgramID, uniformname.c_str()), i);
    glBindTexture(GL_TEXTURE_2D, id);
}

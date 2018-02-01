#include "transformation.h"

void Pipeline::InitScaleTransform(glm::mat4 &m) const {
    m = glm::scale(m, m_scale);
}

void Pipeline::InitRotateTransform(glm::mat4 &m) const {
    // x rotation
    m = glm::rotate(m, m_rotateInfo.x, glm::vec3(1.0, 0.0, 0.0));
    // y rotation
    m = glm::rotate(m, m_rotateInfo.y, glm::vec3(0.0, 1.0, 0.0));
    // z rotation
    m = glm::rotate(m, m_rotateInfo.z, glm::vec3(0.0, 0.0, 1.0));
}

void Pipeline::InitTranslationTransform(glm::mat4 &m) const {
    m = glm::translate(m, m_shift);
}


glm::mat4& Pipeline::GetTrans() {
    glm::mat4 scale, rotate, translate;

    InitScaleTransform(scale);
    InitRotateTransform(rotate);
    InitTranslationTransform(translate);


    m_transformation = translate * rotate * scale;
    return m_transformation;
}

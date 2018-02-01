#ifndef TRANSFORMATION
#define TRANSFORMATION

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

extern float width;
extern float hight;

#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / M_PI)

class Pipeline
{
    public:
        Pipeline() {
            m_scale = glm::vec3(1.0, 1.0, 1.0);
            m_shift = glm::vec3(0.0, 0.0, 0.0);
            m_rotateInfo = glm::vec3(0.0, 0.0, 0.0);
        }

        void Scale(float ScaleX, float ScaleY, float ScaleZ) {
            m_scale = glm::vec3(ScaleX, ScaleY, ScaleZ);
        }
        void Scale(glm::vec3 v) {
            m_scale = v;
        }

        void Translate(float x, float y, float z) {
            m_shift = glm::vec3(x, y, z);
        }
        void Translate(glm::vec3 v) {
            m_shift = v;
        }

        void Rotate(float RotateX, float RotateY, float RotateZ) {
            m_rotateInfo = glm::vec3(RotateX, RotateY, RotateZ);
        }
        void Rotate(glm::vec3 v) {
            m_rotateInfo = v;
        }

        glm::mat4& GetTrans();
    private:
        void InitScaleTransform(glm::mat4 &m) const;
        void InitRotateTransform(glm::mat4 &m) const;
        void InitTranslationTransform(glm::mat4 &m) const;

        glm::vec3 m_scale;
        glm::vec3 m_shift;
        glm::vec3 m_rotateInfo;

        glm::mat4 m_transformation;
};


#endif // TRANSFORMATION


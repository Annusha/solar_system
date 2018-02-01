#version 400

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 transform;
uniform mat4 camera;

void main()
{
    TexCoords = aTexCoords;

    gl_Position = camera * transform * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
}

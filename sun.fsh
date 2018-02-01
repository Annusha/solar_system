#version 400
out vec4 FragColor;
in vec2 TexCoords;

struct Material {
    sampler2D texture_diffuse;
};

uniform Material material;

void main()
{
//    FragColor = vec4(1.0, 1.0, 0.0, 1.0);
//    vec4 texColor = texture2D(material.texture_diffuse, TexCoords);
//        if(texColor.a < 0.1)
//            discard;
//        FragColor = texColor;
    FragColor = texture2D(material.texture_diffuse, TexCoords);
}

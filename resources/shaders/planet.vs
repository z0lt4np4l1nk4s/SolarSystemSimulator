#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 matrix;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0)); // Transform position to world space
    Normal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = matrix * model * vec4(aPos, 1.0f);
    TexCoord = aTexCoord;
}

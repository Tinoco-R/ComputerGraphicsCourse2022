#version 330 core
// First three float values = position of vertex
layout (location = 0) in vec3 position;
// Second three float values = normal vector
layout (location = 1) in vec3 normal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// References:
// gl_Position calculation and Normal calculation both seen in 
// https://learnopengl.com/Lighting/Basic-Lighting 
void main()
{
    // TODO: Your code here
    // Translates the position of the input to the 2D screen space
    // by following the Graphics Transformation Pipeline
    FragPos = vec3(model * vec4(position, 1.0f));
    gl_Position = projection * view * vec4(FragPos, 1.0);

    // Calculates transformed Normal vector (in World Space) from the normal
    // of the object in local coordinate space
    Normal = mat3(transpose(inverse(model))) * normal;
} 

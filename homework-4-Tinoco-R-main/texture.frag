#version 330 core
out vec4 color;

in vec2 UV;
uniform sampler2D myTextureSampler;

void main()
{
    // TODO: pub with your code...
    // Samples color of myTextureSampler according to UV texture coordinates
    color = texture(myTextureSampler, UV);
}

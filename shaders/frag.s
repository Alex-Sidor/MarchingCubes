#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 normalVector;

uniform sampler2D ourTexture;

void main()
{
    float diffuse = max(dot(normalVector, vec3(0,1,0)), 0.0);
    FragColor = texture(ourTexture, TexCoord) * (diffuse +  + 0.3);   
}

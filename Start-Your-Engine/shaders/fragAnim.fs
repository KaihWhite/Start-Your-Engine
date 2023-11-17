#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;

uniform int currentFrame;
uniform int totalFrames;

void main()
{    
    float frameWidth = 1.0 / float(totalFrames);
    float offsetX = frameWidth * float(currentFrame);

    vec2 frameUV = vec2(frameWidth * TexCoords.x + offsetX, TexCoords.y);

    color = vec4(spriteColor, 1.0) * texture(image, frameUV);
}  
#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D textTexture;
uniform vec3 textColor;

void main()
{
    float alpha = texture(textTexture, TexCoord).r;
    
    // Use smoothstep for better anti-aliasing (smoother edges)
    alpha = smoothstep(0.3, 0.7, alpha);

    FragColor = vec4(textColor, alpha);
}

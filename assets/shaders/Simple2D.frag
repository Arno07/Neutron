#version 330 core
out vec4 FragColor;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform bool u_UseTexture;

in vec2 v_TexCoord;

void main() {
    if (u_UseTexture)
    FragColor = texture(u_Texture, v_TexCoord);
    else
    FragColor = u_Color;
}
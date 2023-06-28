#version 440

in vec4 colorPass;
in vec2 texCoordsPass;
out vec4 colorOut;

uniform sampler2D un_texture;
void main(void)
{
  // colorOut = colorPass;
  // colorOut = un_color;
  // colorOut = vec4(texCoordsPass, 0, 1);
  colorOut = texture(un_texture, texCoordsPass);
}
#version 440

in vec4 colorPass;
in vec2 texCoordsPass;
in float lightIntensityPass;

out vec4 colorOut;

uniform sampler2D un_texture;
void main(void)
{
  colorOut = colorPass;
  // colorOut = vec4(texture(un_texture, texCoordsPass).xyz * lightIntensityPass, 1);
}
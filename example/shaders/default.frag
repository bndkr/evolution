#version 440

in vec4 colorPass;
in vec2 texCoordsPass;
in vec3 normalPass;

out vec4 colorOut;

uniform sampler2D un_texture;
void main(void)
{
  // colorOut = colorPass;
  // colorOut = texture(un_texture, texCoordsPass);
  colorOut = vec4(normalPass.xyz, 1);
}
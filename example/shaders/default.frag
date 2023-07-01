#version 440

in vec4 colorPass;
in vec2 texCoordsPass;
in vec3 normalPass;
in vec3 vertexPosPass;

uniform vec3 un_lightPos;


out vec4 colorOut;

uniform sampler2D un_texture;
void main(void)
{
  // colorOut = colorPass;
  vec3 lightDir = normalize(un_lightPos - vertexPosPass);
  float diffuseIntensity = max(dot(normalize(normalPass), lightDir), 0);

  colorOut = vec4(texture(un_texture, texCoordsPass).xyz * diffuseIntensity, 1);
}
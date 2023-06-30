#version 440

layout(location=0) in vec3 positionIn;
layout(location=1) in vec4 colorIn;
layout(location=2) in vec2 texCoordsIn;
layout(location=3) in vec3 normalIn;

uniform mat4 un_modelMatrix;
uniform mat4 un_eyeMatrix;
uniform mat4 un_projMatrix;
uniform vec3 un_lightPos;


out vec4 colorPass;
out vec2 texCoordsPass;
out float lightIntensityPass;

void main(void)
{
  gl_Position = (un_projMatrix * un_eyeMatrix * un_modelMatrix) * vec4(positionIn.xyz, 1);

  vec3 worldLocation = ((un_modelMatrix) * vec4(positionIn.xyz, 1)).xyz;
  vec3 lightVec = normalize(un_lightPos - worldLocation);
  lightIntensityPass = max(dot(lightVec, normalize(normalIn)), 0.0);
  colorPass = vec4(worldLocation.xyz, 1);
  texCoordsPass = texCoordsIn;
}
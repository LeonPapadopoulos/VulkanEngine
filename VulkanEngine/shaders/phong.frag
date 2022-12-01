#version 450

layout(binding = 2) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

// SOURCE: https://www.mathematik.uni-marburg.de/~thormae/lectures/graphics1/code/WebGLShaderLightMat/ShaderLightMat.html
// TODO: Remove Hardcoded Light & ViewDirection
const vec3 lightDirection = vec3(-10, 10, -10);
const vec3 viewDirection = vec3(10, 10, 0);

const vec4 ambientColor = vec4(0.01, 0.0, 0.0, 1.0);
const vec4 diffuseColor = vec4(0.25, 0.0, 0.0, 1.0);
const vec4 specularColor = vec4(1.0, 1.0, 1.0, 1.0);
const float shininess = 20.0;
const vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
const float irradiPerp = 1.0;

vec3 phongBRDF(vec3 lightDir, vec3 viewDir, vec3 normal, vec3 phongDiffuseCol, vec3 phongSpecularCol, float phongShininess) {
  vec3 color = phongDiffuseCol;
  vec3 reflectDir = reflect(-lightDir, normal);
  float specDot = max(dot(reflectDir, viewDir), 0.0);
  color += pow(specDot, phongShininess) * phongSpecularCol;
  return color;
}

void main() {
  vec3 lightDir = normalize(-lightDirection);
  //vec3 viewDir = normalize(-vertPos);
  //vec3 n = normalize(fn);
  vec3 normal = vec3(1,0,0);

  vec3 radiance = ambientColor.rgb;
  
  float irradiance = max(dot(lightDir, normal), 0.0) * irradiPerp;
  if(irradiance > 0.0) {
    vec3 brdf = phongBRDF(lightDir, viewDirection, normal, fragColor.rgb, specularColor.rgb, shininess);
    radiance += brdf * irradiance * lightColor.rgb;
  }

  //radiance = pow(radiance, vec3(1.0 / 2.2) ); // gamma correction
  outColor.rgb = radiance / 30000;
  outColor.a = 1.0;
}
#version 450

layout(binding = 0) uniform UniformBufferGlobal {
    mat4 view;
    mat4 proj;
    mat4 viewProj;
} uboGlobal;

layout(binding = 1) uniform UniformBufferPerModel {
    mat4 model;
} uboModel;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;

void main() {
    gl_Position = uboGlobal.viewProj * uboModel.model * vec4(inPosition, 1.0);
    fragColor = inColor;
    fragTexCoord = inTexCoord;
}
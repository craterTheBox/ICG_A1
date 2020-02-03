#version 420

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inUV;
layout(location = 2) in vec3 inNormal;

layout(location = 0) out vec3 outWorldPosition;
layout(location = 1) out vec2 outUV;
layout(location = 2) out vec3 outNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat3 normalMatrix;

void main() {
	outWorldPosition = (model * vec4(inPosition, 1.0)).xyz;
	outUV = inUV;
	outNormal = normalMatrix * inNormal;
	
	gl_Position = projection * view * model * vec4(inPosition, 1.0);
}
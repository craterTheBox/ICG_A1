#version 420
out vec4 fColour;

uniform vec3 colour;

void main(){
    fColour = vec4(colour,1.0f);
}
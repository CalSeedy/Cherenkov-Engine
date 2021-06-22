#version 330 core

layout(location = 0) out vec4 c;

uniform vec4 colour;

void main(){
	c = colour;
}
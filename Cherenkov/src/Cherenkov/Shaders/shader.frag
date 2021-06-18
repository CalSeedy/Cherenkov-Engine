#version 330 core

layout(location = 0) out vec4 color;
in vec3 posOut;

void main(){
	color = vec4((posOut*0.5) + 0.5, 1.0);
}
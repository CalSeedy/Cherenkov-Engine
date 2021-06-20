#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Pos;

void main(){
	color = vec4((v_Pos*0.5) + 0.5, 1.0);
}
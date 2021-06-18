#version 330 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec4 a_Col;


out vec3 v_Pos;
out vec4 v_Col;


void main(){
	gl_Position = vec4(a_Pos, 1.0);
	v_Pos = a_Pos;
	v_Col = a_Col;
}
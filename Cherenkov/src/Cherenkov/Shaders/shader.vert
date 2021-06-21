#version 330 core

layout(location = 0) in vec3 a_Pos;

uniform mat4 viewProjection;
uniform mat4 transform;

out vec3 v_Pos;


void main(){
	v_Pos = a_Pos;
	gl_Position = viewProjection * transform * vec4(a_Pos, 1.0);
}
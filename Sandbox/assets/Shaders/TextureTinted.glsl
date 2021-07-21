#type vertex
#version 330 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 viewProjection;
uniform mat4 transform;

out vec2 texCoord;

void main(){
	texCoord = a_TexCoord;
	gl_Position = viewProjection * transform * vec4(a_Pos, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 c;

uniform vec4 colour;
uniform sampler2D tex;

in vec2 texCoord;

void main(){
	
	c = texture(tex, texCoord) * colour;

}
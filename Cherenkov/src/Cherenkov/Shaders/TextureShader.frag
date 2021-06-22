#version 330 core

layout(location = 0) out vec4 c;

uniform vec4 colour;
uniform sampler2D tex;

in vec2 texCoord;

void main(){
	
	c = texture(tex, texCoord);

}
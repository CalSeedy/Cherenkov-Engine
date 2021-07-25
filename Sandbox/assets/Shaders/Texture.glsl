#type vertex
#version 330 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec4 in_Colour;
layout(location = 2) in vec2 in_TextureCoord;

uniform mat4 viewProjection;

out vec2 out_TextureCoord;
out vec4 out_Colour;

void main(){
	out_TextureCoord = in_TextureCoord;
	out_Colour = in_Colour;
	gl_Position = viewProjection * vec4(in_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 final_Colour;

in vec4 out_Colour;
in vec2 out_TextureCoord;

uniform vec4 colour;
uniform sampler2D tex;
uniform float tilingFactor;

void main(){
	
	final_Colour = out_Colour; //texture(tex, texCoord * tilingFactor) * colour;

}
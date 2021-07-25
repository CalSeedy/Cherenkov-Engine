#type vertex
#version 330 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec4 in_Colour;
layout(location = 2) in vec2 in_TextureCoord;
layout(location = 3) in float in_TextureIdx;
layout(location = 4) in float in_TilingFactor;

uniform mat4 viewProjection;

out vec4 out_Colour;
out vec2 out_TextureCoord;
out float out_TextureIdx;
out float out_TilingFactor;

void main(){
	out_Colour = in_Colour;
	out_TextureCoord = in_TextureCoord;
	out_TextureIdx = in_TextureIdx;
	out_TilingFactor = in_TilingFactor;
	gl_Position = viewProjection * vec4(in_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 final_Colour;

in vec4 out_Colour;
in vec2 out_TextureCoord;
in float out_TextureIdx;
in float out_TilingFactor;

uniform sampler2D textures[32];

void main(){
	
	final_Colour = texture(textures[int(out_TextureIdx)], out_TextureCoord * out_TilingFactor) * out_Colour;

}
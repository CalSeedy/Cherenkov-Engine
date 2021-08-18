#type vertex
#version 450

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec4 in_Colour;
layout(location = 2) in vec2 in_TextureCoord;
layout(location = 3) in float in_TextureIdx;
layout(location = 4) in float in_TilingFactor;

uniform mat4 viewProjection;

out vec4 out_Colour;
out vec2 out_TextureCoord;
out flat float out_TextureIdx;
out float out_TilingFactor;

void main(){
	out_Colour = in_Colour;
	out_TextureCoord = in_TextureCoord;
	out_TextureIdx = in_TextureIdx;
	out_TilingFactor = in_TilingFactor;
	gl_Position = viewProjection * vec4(in_Position, 1.0);
}

#type fragment
#version 450

layout(location = 0) out vec4 final_Colour;
layout(location = 1) out int final_Colour2;

in vec4 out_Colour;
in vec2 out_TextureCoord;
in flat float out_TextureIdx;
in float out_TilingFactor;

uniform sampler2D textures[32];

void main(){
	vec4 texColour = out_Colour;
	switch(int(out_TextureIdx)){
	case 0: texColour *= texture(textures[0], out_TextureCoord * out_TilingFactor); break;
	case 1: texColour *= texture(textures[1], out_TextureCoord * out_TilingFactor); break;
	case 2: texColour *= texture(textures[2], out_TextureCoord * out_TilingFactor); break;
	case 3: texColour *= texture(textures[3], out_TextureCoord * out_TilingFactor); break;
	case 4: texColour *= texture(textures[4], out_TextureCoord * out_TilingFactor); break;
	case 5: texColour *= texture(textures[5], out_TextureCoord * out_TilingFactor); break;
	case 6: texColour *= texture(textures[6], out_TextureCoord * out_TilingFactor); break;
	case 7: texColour *= texture(textures[7], out_TextureCoord * out_TilingFactor); break;
	case 8: texColour *= texture(textures[8], out_TextureCoord * out_TilingFactor); break;
	case 9: texColour *= texture(textures[9], out_TextureCoord * out_TilingFactor); break;
	case 10: texColour *= texture(textures[10], out_TextureCoord * out_TilingFactor); break;
	case 11: texColour *= texture(textures[11], out_TextureCoord * out_TilingFactor); break;
	case 12: texColour *= texture(textures[12], out_TextureCoord * out_TilingFactor); break;
	case 13: texColour *= texture(textures[13], out_TextureCoord * out_TilingFactor); break;
	case 14: texColour *= texture(textures[14], out_TextureCoord * out_TilingFactor); break;
	case 15: texColour *= texture(textures[15], out_TextureCoord * out_TilingFactor); break;
	case 16: texColour *= texture(textures[16], out_TextureCoord * out_TilingFactor); break;
	case 17: texColour *= texture(textures[17], out_TextureCoord * out_TilingFactor); break;
	case 18: texColour *= texture(textures[18], out_TextureCoord * out_TilingFactor); break;
	case 19: texColour *= texture(textures[19], out_TextureCoord * out_TilingFactor); break;
	case 20: texColour *= texture(textures[20], out_TextureCoord * out_TilingFactor); break;
	case 21: texColour *= texture(textures[21], out_TextureCoord * out_TilingFactor); break;
	case 22: texColour *= texture(textures[22], out_TextureCoord * out_TilingFactor); break;
	case 23: texColour *= texture(textures[23], out_TextureCoord * out_TilingFactor); break;
	case 24: texColour *= texture(textures[24], out_TextureCoord * out_TilingFactor); break;
	case 25: texColour *= texture(textures[25], out_TextureCoord * out_TilingFactor); break;
	case 26: texColour *= texture(textures[26], out_TextureCoord * out_TilingFactor); break;
	case 27: texColour *= texture(textures[27], out_TextureCoord * out_TilingFactor); break;
	case 28: texColour *= texture(textures[28], out_TextureCoord * out_TilingFactor); break;
	case 29: texColour *= texture(textures[29], out_TextureCoord * out_TilingFactor); break;
	case 30: texColour *= texture(textures[30], out_TextureCoord * out_TilingFactor); break;
	case 31: texColour *= texture(textures[31], out_TextureCoord * out_TilingFactor); break;
	}

	final_Colour = texColour;
	final_Colour2 = 50;
}

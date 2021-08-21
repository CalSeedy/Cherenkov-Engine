#type vertex
#version 450 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec4 in_Colour;
layout(location = 2) in vec2 in_TextureCoord;
layout(location = 3) in float in_TilingFactor;
layout(location = 4) in float in_TextureIdx;
layout(location = 5) in int in_EntityID;

layout(std140, binding = 0) uniform Camera {
	mat4 viewProjection;
};

struct VertexOutput {
	vec4 Colour;
	vec2 TextureCoord;
	float TilingFactor;
};

layout (location = 0) out VertexOutput Output;
layout (location = 3) out flat float out_TextureIdx;
layout (location = 4) out flat int out_EntityID;

void main(){
	Output.Colour = in_Colour;
	Output.TextureCoord = in_TextureCoord;
	Output.TilingFactor = in_TilingFactor;
	out_TextureIdx = in_TextureIdx;
	out_EntityID = in_EntityID;
	gl_Position = viewProjection * vec4(in_Position, 1.0);
}

#type fragment
#version 450 core

layout(location = 0) out vec4 final_Colour;
layout(location = 1) out int final_Colour2;

struct VertexOutput {
	vec4 Colour;
	vec2 TextureCoord;
	float TilingFactor;
};

layout (location = 0) in VertexOutput Input;
layout (location = 3) in flat float out_TextureIdx;
layout (location = 4) in flat int out_EntityID;

layout (binding = 0) uniform sampler2D textures[32];

void main(){
	vec4 texColour = Input.Colour;
	switch(int(out_TextureIdx)){
	case 0: texColour *= texture(textures[0], Input.TextureCoord * Input.TilingFactor); break;
	case 1: texColour *= texture(textures[1], Input.TextureCoord * Input.TilingFactor); break;
	case 2: texColour *= texture(textures[2], Input.TextureCoord * Input.TilingFactor); break;
	case 3: texColour *= texture(textures[3], Input.TextureCoord * Input.TilingFactor); break;
	case 4: texColour *= texture(textures[4], Input.TextureCoord * Input.TilingFactor); break;
	case 5: texColour *= texture(textures[5], Input.TextureCoord * Input.TilingFactor); break;
	case 6: texColour *= texture(textures[6], Input.TextureCoord * Input.TilingFactor); break;
	case 7: texColour *= texture(textures[7], Input.TextureCoord * Input.TilingFactor); break;
	case 8: texColour *= texture(textures[8], Input.TextureCoord * Input.TilingFactor); break;
	case 9: texColour *= texture(textures[9], Input.TextureCoord * Input.TilingFactor); break;
	case 10: texColour *= texture(textures[10], Input.TextureCoord * Input.TilingFactor); break;
	case 11: texColour *= texture(textures[11], Input.TextureCoord * Input.TilingFactor); break;
	case 12: texColour *= texture(textures[12], Input.TextureCoord * Input.TilingFactor); break;
	case 13: texColour *= texture(textures[13], Input.TextureCoord * Input.TilingFactor); break;
	case 14: texColour *= texture(textures[14], Input.TextureCoord * Input.TilingFactor); break;
	case 15: texColour *= texture(textures[15], Input.TextureCoord * Input.TilingFactor); break;
	case 16: texColour *= texture(textures[16], Input.TextureCoord * Input.TilingFactor); break;
	case 17: texColour *= texture(textures[17], Input.TextureCoord * Input.TilingFactor); break;
	case 18: texColour *= texture(textures[18], Input.TextureCoord * Input.TilingFactor); break;
	case 19: texColour *= texture(textures[19], Input.TextureCoord * Input.TilingFactor); break;
	case 20: texColour *= texture(textures[20], Input.TextureCoord * Input.TilingFactor); break;
	case 21: texColour *= texture(textures[21], Input.TextureCoord * Input.TilingFactor); break;
	case 22: texColour *= texture(textures[22], Input.TextureCoord * Input.TilingFactor); break;
	case 23: texColour *= texture(textures[23], Input.TextureCoord * Input.TilingFactor); break;
	case 24: texColour *= texture(textures[24], Input.TextureCoord * Input.TilingFactor); break;
	case 25: texColour *= texture(textures[25], Input.TextureCoord * Input.TilingFactor); break;
	case 26: texColour *= texture(textures[26], Input.TextureCoord * Input.TilingFactor); break;
	case 27: texColour *= texture(textures[27], Input.TextureCoord * Input.TilingFactor); break;
	case 28: texColour *= texture(textures[28], Input.TextureCoord * Input.TilingFactor); break;
	case 29: texColour *= texture(textures[29], Input.TextureCoord * Input.TilingFactor); break;
	case 30: texColour *= texture(textures[30], Input.TextureCoord * Input.TilingFactor); break;
	case 31: texColour *= texture(textures[31], Input.TextureCoord * Input.TilingFactor); break;
	}

	final_Colour = texColour;
	final_Colour2 = out_EntityID;
}

#version 420 core

in vec4 fs_norm;
in vec4 fs_texcoord;

layout (location = 0) out vec4 render_color;

layout (std140, binding = 0) uniform ConstantBuffer
{
	mat4 transformMat;
	int mode;
};

uniform sampler2D texture0;
uniform sampler2D texture1;

vec4 SampleTex(sampler2D textureX, vec2 __texcoord)
{
	__texcoord.y = 1.0 - __texcoord.y;
	return texture(textureX, __texcoord);
}

void main()
{
	if (mode == 1)
	{
		float scale = max(dot(normalize(fs_norm), normalize(vec4(0.0, 1.0, -1.0, 0.0))), 0.0) * 0.5;
		scale += 0.5;
		render_color = (SampleTex(texture0, fs_texcoord.xy) + SampleTex(texture1, fs_texcoord.xy)) * 0.5;
		//render_color = SampleTex(texture0, fs_texcoord.xy);
		render_color = vec4(render_color.xyz * scale, render_color.w);
	}
	else render_color = vec4(fs_texcoord.xyz, fs_texcoord.w);
}
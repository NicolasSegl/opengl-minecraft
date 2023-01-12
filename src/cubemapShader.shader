#shader vertex
#version 330 core

layout(location = 0) in vec3 pos;
//layout(location = 1) in vec2 texCoord;
layout(location = 3) in mat4 instanceMatrix;

out vec3 finalTexCoord;

// matrix, view, projection
uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * instanceMatrix * vec4(pos, 1.0);
	finalTexCoord = pos;
}

#shader fragment
#version 330 core
out vec4 colour;

in vec3 finalTexCoord;

uniform samplerCube texture1;

uniform float alpha;

void main()
{
	colour = texture(texture1, finalTexCoord);

	// if the player is underwater, uncomment these and switch them using uniforms.
	// make the alpha = to zero when rendering the water

	//colour.b = colour.b + 0.7f;
	//colour.r = colour.r - 0.1f;
	//colour.g = colour.g - 0.1f;
	colour.a = alpha;
}
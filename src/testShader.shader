#shader vertex

#version 330 core

layout (location = 0) in vec3 pos;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
}

#shader fragment

#version 330 core

out vec4 fragColour;

void main()
{
	fragColour = vec4(0.0f, 0.6f, 0.3f, 1.0f);
}
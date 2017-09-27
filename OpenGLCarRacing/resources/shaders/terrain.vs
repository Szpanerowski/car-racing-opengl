#version 330 core
layout ( location = 0 ) in vec3 position;
layout ( location = 1 ) in vec3 normal;
layout ( location = 2 ) in vec2 texCoords;

out vec2 TexCoords;
out vec3 n;
out vec3 p;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main( )
{
	vec4 p4 = model * vec4( position, 1.0f );

    gl_Position = projection * view * p4;
    
	TexCoords = texCoords;
	n = normal;
	p = p4.xyz;
}

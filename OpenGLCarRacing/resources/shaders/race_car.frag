#version 330 core

in vec2 TexCoords;
in vec3 n;
in vec3 p;

out vec4 color;

uniform sampler2D texture_diffuse;

uniform int lightSourcesCount;
uniform vec3 globalAmbient;
uniform vec3 lightPositions[32];
uniform vec3 lightDirections[32];
uniform vec3 lightColors[32];
uniform float lightAngles[32];

void main( )
{
	vec3 lightIntensity = globalAmbient;

	for (int i = 0; i < lightSourcesCount; ++i) {

		vec3 l = p - lightPositions[i];
		vec3 d = lightDirections[i];

		float nl = max(dot(-normalize(l), n), 0);
		float angle = acos(dot(normalize(d), normalize(l)));
		float penumbra = radians(lightAngles[i]);
		float umbra = radians(lightAngles[i] + 15);

		vec3 il = vec3(0, 0, 0);

		if (angle <= penumbra)
			il = lightColors[i] * vec3(nl, nl, nl) / (length(l) / 2);
		else if (angle <= umbra)
			il = (lightColors[i] * vec3(nl, nl, nl) / (length(l) / 2)) * (cos(angle) - cos(umbra)) / (cos(penumbra) - cos(umbra));

		lightIntensity += il;
	}

    color = vec4( texture( texture_diffuse, TexCoords )) * vec4(lightIntensity, 0);
}

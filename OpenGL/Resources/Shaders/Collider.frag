#version 330 core
out vec4 FragColor;

uniform int isActive;
uniform int collide;

void main()
{
	if(isActive != 1)
		FragColor = vec4(0, 0.5, 0, 1);
	else if(collide != 1)
		FragColor = vec4(0, 1, 0, 1);
	else
		FragColor = vec4(1, 0, 0, 1);
}

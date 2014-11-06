#version 430 core

//Push through the color

varying vec4 gl_Color; 

void main()
{
	gl_FragColor = vec4(0.4,0.4,0.8,1.0);
}
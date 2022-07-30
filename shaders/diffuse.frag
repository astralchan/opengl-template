// vim: ts=4 sw=4 noet cc=80

#version 330 core

#ifdef GL_ES
precision mediump float;
#endif

layout(location = 0) out vec4 color;

void main()
{
	color = vec4(0.0f, 0.25f, 0.5f, 1.0f);
}

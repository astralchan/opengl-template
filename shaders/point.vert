// vim: ts=4 sw=4 noet cc=80

#version 330 core

#ifdef GL_ES
precision mediump float;
#endif

layout(location = 0) in vec2 pos;

void main()
{
	gl_Position = vec4(pos, 0.0f, 1.0f);
}

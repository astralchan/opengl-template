// vim: ts=4 sw=4 noet cc=80

#include <epoxy/gl.h>
#include <stdio.h>

#include "renderer.h"

// Initialize a vertex buffer object
void vboinit(GLsizeiptr size, const GLvoid *data)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

// Initialize a vertex array object
void vaoinit(GLuint index, GLint size, GLsizei stride)
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
}

// Print GL information
void printGlInfo(void)
{
	printf(
		"GL Vendor: %s\n"
		"GL Renderer: %s\n"
		"GL Version: %s\n"
		"GLSL Version: %s\n",
		glGetString(GL_VENDOR),
		glGetString(GL_RENDERER),
		glGetString(GL_VERSION),
		glGetString(GL_SHADING_LANGUAGE_VERSION)
	);
}

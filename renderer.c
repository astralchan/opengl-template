// vim: ts=4 sw=4 noet cc=80

#include <epoxy/gl.h>
#include <stdio.h>
#include <stdlib.h>

#include "renderer.h"
#include "util.h"

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
void print_gl_info(void)
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

// Make a shader from a source file
GLuint makeshader(const GLenum type, const char path[])
{
	// Read shader source in
	const GLchar *src = (const GLchar *)readfile(path);
	if (!src) return 0;

	// Make shader
	GLuint shader = glCreateShader(type);

	// Build shader
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	// Check the build
	GLint result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		// Print that error occured
		fprintf(stderr, "Failed to compile shader: %s\n", path);

		// Make char array for log msg
		GLchar *msg = malloc(sizeof(GLchar) * length);
		if (!msg) {
			perror("ERROR");
			fputs("Failed to allocate memory for log\n", stderr);
			glDeleteShader(shader);
			return 0;
		}

		// Read log into msg
		glGetShaderInfoLog(shader, length, &length, msg);
		fputs(msg, stderr);
		free(msg);

		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

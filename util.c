// vim: ts=4 sw=4 noet cc=80

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "util.h"

// Read file into char pointer
char *readfile(const char filename[])
{
	// Open the file
	FILE *fp = fopen(filename, "r");
	if (!fp) {
		perror("ERROR");
		fprintf(stderr, "Failed to open file: %s\n", filename);
		return NULL;
	}

	// Get file size
	if (fseek(fp, 0L, SEEK_END) == -1) {
		perror("ERROR");
		fprintf(stderr, "Failed to seek end of file: %s\n", filename);
		fclose(fp);
		return NULL;
	}
	long filesize = ftell(fp);
	rewind(fp);

	// Allocate memory for the file content
	char *content = malloc(filesize + 1);
	if (!content) {
		perror("ERROR");
		fprintf(stderr, "Failed to allocate memory for file: %s\n", filename);
		fclose(fp);
		return NULL;
	}

	// Read file into char pointer
	if (!fread(content, 1, filesize, fp)) {
		perror("ERROR");
		fprintf(stderr, "Failed to read file: %s\n", filename);
		fclose(fp);
		free(content);
		return NULL;
	}

	// Close the file
	fclose(fp);

	// Null-terminate the file content
	content[filesize] = '\0';

	return content;
}

// Make a shader from a source file
GLuint makeshader(const GLenum type, const char shaderpath[])
{
	// Read shader source in
	const GLchar *src = (const GLchar *)readfile(shaderpath);
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

		// Print error and exit
		fprintf(stderr, "Failed to compile shader: %s\n%s", shaderpath, msg);
		free(msg);
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

void printGlfwVersion(void)
{
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Running GLFW %d.%d.%d\n", major, minor, revision);
}

// vim: ts=4 sw=4 noet cc=80

// Spawn a window with a triangle in it

#include <epoxy/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "util.h"
#include "renderer.h"

#define GLFW_INIT_ERROR   1
#define GLFW_WINDOW_ERROR 2
#define FILE_READ_ERROR   3

int main(void)
{
	// Print GLFW running version
	print_glfw_version();

	// Initialize GLFW
	if (glfwInit() != GLFW_TRUE) {
		fputs("Failed to initialize GLFW\n", stderr);
		return GLFW_INIT_ERROR;
	}

	// Set GLFW window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFW window
	GLFWwindow *window = glfwCreateWindow(800, 600, "Title", NULL, NULL);
	if (!window) {
		glfwTerminate();
		fputs("Failed to create GLFW window\n", stderr);
		return GLFW_WINDOW_ERROR;
	}

	// Make the window the current context
	glfwMakeContextCurrent(window);

	// Print GL info
	print_gl_info();

	// Make points for triangle
	GLfloat points[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.0f,  0.5f
	};

	// Make and bind vertex buffer object
	vboinit(sizeof(GLfloat) * 6, points);

	// Make and bind vertex array object
	vaoinit(0, 2, 0);

	// Read in and compile shader programs

	GLuint fragmentShader = makeshader(GL_FRAGMENT_SHADER,
		"shaders/fragment.glsl");
	if (!fragmentShader) return FILE_READ_ERROR;

	GLuint vertexShader = makeshader(GL_VERTEX_SHADER, "shaders/vertex.glsl");
	if (!vertexShader) return FILE_READ_ERROR;

	// Make and link shader program
	GLuint shader = glCreateProgram();
	glAttachShader(shader, fragmentShader);
	glAttachShader(shader, vertexShader);
	glLinkProgram(shader);

	// Use the shader program
	glUseProgram(shader);

	// Keep window open while not closed
	while (!glfwWindowShouldClose(window)) {
		// Clear buffer
		glClear(GL_COLOR_BUFFER_BIT);
		// Clear color
		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		// Draw a triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// Swap front and back buffers
		glfwSwapBuffers(window);
		// Listen for window events
		glfwPollEvents();
	}

	// Terminate GLFW
	glfwTerminate();

	return 0;
}

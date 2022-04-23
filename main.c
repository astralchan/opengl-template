// vim: ts=4 sw=4 noet cc=80

// Spawn a window with a triangle in it

#include <epoxy/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "util.h"

#define GLFW_INIT_ERROR   1
#define GLFW_WINDOW_ERROR 2
#define FILE_READ_ERROR   3

int main(void)
{
	// Print GLFW running version
	printGlfwVersion();

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

	// Make points for triangle
	GLfloat points[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.0f,  0.5f
	};

	// Make and bind vertex buffer object
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6, points, GL_STATIC_DRAW);

	// Make and bind vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

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

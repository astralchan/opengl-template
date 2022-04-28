// vim: ts=4 sw=4 noet cc=80

#include <stdio.h>
#include <stdlib.h>
#include <epoxy/gl.h>
#include <GLFW/glfw3.h>

#include "util.h"

// Read file into char pointer
char *readfile(const char file[])
{
	// Open the file
	FILE *fp = fopen(file, "r");
	if (!fp) {
		perror("ERROR");
		fprintf(stderr, "Failed to open file: %s\n", file);
		return NULL;
	}

	// Get file size
	if (fseek(fp, 0L, SEEK_END) == -1) {
		perror("ERROR");
		fprintf(stderr, "Failed to seek end of file: %s\n", file);
		fclose(fp);
		return NULL;
	}
	long filesize = ftell(fp);
	rewind(fp);

	// Allocate memory for the file content
	char *content = malloc(filesize + 1);
	if (!content) {
		perror("ERROR");
		fprintf(stderr, "Failed to allocate memory for file: %s\n", file);
		fclose(fp);
		return NULL;
	}

	// Read file into char pointer
	if (!fread(content, 1, filesize, fp)) {
		perror("ERROR");
		fprintf(stderr, "Failed to read file: %s\n", file);
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

void print_glfw_version(void)
{
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Running GLFW %d.%d.%d\n", major, minor, revision);
}

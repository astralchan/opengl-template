// vim: ts=4 sw=4 noet cc=80

#ifndef UTIL_H
#define UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

// Defines

// Error code for fileread
#define FILE_READ_ERROR 3

// Prototypes

// Read a file
char *readfile(const char[]);
// Print GLFW running version
void print_glfw_version(void);

#ifdef __cplusplus
}
#endif

#endif // UTIL_H

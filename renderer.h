// vim: ts=4 sw=4 noet cc=80

#ifndef RENDERER_H
#define RENDERER_H

#ifdef __cplusplus
extern "C" {
#endif

// Includes

#include <epoxy/gl.h>

// Prototypes

// Initislize vertex buffer object
void vboinit(GLsizeiptr, const GLvoid *);
// Initialize vertex array object
void vaoinit(GLuint, GLint, GLsizei);
// Print GL information
void print_gl_info(void);
// Read and compile a shader
GLuint makeshader(const GLenum, const char[]);

#ifdef __cplusplus
}
#endif

#endif // RENDERER_H

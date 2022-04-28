// vim: ts=4 sw=4 noet cc=80

#ifndef RENDERER_H
#define RENDERER_H
void vboinit(GLsizeiptr, const GLvoid *);
void vaoinit(GLuint, GLint, GLsizei);
void print_gl_info(void);
GLuint makeshader(const GLenum, const char[]);
#endif

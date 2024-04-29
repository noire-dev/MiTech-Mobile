/*
 * This file is part of the D3wasm project (http://www.continuation-labs.com/projects/d3wasm)
 * Copyright (c) 2019 Gabriel Cuvillier.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef QGLPROC
#error "you must define QGLPROC before including this file"
#endif

// OpenGL ES 2.0 / WebGL 1.0 API
QGLPROC(glActiveTexture, void, (GLenum texture))
QGLPROC(glAttachShader, void, (GLuint program, GLuint shader))
QGLPROC(glBindAttribLocation, void, (GLuint program, GLuint index, const GLchar *name))
QGLPROC(glBindBuffer, void, (GLenum target, GLuint buffer))
QGLPROC(glBindFramebuffer, void, (GLenum target, GLuint framebuffer))
QGLPROC(glBindRenderbuffer, void, (GLenum target, GLuint renderbuffer))
QGLPROC(glBindTexture, void, (GLenum target, GLuint texture))
QGLPROC(glBlendColor, void, (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha))
QGLPROC(glBlendEquation, void, (GLenum mode))
QGLPROC(glBlendEquationSeparate, void, (GLenum modeRGB, GLenum modeAlpha))
QGLPROC(glBlendFunc, void, (GLenum sfactor, GLenum dfactor))
QGLPROC(glBlendFuncSeparate, void, (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha))
QGLPROC(glBufferData, void, (GLenum target, GLsizeiptr size, const void *data, GLenum usage))
QGLPROC(glBufferSubData, void, (GLenum target, GLintptr offset, GLsizeiptr size, const void *data))
QGLPROC(glCheckFramebufferStatus, GLenum, (GLenum target))
QGLPROC(glClear, void, (GLbitfield mask))
QGLPROC(glClearColor, void, (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha))
QGLPROC(glClearDepthf, void, (GLfloat d))
QGLPROC(glClearStencil, void, (GLint s))
QGLPROC(glColorMask, void, (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha))
QGLPROC(glCompileShader, void, (GLuint shader))
QGLPROC(glCompressedTexImage2D, void, (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data))
QGLPROC(glCompressedTexSubImage2D, void, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data))
QGLPROC(glCopyTexImage2D, void, (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border))
QGLPROC(glCopyTexSubImage2D, void, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height))
QGLPROC(glCreateProgram, GLuint, (void))
QGLPROC(glCreateShader, GLuint, (GLenum type))
QGLPROC(glCullFace, void, (GLenum mode))
QGLPROC(glDeleteBuffers, void, (GLsizei n, const GLuint *buffers))
QGLPROC(glDeleteFramebuffers, void, (GLsizei n, const GLuint *framebuffers))
QGLPROC(glDeleteProgram, void, (GLuint program))
QGLPROC(glDeleteRenderbuffers, void, (GLsizei n, const GLuint *renderbuffers))
QGLPROC(glDeleteShader, void, (GLuint shader))
QGLPROC(glDeleteTextures, void, (GLsizei n, const GLuint *textures))
QGLPROC(glDepthFunc, void, (GLenum func))
QGLPROC(glDepthMask, void, (GLboolean flag))
QGLPROC(glDepthRangef, void, (GLfloat n, GLfloat f))
QGLPROC(glDetachShader, void, (GLuint program, GLuint shader))
QGLPROC(glDisable, void, (GLenum cap))
QGLPROC(glDisableVertexAttribArray, void, (GLuint index))
QGLPROC(glDrawArrays, void, (GLenum mode, GLint first, GLsizei count))
QGLPROC(glDrawElements, void, (GLenum mode, GLsizei count, GLenum type, const void *indices))
QGLPROC(glEnable, void, (GLenum cap))
QGLPROC(glEnableVertexAttribArray, void, (GLuint index))
QGLPROC(glFinish, void, (void))
QGLPROC(glFlush, void, (void))
QGLPROC(glFramebufferRenderbuffer, void, (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer))
QGLPROC(glFramebufferTexture2D, void, (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level))
QGLPROC(glFrontFace, void, (GLenum mode))
QGLPROC(glGenBuffers, void, (GLsizei n, GLuint *buffers))
QGLPROC(glGenerateMipmap, void, (GLenum target))
QGLPROC(glGenFramebuffers, void, (GLsizei n, GLuint *framebuffers))
QGLPROC(glGenRenderbuffers, void, (GLsizei n, GLuint *renderbuffers))
QGLPROC(glGenTextures, void, (GLsizei n, GLuint *textures))
QGLPROC(glGetActiveAttrib, void, (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name))
QGLPROC(glGetActiveUniform, void, (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name))
QGLPROC(glGetAttachedShaders, void, (GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders))
QGLPROC(glGetAttribLocation, GLint, (GLuint program, const GLchar *name))
QGLPROC(glGetBooleanv, void, (GLenum pname, GLboolean *data))
QGLPROC(glGetBufferParameteriv, void, (GLenum target, GLenum pname, GLint *params))
QGLPROC(glGetError, GLenum, (void))
QGLPROC(glGetFloatv, void, (GLenum pname, GLfloat *data))
QGLPROC(glGetFramebufferAttachmentParameteriv, void, (GLenum target, GLenum attachment, GLenum pname, GLint *params))
QGLPROC(glGetIntegerv, void, (GLenum pname, GLint *data))
QGLPROC(glGetProgramiv, void, (GLuint program, GLenum pname, GLint *params))
QGLPROC(glGetProgramInfoLog, void, (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog))
QGLPROC(glGetRenderbufferParameteriv, void, (GLenum target, GLenum pname, GLint *params))
QGLPROC(glGetShaderiv, void, (GLuint shader, GLenum pname, GLint *params))
QGLPROC(glGetShaderInfoLog, void, (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog))
QGLPROC(glGetShaderPrecisionFormat, void, (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision))
QGLPROC(glGetShaderSource, void, (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source))
QGLPROC(glGetString, const GLubyte *, (GLenum name))
QGLPROC(glGetTexParameterfv, void, (GLenum target, GLenum pname, GLfloat *params))
QGLPROC(glGetTexParameteriv, void, (GLenum target, GLenum pname, GLint *params))
QGLPROC(glGetUniformfv, void, (GLuint program, GLint location, GLfloat *params))
QGLPROC(glGetUniformiv, void, (GLuint program, GLint location, GLint *params))
QGLPROC(glGetUniformLocation, GLint, (GLuint program, const GLchar *name))
QGLPROC(glGetVertexAttribfv, void, (GLuint index, GLenum pname, GLfloat *params))
QGLPROC(glGetVertexAttribiv, void, (GLuint index, GLenum pname, GLint *params))
QGLPROC(glGetVertexAttribPointerv, void, (GLuint index, GLenum pname, void **pointer))
QGLPROC(glHint, void, (GLenum target, GLenum mode))
QGLPROC(glIsBuffer, GLboolean, (GLuint buffer))
QGLPROC(glIsEnabled, GLboolean, (GLenum cap))
QGLPROC(glIsFramebuffer, GLboolean, (GLuint framebuffer))
QGLPROC(glIsProgram, GLboolean, (GLuint program))
QGLPROC(glIsRenderbuffer, GLboolean, (GLuint renderbuffer))
QGLPROC(glIsShader, GLboolean, (GLuint shader))
QGLPROC(glIsTexture, GLboolean, (GLuint texture))
QGLPROC(glLineWidth, void, (GLfloat width))
QGLPROC(glLinkProgram, void, (GLuint program))
QGLPROC(glPixelStorei, void, (GLenum pname, GLint param))
QGLPROC(glPolygonOffset, void, (GLfloat factor, GLfloat units))
QGLPROC(glReadPixels, void, (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels))
QGLPROC(glReleaseShaderCompiler, void, (void))
QGLPROC(glRenderbufferStorage, void, (GLenum target, GLenum internalformat, GLsizei width, GLsizei height))
QGLPROC(glSampleCoverage, void, (GLfloat value, GLboolean invert))
QGLPROC(glScissor, void, (GLint x, GLint y, GLsizei width, GLsizei height))
QGLPROC(glShaderBinary, void, (GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length))
QGLPROC(glShaderSource, void, (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length))
QGLPROC(glStencilFunc, void, (GLenum func, GLint ref, GLuint mask))
QGLPROC(glStencilFuncSeparate, void, (GLenum face, GLenum func, GLint ref, GLuint mask))
QGLPROC(glStencilMask, void, (GLuint mask))
QGLPROC(glStencilMaskSeparate, void, (GLenum face, GLuint mask))
QGLPROC(glStencilOp, void, (GLenum fail, GLenum zfail, GLenum zpass))
QGLPROC(glStencilOpSeparate, void, (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass))
QGLPROC(glTexImage2D, void, (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels))
QGLPROC(glTexParameterf, void, (GLenum target, GLenum pname, GLfloat param))
QGLPROC(glTexParameterfv, void, (GLenum target, GLenum pname, const GLfloat *params))
QGLPROC(glTexParameteri, void, (GLenum target, GLenum pname, GLint param))
QGLPROC(glTexParameteriv, void, (GLenum target, GLenum pname, const GLint *params))
QGLPROC(glTexSubImage2D, void, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels))
QGLPROC(glUniform1f, void, (GLint location, GLfloat v0))
QGLPROC(glUniform1fv, void, (GLint location, GLsizei count, const GLfloat *value))
QGLPROC(glUniform1i, void, (GLint location, GLint v0))
QGLPROC(glUniform1iv, void, (GLint location, GLsizei count, const GLint *value))
QGLPROC(glUniform2f, void, (GLint location, GLfloat v0, GLfloat v1))
QGLPROC(glUniform2fv, void, (GLint location, GLsizei count, const GLfloat *value))
QGLPROC(glUniform2i, void, (GLint location, GLint v0, GLint v1))
QGLPROC(glUniform2iv, void, (GLint location, GLsizei count, const GLint *value))
QGLPROC(glUniform3f, void, (GLint location, GLfloat v0, GLfloat v1, GLfloat v2))
QGLPROC(glUniform3fv, void, (GLint location, GLsizei count, const GLfloat *value))
QGLPROC(glUniform3i, void, (GLint location, GLint v0, GLint v1, GLint v2))
QGLPROC(glUniform3iv, void, (GLint location, GLsizei count, const GLint *value))
QGLPROC(glUniform4f, void, (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3))
QGLPROC(glUniform4fv, void, (GLint location, GLsizei count, const GLfloat *value))
QGLPROC(glUniform4i, void, (GLint location, GLint v0, GLint v1, GLint v2, GLint v3))
QGLPROC(glUniform4iv, void, (GLint location, GLsizei count, const GLint *value))
QGLPROC(glUniformMatrix2fv, void, (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value))
QGLPROC(glUniformMatrix3fv, void, (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value))
QGLPROC(glUniformMatrix4fv, void, (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value))
QGLPROC(glUseProgram, void, (GLuint program))
QGLPROC(glValidateProgram, void, (GLuint program))
QGLPROC(glVertexAttrib1f, void, (GLuint index, GLfloat x))
QGLPROC(glVertexAttrib1fv, void, (GLuint index, const GLfloat *v))
QGLPROC(glVertexAttrib2f, void, (GLuint index, GLfloat x, GLfloat y))
QGLPROC(glVertexAttrib2fv, void, (GLuint index, const GLfloat *v))
QGLPROC(glVertexAttrib3f, void, (GLuint index, GLfloat x, GLfloat y, GLfloat z))
QGLPROC(glVertexAttrib3fv, void, (GLuint index, const GLfloat *v))
QGLPROC(glVertexAttrib4f, void, (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w))
QGLPROC(glVertexAttrib4fv, void, (GLuint index, const GLfloat *v))
QGLPROC(glVertexAttribPointer, void, (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer))
QGLPROC(glViewport, void, (GLint x, GLint y, GLsizei width, GLsizei height))


#define USE_MAP false

#if USE_MAP
QGLPROC(glMapBufferRange, void*, (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access))
//QGLPROC(glMapBuffer, void*, (GLenum target, GLenum access))
QGLPROC(glUnmapBuffer, GLboolean,(GLenum target))
#endif

// GLES3.0
#ifdef _OPENGLES3
QGLPROC(glTexImage3D, void, (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels))
QGLPROC(glReadBuffer, void, (GLenum src));
QGLPROC(glDrawBuffers, void, (GLsizei n, const GLenum *bufs));
QGLPROC(glFramebufferTextureLayer, void, (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer));
#endif

#undef QGLPROC

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

#ifndef QGLCALL
#error "you must define QGLCALL before including this file"
#endif
QGLCALL(glActiveTexture, void, (GLenum texture), (void), (texture), return)
QGLCALL(glAttachShader, void, (GLuint program, GLuint shader), (void), (program, shader), return)
QGLCALL(glBindAttribLocation, void, (GLuint program, GLuint index, const GLchar *name), (void), (program, index, name), return)
QGLCALL(glBindBuffer, void, (GLenum target, GLuint buffer), (void), (target, buffer), return)
QGLCALL(glBindFramebuffer, void, (GLenum target, GLuint framebuffer), (void), (target, framebuffer), return)
QGLCALL(glBindRenderbuffer, void, (GLenum target, GLuint renderbuffer), (void), (target, renderbuffer), return)
QGLCALL(glBindTexture, void, (GLenum target, GLuint texture), (void), (target, texture), return)
QGLCALL(glBlendColor, void, (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha), (void), (red, green, blue, alpha), return)
QGLCALL(glBlendEquation, void, (GLenum mode), (void), (mode), return)
QGLCALL(glBlendEquationSeparate, void, (GLenum modeRGB, GLenum modeAlpha), (void), (modeRGB, modeAlpha), return)
QGLCALL(glBlendFunc, void, (GLenum sfactor, GLenum dfactor), (void), (sfactor, dfactor), return)
QGLCALL(glBlendFuncSeparate, void, (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha), (void), (sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha), return)
QGLCALL(glBufferData, void, (GLenum target, GLsizeiptr size, const void *data, GLenum usage), (void), (target, size, data, usage), return)
QGLCALL(glBufferSubData, void, (GLenum target, GLintptr offset, GLsizeiptr size, const void *data), (void), (target, offset, size, data), return)
QGLCALL(glCheckFramebufferStatus, GLenum, (GLenum target), GLenum _ret =, (target), return _ret)
QGLCALL(glClear, void, (GLbitfield mask), (void), (mask), return)
QGLCALL(glClearColor, void, (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha), (void), (red, green, blue, alpha), return)
QGLCALL(glClearDepthf, void, (GLfloat d), (void), (d), return)
QGLCALL(glClearStencil, void, (GLint s), (void), (s), return)
QGLCALL(glColorMask, void, (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha), (void), (red, green, blue, alpha), return)
QGLCALL(glCompileShader, void, (GLuint shader), (void), (shader), return)
QGLCALL(glCompressedTexImage2D, void, (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data), (void), (target, level, internalformat, width, height, border, imageSize, data), return)
QGLCALL(glCompressedTexSubImage2D, void, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data), (void), (target, level, xoffset, yoffset, width, height, format, imageSize, data), return)
QGLCALL(glCopyTexImage2D, void, (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border), (void), (target, level, internalformat, x, y, width, height, border), return)
QGLCALL(glCopyTexSubImage2D, void, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height), (void), (target, level, xoffset, yoffset, x, y, width, height), return)
QGLCALL(glCreateProgram, GLuint, (void), GLuint _ret =, (), return _ret)
QGLCALL(glCreateShader, GLuint, (GLenum type), GLuint _ret =, (type), return _ret)
QGLCALL(glCullFace, void, (GLenum mode), (void), (mode), return)
QGLCALL(glDeleteBuffers, void, (GLsizei n, const GLuint *buffers), (void), (n, buffers), return)
QGLCALL(glDeleteFramebuffers, void, (GLsizei n, const GLuint *framebuffers), (void), (n, framebuffers), return)
QGLCALL(glDeleteProgram, void, (GLuint program), (void), (program), return)
QGLCALL(glDeleteRenderbuffers, void, (GLsizei n, const GLuint *renderbuffers), (void), (n, renderbuffers), return)
QGLCALL(glDeleteShader, void, (GLuint shader), (void), (shader), return)
QGLCALL(glDeleteTextures, void, (GLsizei n, const GLuint *textures), (void), (n, textures), return)
QGLCALL(glDepthFunc, void, (GLenum func), (void), (func), return)
QGLCALL(glDepthMask, void, (GLboolean flag), (void), (flag), return)
QGLCALL(glDepthRangef, void, (GLfloat n, GLfloat f), (void), (n, f), return)
QGLCALL(glDetachShader, void, (GLuint program, GLuint shader), (void), (program, shader), return)
QGLCALL(glDisable, void, (GLenum cap), (void), (cap), return)
QGLCALL(glDisableVertexAttribArray, void, (GLuint index), (void), (index), return)
QGLCALL(glDrawArrays, void, (GLenum mode, GLint first, GLsizei count), (void), (mode, first, count), return)
QGLCALL(glDrawElements, void, (GLenum mode, GLsizei count, GLenum type, const void *indices), (void), (mode, count, type, indices), return)
QGLCALL(glEnable, void, (GLenum cap), (void), (cap), return)
QGLCALL(glEnableVertexAttribArray, void, (GLuint index), (void), (index), return)
QGLCALL(glFinish, void, (void), (void), (), return)
QGLCALL(glFlush, void, (void), (void), (), return)
QGLCALL(glFramebufferRenderbuffer, void, (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer), (void), (target, attachment, renderbuffertarget, renderbuffer), return)
QGLCALL(glFramebufferTexture2D, void, (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level), (void), (target, attachment, textarget, texture, level), return)
QGLCALL(glFrontFace, void, (GLenum mode), (void), (mode), return)
QGLCALL(glGenBuffers, void, (GLsizei n, GLuint *buffers), (void), (n, buffers), return)
QGLCALL(glGenerateMipmap, void, (GLenum target), (void), (target), return)
QGLCALL(glGenFramebuffers, void, (GLsizei n, GLuint *framebuffers), (void), (n, framebuffers), return)
QGLCALL(glGenRenderbuffers, void, (GLsizei n, GLuint *renderbuffers), (void), (n, renderbuffers), return)
QGLCALL(glGenTextures, void, (GLsizei n, GLuint *textures), (void), (n, textures), return)
QGLCALL(glGetActiveAttrib, void, (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name), (void), (program, index, bufSize, length, size, type, name), return)
QGLCALL(glGetActiveUniform, void, (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name), (void), (program, index, bufSize, length, size, type, name), return)
QGLCALL(glGetAttachedShaders, void, (GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders), (void), (program, maxCount, count, shaders), return)
QGLCALL(glGetAttribLocation, GLint, (GLuint program, const GLchar *name), GLint _ret =, (program, name), return _ret)
QGLCALL(glGetBooleanv, void, (GLenum pname, GLboolean *data), (void), (pname, data), return)
QGLCALL(glGetBufferParameteriv, void, (GLenum target, GLenum pname, GLint *params), (void), (target, pname, params), return)
QGLCALL(glGetError, GLenum, (void), GLenum _ret =, (), return _ret)
QGLCALL(glGetFloatv, void, (GLenum pname, GLfloat *data), (void), (pname, data), return)
QGLCALL(glGetFramebufferAttachmentParameteriv, void, (GLenum target, GLenum attachment, GLenum pname, GLint *params), (void), (target, attachment, pname, params), return)
QGLCALL(glGetIntegerv, void, (GLenum pname, GLint *data), (void), (pname, data), return)
QGLCALL(glGetProgramiv, void, (GLuint program, GLenum pname, GLint *params), (void), (program, pname, params), return)
QGLCALL(glGetProgramInfoLog, void, (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog), (void), (program, bufSize, length, infoLog), return)
QGLCALL(glGetRenderbufferParameteriv, void, (GLenum target, GLenum pname, GLint *params), (void), (target, pname, params), return)
QGLCALL(glGetShaderiv, void, (GLuint shader, GLenum pname, GLint *params), (void), (shader, pname, params), return)
QGLCALL(glGetShaderInfoLog, void, (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog), (void), (shader, bufSize, length, infoLog), return)
QGLCALL(glGetShaderPrecisionFormat, void, (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision), (void), (shadertype, precisiontype, range, precision), return)
QGLCALL(glGetShaderSource, void, (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source), (void), (shader, bufSize, length, source), return)
QGLCALL(glGetString, const GLubyte *, (GLenum name), const GLubyte * _ret =, (name), return _ret)
QGLCALL(glGetTexParameterfv, void, (GLenum target, GLenum pname, GLfloat *params), (void), (target, pname, params), return)
QGLCALL(glGetTexParameteriv, void, (GLenum target, GLenum pname, GLint *params), (void), (target, pname, params), return)
QGLCALL(glGetUniformfv, void, (GLuint program, GLint location, GLfloat *params), (void), (program, location, params), return)
QGLCALL(glGetUniformiv, void, (GLuint program, GLint location, GLint *params), (void), (program, location, params), return)
QGLCALL(glGetUniformLocation, GLint, (GLuint program, const GLchar *name), GLint _ret =, (program, name), return _ret)
QGLCALL(glGetVertexAttribfv, void, (GLuint index, GLenum pname, GLfloat *params), (void), (index, pname, params), return)
QGLCALL(glGetVertexAttribiv, void, (GLuint index, GLenum pname, GLint *params), (void), (index, pname, params), return)
QGLCALL(glGetVertexAttribPointerv, void, (GLuint index, GLenum pname, void **pointer), (void), (index, pname, pointer), return)
QGLCALL(glHint, void, (GLenum target, GLenum mode), (void), (target, mode), return)
QGLCALL(glIsBuffer, GLboolean, (GLuint buffer), GLboolean _ret =, (buffer), return _ret)
QGLCALL(glIsEnabled, GLboolean, (GLenum cap), GLboolean _ret =, (cap), return _ret)
QGLCALL(glIsFramebuffer, GLboolean, (GLuint framebuffer), GLboolean _ret =, (framebuffer), return _ret)
QGLCALL(glIsProgram, GLboolean, (GLuint program), GLboolean _ret =, (program), return _ret)
QGLCALL(glIsRenderbuffer, GLboolean, (GLuint renderbuffer), GLboolean _ret =, (renderbuffer), return _ret)
QGLCALL(glIsShader, GLboolean, (GLuint shader), GLboolean _ret =, (shader), return _ret)
QGLCALL(glIsTexture, GLboolean, (GLuint texture), GLboolean _ret =, (texture), return _ret)
QGLCALL(glLineWidth, void, (GLfloat width), (void), (width), return)
QGLCALL(glLinkProgram, void, (GLuint program), (void), (program), return)
QGLCALL(glPixelStorei, void, (GLenum pname, GLint param), (void), (pname, param), return)
QGLCALL(glPolygonOffset, void, (GLfloat factor, GLfloat units), (void), (factor, units), return)
QGLCALL(glReadPixels, void, (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels), (void), (x, y, width, height, format, type, pixels), return)
QGLCALL(glReleaseShaderCompiler, void, (void), (void), (), return)
QGLCALL(glRenderbufferStorage, void, (GLenum target, GLenum internalformat, GLsizei width, GLsizei height), (void), (target, internalformat, width, height), return)
QGLCALL(glSampleCoverage, void, (GLfloat value, GLboolean invert), (void), (value, invert), return)
QGLCALL(glScissor, void, (GLint x, GLint y, GLsizei width, GLsizei height), (void), (x, y, width, height), return)
QGLCALL(glShaderBinary, void, (GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length), (void), (count, shaders, binaryformat, binary, length), return)
QGLCALL(glShaderSource, void, (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length), (void), (shader, count, string, length), return)
QGLCALL(glStencilFunc, void, (GLenum func, GLint ref, GLuint mask), (void), (func, ref, mask), return)
QGLCALL(glStencilFuncSeparate, void, (GLenum face, GLenum func, GLint ref, GLuint mask), (void), (face, func, ref, mask), return)
QGLCALL(glStencilMask, void, (GLuint mask), (void), (mask), return)
QGLCALL(glStencilMaskSeparate, void, (GLenum face, GLuint mask), (void), (face, mask), return)
QGLCALL(glStencilOp, void, (GLenum fail, GLenum zfail, GLenum zpass), (void), (fail, zfail, zpass), return)
QGLCALL(glStencilOpSeparate, void, (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass), (void), (face, sfail, dpfail, dppass), return)
QGLCALL(glTexImage2D, void, (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels), (void), (target, level, internalformat, width, height, border, format, type, pixels), return)
QGLCALL(glTexParameterf, void, (GLenum target, GLenum pname, GLfloat param), (void), (target, pname, param), return)
QGLCALL(glTexParameterfv, void, (GLenum target, GLenum pname, const GLfloat *params), (void), (target, pname, params), return)
QGLCALL(glTexParameteri, void, (GLenum target, GLenum pname, GLint param), (void), (target, pname, param), return)
QGLCALL(glTexParameteriv, void, (GLenum target, GLenum pname, const GLint *params), (void), (target, pname, params), return)
QGLCALL(glTexSubImage2D, void, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels), (void), (target, level, xoffset, yoffset, width, height, format, type, pixels), return)
QGLCALL(glUniform1f, void, (GLint location, GLfloat v0), (void), (location, v0), return)
QGLCALL(glUniform1fv, void, (GLint location, GLsizei count, const GLfloat *value), (void), (location, count, value), return)
QGLCALL(glUniform1i, void, (GLint location, GLint v0), (void), (location, v0), return)
QGLCALL(glUniform1iv, void, (GLint location, GLsizei count, const GLint *value), (void), (location, count, value), return)
QGLCALL(glUniform2f, void, (GLint location, GLfloat v0, GLfloat v1), (void), (location, v0, v1), return)
QGLCALL(glUniform2fv, void, (GLint location, GLsizei count, const GLfloat *value), (void), (location, count, value), return)
QGLCALL(glUniform2i, void, (GLint location, GLint v0, GLint v1), (void), (location, v0, v1), return)
QGLCALL(glUniform2iv, void, (GLint location, GLsizei count, const GLint *value), (void), (location, count, value), return)
QGLCALL(glUniform3f, void, (GLint location, GLfloat v0, GLfloat v1, GLfloat v2), (void), (location, v0, v1, v2), return)
QGLCALL(glUniform3fv, void, (GLint location, GLsizei count, const GLfloat *value), (void), (location, count, value), return)
QGLCALL(glUniform3i, void, (GLint location, GLint v0, GLint v1, GLint v2), (void), (location, v0, v1, v2), return)
QGLCALL(glUniform3iv, void, (GLint location, GLsizei count, const GLint *value), (void), (location, count, value), return)
QGLCALL(glUniform4f, void, (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3), (void), (location, v0, v1, v2, v3), return)
QGLCALL(glUniform4fv, void, (GLint location, GLsizei count, const GLfloat *value), (void), (location, count, value), return)
QGLCALL(glUniform4i, void, (GLint location, GLint v0, GLint v1, GLint v2, GLint v3), (void), (location, v0, v1, v2, v3), return)
QGLCALL(glUniform4iv, void, (GLint location, GLsizei count, const GLint *value), (void), (location, count, value), return)
QGLCALL(glUniformMatrix2fv, void, (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value), (void), (location, count, transpose, value), return)
QGLCALL(glUniformMatrix3fv, void, (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value), (void), (location, count, transpose, value), return)
QGLCALL(glUniformMatrix4fv, void, (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value), (void), (location, count, transpose, value), return)
QGLCALL(glUseProgram, void, (GLuint program), (void), (program), return)
QGLCALL(glValidateProgram, void, (GLuint program), (void), (program), return)
QGLCALL(glVertexAttrib1f, void, (GLuint index, GLfloat x), (void), (index, x), return)
QGLCALL(glVertexAttrib1fv, void, (GLuint index, const GLfloat *v), (void), (index, v), return)
QGLCALL(glVertexAttrib2f, void, (GLuint index, GLfloat x, GLfloat y), (void), (index, x, y), return)
QGLCALL(glVertexAttrib2fv, void, (GLuint index, const GLfloat *v), (void), (index, v), return)
QGLCALL(glVertexAttrib3f, void, (GLuint index, GLfloat x, GLfloat y, GLfloat z), (void), (index, x, y, z), return)
QGLCALL(glVertexAttrib3fv, void, (GLuint index, const GLfloat *v), (void), (index, v), return)
QGLCALL(glVertexAttrib4f, void, (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w), (void), (index, x, y, z, w), return)
QGLCALL(glVertexAttrib4fv, void, (GLuint index, const GLfloat *v), (void), (index, v), return)
QGLCALL(glVertexAttribPointer, void, (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer), (void), (index, size, type, normalized, stride, pointer), return)
QGLCALL(glViewport, void, (GLint x, GLint y, GLsizei width, GLsizei height), (void), (x, y, width, height), return)
QGLCALL(glMapBufferRange, void *, (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access), void * _ret =, (target, offset, length, access), return _ret)
QGLCALL(glUnmapBuffer, GLboolean, (GLenum target), GLboolean _ret =, (target), return _ret)
QGLCALL(glTexImage3D, void, (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels), (void), (target, level, internalformat, width, height, depth, border, format, type, pixels), return)
QGLCALL(glDrawBuffers, void, (GLsizei n, const GLenum *bufs), (void), (n, bufs), return)
QGLCALL(glFramebufferTextureLayer, void, (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer), (void), (target, attachment, texture, level, layer), return)
QGLCALL(glReadBuffer, void, (GLenum type), (void), (type), return)
QGLCALL(glUniformBlockBinding, void, (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding), (void), (program, uniformBlockIndex, uniformBlockBinding), return)
QGLCALL(glGetUniformBlockIndex, GLuint, (GLuint program, const GLchar *uniformBlockName), GLuint _ret =, (program, uniformBlockName), return _ret)
QGLCALL(glBindBufferRange, void, (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size), (void), (target, index, buffer, offset, size), return)
QGLCALL(glBeginQuery, void, (GLenum target, GLuint id), (void), (target, id), return)
QGLCALL(glEndQuery, void, (GLenum target), (void), (target), return)
QGLCALL(glGenQueries, void, (GLsizei n, GLuint *ids), (void), (n, ids), return)
QGLCALL(glDeleteQueries, void, (GLsizei n, const GLuint *ids), (void), (n, ids), return)
QGLCALL(glGetQueryObjectuiv, void, (GLuint id, GLenum pname, GLuint *params), (void), (id, pname, params), return)
QGLCALL(glBlitFramebuffer, void, (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter), (void), (srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter), return)


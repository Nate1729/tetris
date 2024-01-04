#ifndef SHADER_H
#define SHADER_H

typedef unsigned int ShaderProgram;

ShaderProgram
shader_program_create_from_files(const char *vertex_shader_file,
                                 const char *fragment_shader_file);

void shader_program_set_uniform_i(ShaderProgram prog, const char *name,
                                  int value);
void shader_program_set_uniform_f(ShaderProgram prog, const char *name,
                                  float value);

#endif // !SHADER_H

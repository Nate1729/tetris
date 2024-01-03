#include <stdio.h>

#include <glad.h>

#include "shader.h"

int dump_file(const char *path, char *buffer, unsigned int buffer_size) {
  FILE *f = fopen(path, "r");
  if (f == NULL) {
    printf("Couldn't open file: %s\n", path);
    fclose(f);
    return -1;
  }

  char current_char = fgetc(f);
  int index = 0;
  while (current_char != EOF && index < buffer_size) {
    buffer[index] = current_char;
    current_char = fgetc(f);
    index += 1;
  }
  buffer[index] = 0; /* Null Terminate the string*/

  fclose(f);
  return index;
}

/* Create a vertex shader and compile it.
 * RETURNS 1 on success and 0 on failure.
 *
 */
int create_vertex_shader(unsigned int *shader, const char *shader_source) {
  int success;
  char infoLog[512];
  unsigned int new_shader;

  new_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(new_shader, 1, &shader_source, NULL);
  glCompileShader(new_shader);

  // Error Checking
  glGetShaderiv(new_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(new_shader, 512, NULL, infoLog);
    fprintf(stderr,
            "Error -- Couldn't create vertex shader. Compilation Failed\n%s\n",
            infoLog);
    return 0;
  }

  *shader = new_shader;
  return 1;
}

/* Create a fragment shader and compile it.
 * RETURNS 1 on success and 0 on failure.
 *
 */
int create_fragment_shader(unsigned int *shader, const char *shader_source) {
  int success;
  char infoLog[512];
  unsigned int new_shader;

  new_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(new_shader, 1, &shader_source, NULL);
  glCompileShader(new_shader);

  // Error Checking
  glGetShaderiv(new_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(new_shader, 512, NULL, infoLog);
    fprintf(
        stderr,
        "Error -- Couldn't create fragment shader. Compilation Failed\n%s\n",
        infoLog);
    return 0;
  }

  *shader = new_shader;
  return 1;
}

unsigned int
create_shader_program_from_files(const char *vertex_shader_file,
                                 const char *fragment_shader_file) {

  char vertex_shader_source[2048], fragment_shader_source[2048];
  int characters_read;

  /* Reading Files */
  characters_read = dump_file(vertex_shader_file, vertex_shader_source, 2048);
  if (characters_read < 0) {
    fprintf(stderr, "Error creating shader program.\n");
    return 0;
  }
  characters_read =
      dump_file(fragment_shader_file, fragment_shader_source, 2048);
  if (characters_read < 0) {
    fprintf(stderr, "Error creating shader program.\n");
    return 0;
  }

  /* Compiling shaders
   */
  unsigned int vertex_shader, fragment_shader;
  if (!create_vertex_shader(&vertex_shader, vertex_shader_source)) {
    return 0;
  }
  if (!create_fragment_shader(&fragment_shader, fragment_shader_source)) {
    glDeleteShader(vertex_shader);
    return 0;
  }

  /*Creating Shader Program */
  int success;
  char infoLog[512];
  unsigned int shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

  /* Whether or not we are successful
   * we no longer need the shaders
   */
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
  if (!success) {
    glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
    fprintf(stderr, "Couldn't create shader program.\nError: %s\n", infoLog);
    return 0;
  }
  return shader_program;
}

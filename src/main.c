#include <stdio.h>
#include <stdlib.h>

/* This let's us include in any order.
 */
#define GLFW_INCLUDE_NONE

/* 3rd Party imports */
#include <GLFW/glfw3.h>
#include <glad.h>

/* Local imports */
#include "shader.h"

/* Error callback for GLFW. When an error occurs this
 * function will be called
 */
void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

/* Callback function to handle all key press events
 */
static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

/* Initial game and return active window.
 * - Initialize GLFW,
 * - Setup OPENGL with VERSION 3.3
 * - Create Window
 * - Setup glad
 */
GLFWwindow *init() {
  printf("Initializing glfw.\n");
  if (!glfwInit()) {
    fprintf(stderr, "glfw3 initalization failed! Exiting early.\n");
    exit(EXIT_FAILURE);
  }

  glfwSetErrorCallback(error_callback);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow *window = glfwCreateWindow(640, 480, "Tetris", NULL, NULL);
  if (!window) {
    fprintf(stderr, "Error, couldn't create window. Exiting Early\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);

  /* Bind callback function for key presses.
   * Must be done _after_ window creation since key
   * presses are bound to a window
   */
  glfwSetKeyCallback(window, key_callback);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  /* glad: Load opengl function ptrs */
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize GLAD\n");
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  return window;
}

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSouce = "#version 330 core\n"
                                  "out vec4 FragColor;\n\n"
                                  "void main() {\n"
                                  " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                  "}\0";
void clean_up(GLFWwindow *window) {
  glfwDestroyWindow(window);
  glfwTerminate();
}

int main() {
  GLFWwindow *window = init();
  int foo = 1;
  unsigned int shader_program = create_shader_program_from_files(
      "shaders/simple.vshader", "shaders/orange.fshader");

  /*Vertex data
   */
  float vertices[] = {
      -0.8f, -0.8f, 0.0f, /*Left*/
      -0.2f, -0.8f, 0.0f, /* Right */
      -0.8f, 0.8f,  0.0f, /* Top */
  };
  unsigned int VBO, VAO;
  // Bind Vertex Array Object (VAO)
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // Bind VAO
  glBindVertexArray(VAO);

  // Copy vertices in array to the vertex buffer object (VBO)
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // Finally, set VAO pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Other stuff -- Not sure what this does
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  while (!glfwWindowShouldClose(window)) {
    /* GAME LOOP */

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shader_program);
  glfwDestroyWindow(window);
  glfwTerminate();
  return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>

/* This let's us include in any order.
 */
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad.h>

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

int main() {
  GLFWwindow *window = init();

  while (!glfwWindowShouldClose(window)) {
    /* GAME LOOP */
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return EXIT_SUCCESS;
}

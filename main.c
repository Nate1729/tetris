#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

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

int main() {
  printf("Initializing glfw.\n");
  if (!glfwInit()) {
    fprintf(stderr, "glfw3 initalization failed! Exiting early.\n");
    return EXIT_FAILURE;
  }

  glfwSetErrorCallback(error_callback);

  GLFWwindow *window = glfwCreateWindow(640, 480, "Tetris", NULL, NULL);
  if (!window) {
    fprintf(stderr, "Error, couldn't create window. Exiting Early\n");
    glfwTerminate();
    return EXIT_FAILURE;
  }

  /* Bind callback function for key presses.
   * Must be done _after_ window creation since key
   * presses are bound to a window
   */
  glfwSetKeyCallback(window, key_callback);

  while (!glfwWindowShouldClose(window)) {
    /* GAME LOOP */
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return EXIT_SUCCESS;
}

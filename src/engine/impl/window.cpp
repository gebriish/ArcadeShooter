#include "../window.h"
#include <glad/glad.h>
#include <iostream>

#include "../action_map.h"
#include "../internals/window_internal.h"
#include "../internals/event_internal.h"
#include "../event.h"
#include "../log.h"

static GlfwWindowWrapper g_GlfwWindowWrapper;

void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {\
  Event event = _event_intr_create_key_(key, scancode, action, mods);
  g_GlfwWindowWrapper.eventQueue.push(event);
}

void GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  Event event = _event_intr_create_mouse_button_(button, action, mods);
  g_GlfwWindowWrapper.eventQueue.push(event);
}

void GLFWCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
  static double lastX = xpos, lastY = ypos;
  Event event = _event_intr_create_cursor_move_(xpos, ypos, xpos - lastX, ypos - lastY);
  lastX = xpos;
  lastY = ypos;
  g_GlfwWindowWrapper.eventQueue.push(event);
}

void GLFWScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
  Event event = _event_intr_create_scroll_(xoffset, yoffset);
  g_GlfwWindowWrapper.eventQueue.push(event);
}

void GLFWFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
  Window& w = *(Window*)glfwGetWindowUserPointer(window);
  w.width = width;
  w.height = height;

  _window_intr_set_global_resolution_(width, height);

  Event event = _event_intr_create_resize_(width, height);
  g_GlfwWindowWrapper.eventQueue.push(event);
}

void GLFWCharCallback(GLFWwindow* window, uint32_t codepoint) {
  Event event = _event_intr_create_character_(static_cast<char>(codepoint));
  g_GlfwWindowWrapper.eventQueue.push(event);
}


bool window_initialize(Window& window)
{
  if(g_GlfwWindowWrapper.glfwWindow)
    window_destroy();

  if(!glfwInit())
    return false;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

  glfwWindowHint(GLFW_RESIZABLE, 
      window.flags & WINDOWFLAGS_RESIZABLE   ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_MAXIMIZED, 
      window.flags & WINDOWFLAGS_MAXIMIZED   ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_DECORATED, 
      window.flags & WINDOWFLAGS_UNDECORATED ? GLFW_FALSE : GLFW_TRUE);

  g_GlfwWindowWrapper.glfwWindow = glfwCreateWindow(window.width,
      window.height,
      window.title.c_str(),
      NULL, NULL);

  if (g_GlfwWindowWrapper.glfwWindow == NULL)
  {
    LOG_SVER("Failed to create GLFW Window");
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(g_GlfwWindowWrapper.glfwWindow);

  if(window.flags & WINDOWFLAGS_CENTERED)
  {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwSetWindowPos(g_GlfwWindowWrapper.glfwWindow, 
        (mode->width - window.width)/2,
        (mode->height - window.height)/2);
  }

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {    
    LOG_SVER("Failed to Initialize Glad");
    return false;
  }

  glViewport(0, 0, (GLsizei)window.width, (GLsizei) window.height);
  glfwSwapInterval(window.flags & WINDOWFLAGS_VSYNC ? 1 : 0);

  glfwShowWindow(g_GlfwWindowWrapper.glfwWindow);
  glfwSetWindowUserPointer(g_GlfwWindowWrapper.glfwWindow, &window);

  _window_intr_setup_event_callback_();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  _window_intr_set_global_resolution_(window.width, window.height);

  return true;
}

bool window_should_close() 
{
  if(!g_GlfwWindowWrapper.glfwWindow)
    return true;

  return glfwWindowShouldClose(g_GlfwWindowWrapper.glfwWindow);
}

bool window_event_in_queue(Event& e)
{
  if(g_GlfwWindowWrapper.eventQueue.empty())
    return false;

  e = g_GlfwWindowWrapper.eventQueue.front();
  g_GlfwWindowWrapper.eventQueue.pop();
  return true;
}

void window_swap_buffers()
{
  if(!g_GlfwWindowWrapper.glfwWindow)
    return;
  glfwSwapBuffers(g_GlfwWindowWrapper.glfwWindow);
}

void window_poll_events()
{
  action_update();
  glfwPollEvents();
}

void window_destroy() {
  if(g_GlfwWindowWrapper.glfwWindow) {
    glfwDestroyWindow(g_GlfwWindowWrapper.glfwWindow);
    glfwTerminate();
    g_GlfwWindowWrapper.glfwWindow = nullptr;
  }
}

void window_clear_viewport(float r, float g, float b, float a)
{
  glClearColor(r, g, b, a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void window_resize_region(int x0, int y0, int x1, int y1) {
  glViewport(x0, y0, x1, y1);
}

GLFWwindow* _window_intr_get_glfwWindow(bool &valid)
{
  if(g_GlfwWindowWrapper.glfwWindow)
  {
    valid = true;
    return g_GlfwWindowWrapper.glfwWindow;
  }
  else
  {
    valid = false;
    return nullptr;
  }
}

GLFWwindow* _window_intr_get_glfw_window(bool &valid)
{
  valid = (g_GlfwWindowWrapper.glfwWindow != nullptr);
  return g_GlfwWindowWrapper.glfwWindow;
}

void _window_intr_setup_event_callback_()
{
  glfwSetKeyCallback(g_GlfwWindowWrapper.glfwWindow, GLFWKeyCallback);
  glfwSetMouseButtonCallback(g_GlfwWindowWrapper.glfwWindow, GLFWMouseButtonCallback);
  glfwSetCursorPosCallback(g_GlfwWindowWrapper.glfwWindow, GLFWCursorPosCallback);
  glfwSetScrollCallback(g_GlfwWindowWrapper.glfwWindow, GLFWScrollCallback);
  glfwSetFramebufferSizeCallback(g_GlfwWindowWrapper.glfwWindow, GLFWFramebufferSizeCallback);
  glfwSetCharCallback(g_GlfwWindowWrapper.glfwWindow, GLFWCharCallback);
}

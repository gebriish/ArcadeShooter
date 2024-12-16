#include "application.h"


Application::Application()
{
  m_Window.width = 640;
  m_Window.height = 400;
  m_Window.title = "arcade shooter";
  m_Window.flags  = WINDOWFLAGS_VSYNC | WINDOWFLAGS_RESIZABLE | WINDOWFLAGS_CENTERED;

  if(!window_initialize(m_Window)) {
    ERROR_EXIT("Failed to initialize window");
  }
}

void Application::update(f32 deltaTime)
{
  Event e;

  static f32 x_pos = -1, z_pos = -1;

  while(window_event_in_queue(e))
  {
  }
}

void Application::render()
{
}

Application::~Application()
{
}

void Application::run()
{
  while (!window_should_close())
  {
    time_begin();

    update(time_get_deltatime());

    window_clear_viewport(0, 0, 0, 1);
    render();

    window_swap_buffers();
    window_poll_events();
  }
}

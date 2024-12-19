#include <glad/glad.h>

#include "application.h"
#include "engine/global.h"
#include "engine/shader.h"
#include "engine/line_batch.h"
#include "engine/input.h"
#include "engine/transform.h"
#include "engine/action_map.h"

float radius = 2.0f, target_radius = 2.0f;
LineBatch3D* lineBatch;
Shader lineShader;
Transform player_transform;
Transform cam_anc_transform;
Transform cam_transform;
vec3 euRotations, smoothEuRotations;
bool cursorDisabled = true;
Camera& camera = global_camera();

vec3 playerVelocity (0.0f);

Application::Application()
{
  m_Window.width = 1000;
  m_Window.height = 625;
  m_Window.title = "Arcade Shooter";
  m_Window.flags  = WINDOWFLAGS_CENTERED | WINDOWFLAGS_RESIZABLE | WINDOWFLAGS_VSYNC;

  if(!window_initialize(m_Window)) {
    ERROR_EXIT("Failed to initialize window");
  }
  camera.proj = mat4::perspective(degrees_to_radians(90), global_aspect_ratio(), 0.001f, 1000.0f);

  lineBatch = new LineBatch3D(512);
  shader_load_glsl("res/line.vert", "res/line.frag", lineShader);

  input_set_cursor_mode(CursorMode::DISABLED);

  cam_transform.position = vec3(0.0, 0.0f, radius);
  cam_anc_transform.position = vec3(0.0f, 0.75f, 0.0f);
  player_transform.position = vec3(10, 5.0, 10);
  cam_transform.SetParent(&cam_anc_transform);
  cam_anc_transform.SetParent(&player_transform);

  action_bind_key("forward", KEY_W);
  action_bind_key("right", KEY_D);
  action_bind_key("backward", KEY_S);
  action_bind_key("left", KEY_A);
  action_bind_key("jump", KEY_SPACE);
}

void Application::update(float deltaTime)
{
  Event e;

  while(window_event_in_queue(e))
  {
    if(e.type == EventType::CURSOR)
    {
      euRotations.y -= e.cursorMoveData.Dx * 0.1f;
      euRotations.x -= e.cursorMoveData.Dy * 0.1f;
      euRotations.x = clamp(-89.9, 89.9, euRotations.x);
    }
    else if(e.type == EventType::RESIZE)
    {
      window_resize_region(0, 0, e.resizeData.width, e.resizeData.height);
      camera.proj = mat4::perspective(degrees_to_radians(90), global_aspect_ratio(), 0.001f, 1000.0f);
    }
    else if(e.type == EventType::KEY)
    {
      switch (e.keyData.key)
      {
        case KEY_ESCAPE:
          if(e.keyData.action == ActionCode::PRESS) {
            cursorDisabled = !cursorDisabled;
            input_set_cursor_mode(cursorDisabled ? CursorMode::DISABLED : CursorMode::NORMAL);
          }
        break;
      }
    }
  }

  smoothEuRotations = smoothEuRotations.lerp(euRotations, 20 * deltaTime);

  cam_anc_transform.SetRotationFromEuler(vec3(smoothEuRotations.x, 0.0, smoothEuRotations.z));
  player_transform.SetRotationFromEuler(vec3(0.0, smoothEuRotations.y, 0.0));

  playerVelocity.x = 0.0;
  playerVelocity.z = 0.0;

  if(player_transform.position.y <= 1.0f)
  {
    player_transform.position.y = 1.0f;
    playerVelocity.y = 0.0;
  }
  else
  {
    playerVelocity.y -= deltaTime * 9.8f;
  }

  if(input_is_key_pressed(KEY_TAB))
    target_radius = 2.0f;
  else
    target_radius = 0.0f; 

  radius = lerp(radius, target_radius, 15 * deltaTime);

  cam_transform.position.z = radius;

  if(action_is_pressed("forward") && !action_is_pressed("backward"))
    playerVelocity += player_transform.forward();
  if(!action_is_pressed("forward") && action_is_pressed("backward"))
    playerVelocity -= player_transform.forward();
  
  if(action_is_pressed("right") && !action_is_pressed("left"))
    playerVelocity += player_transform.right();
  if(!action_is_pressed("right") && action_is_pressed("left"))
    playerVelocity -= player_transform.right();
  
  if(action_is_just_pressed("jump"))
    playerVelocity.y = 2.0f;

  playerVelocity.normalize();
  player_transform.position += playerVelocity * 5.0 * deltaTime;

  camera.view = mat4::lookAt(cam_transform.GetGlobalPosition(), cam_transform.GetGlobalPosition() + cam_transform.forward(), cam_transform.up()); 
}

void addLine(LineBatch3D &batch, const Line3D& line)
{
  if(!batch.AddLine(line))
  {
    batch.DrawBatch();
    batch.Begin();
    batch.AddLine(line);
  }
}

void addAABB(LineBatch3D &batch, const vec3& pos, const vec3& halfSize, const vec3& color)
{
  addLine(batch, Line3D{pos - halfSize, pos - vec3(-halfSize.x, halfSize.y, halfSize.z), color});
  addLine(batch, Line3D{pos - vec3(-halfSize.x, halfSize.y, halfSize.z), pos - vec3(-halfSize.x, halfSize.y, -halfSize.z), color});
  addLine(batch, Line3D{pos - vec3(-halfSize.x, halfSize.y, -halfSize.z), pos - vec3(halfSize.x, halfSize.y, -halfSize.z), color});
  addLine(batch, Line3D{pos - vec3( halfSize.x, halfSize.y, -halfSize.z), pos - halfSize, color});

  addLine(batch, Line3D{pos + halfSize, pos + vec3(-halfSize.x, halfSize.y, halfSize.z), color});
  addLine(batch, Line3D{pos + vec3(-halfSize.x, halfSize.y, halfSize.z), pos  + vec3(-halfSize.x, halfSize.y, -halfSize.z), color});
  addLine(batch, Line3D{pos + vec3(-halfSize.x, halfSize.y, -halfSize.z), pos + vec3(halfSize.x, halfSize.y, -halfSize.z), color});
  addLine(batch, Line3D{pos + vec3( halfSize.x, halfSize.y, -halfSize.z), pos + halfSize, color});

  addLine(batch, Line3D{pos + vec3(-halfSize.x, -halfSize.y, -halfSize.z), pos + vec3(-halfSize.x,  halfSize.y, -halfSize.z), color});
  addLine(batch, Line3D{pos + vec3( halfSize.x, -halfSize.y, -halfSize.z), pos + vec3( halfSize.x,  halfSize.y, -halfSize.z), color});
  addLine(batch, Line3D{pos + vec3( halfSize.x, -halfSize.y,  halfSize.z), pos + vec3( halfSize.x,  halfSize.y,  halfSize.z), color});
  addLine(batch, Line3D{pos + vec3(-halfSize.x, -halfSize.y,  halfSize.z), pos + vec3(-halfSize.x,  halfSize.y,  halfSize.z), color});
}

void Application::render()
{
  shader_use_program(lineShader);

  shader_upload_vec3(lineShader, "uCamPos", player_transform.position.x, player_transform.position.y, player_transform.position.z);
  shader_upload_mat4(lineShader, "uProj", camera.proj.elements);
  shader_upload_mat4(lineShader, "uView", camera.view.elements);

  lineBatch->Begin();
  for(int i=0; i<32; i++)
  {
    Line3D l;
    l.begin = vec3(i, 0, 0);
    l.end = vec3(i, 0, 31);
    l.color = vec3(1.0);
    addLine(*lineBatch, l);

    l.begin = vec3(0, 0,i);
    l.end = vec3(31, 0, i);
    addLine(*lineBatch, l);
  }  

  addAABB(*lineBatch, player_transform.position, vec3(0.25, 1.0, 0.25), vec3(171/255.0f, 221/255.0f, 100/255.0f));

  lineBatch->End();

  lineBatch->DrawBatch();

}

Application::~Application()
{
  shader_delete_program(lineShader);
  delete lineBatch;
}

void Application::run()
{
  while (!window_should_close())
  {
    time_begin();

    update(time_get_deltatime());

    Color bg = color_from_hexcode("4a3052");
    float r = bg.r/255.0;
    float g = bg.g/255.0;
    float b = bg.b/255.0;

    window_clear_viewport(r, g, b, 1);
    render();

    window_swap_buffers();
    window_poll_events();
  }
}

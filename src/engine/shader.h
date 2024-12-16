#pragma once
#include "color.h"

#include "types.h"

struct Shader {
  unsigned int ID;
};

void shader_load_glsl_from_source(const char* vertex_source, 
    const char* fragment_source, Shader& program);

void shader_load_glsl(const char* vertexPath, 
    const char* fragmentPath, Shader& program);

void shader_use_program(const Shader& program);
void shader_delete_program(const Shader& program);

void shader_upload_int(const Shader& program, 
    const char* name, i32 v);

void shader_upload_float(const Shader& program, 
    const char* name, f32 v);

void shader_upload_vec2(const Shader& program, 
    const char* name, f32 x, f32 y);

void shader_upload_vec3(const Shader& program, 
    const char* name, f32 x, f32 y, f32 z);

void shader_upload_vec4(const Shader& program, 
    const char* name, f32 x, f32 y, f32 z, f32 w);

void shader_upload_color(const Shader& program,
    const char* name, const Color& color);

void shader_upload_float_array(const Shader& program, 
    const char* name, 
    const f32* array, unsigned int size);


void shader_upload_mat4(const Shader& program, 
    const char* name, const float* mat);

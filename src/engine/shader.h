#pragma once
#include "color.h"

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
    const char* name, int v);

void shader_upload_float(const Shader& program, 
    const char* name, float v);

void shader_upload_vec2(const Shader& program, 
    const char* name, float x, float y);

void shader_upload_vec3(const Shader& program, 
    const char* name, float x, float y, float z);

void shader_upload_vec4(const Shader& program, 
    const char* name, float x, float y, float z, float w);

void shader_upload_color(const Shader& program,
    const char* name, const Color& color);

void shader_upload_float_array(const Shader& program, 
    const char* name, 
    const float* array, unsigned int size);

void shader_upload_mat4(const Shader& program,   
    const char* name, const float* mat);

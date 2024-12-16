#pragma once
#include <string>
#include "types.h"

void action_bind_key(const std::string& name, i32 key);
void action_clear_bindings();

bool action_is_pressed(const std::string& name);
bool action_is_just_pressed(const std::string& name);
bool action_is_just_released(const std::string& name);

void action_update();

#include "../action_map.h"
#include "../internals/action_map_internal.h"

static ActionMap g_ActionMap;

void action_bind_key(const std::string& name, int key)
{
	g_ActionMap.map[name].keys.insert(key);
}

void action_clear_bindings()
{	
	g_ActionMap.map.clear();
}	

bool action_is_pressed(const std::string& name)
{
	auto it = g_ActionMap.map.find(name);
	if(it != g_ActionMap.map.end()) {
		return it->second.curr_status;
	}

	return false;
}

bool action_is_just_pressed(const std::string& name)
{
	auto it = g_ActionMap.map.find(name);
	if(it != g_ActionMap.map.end()) {
		const Action& action = it->second;
		return action.curr_status && !action.prev_status;
	}
	return false;
}

bool action_is_just_released(const std::string& name)
{
	auto it = g_ActionMap.map.find(name);
	if(it != g_ActionMap.map.end()) {
		const Action& action = it->second;
		return !action.curr_status && action.prev_status;
	}
	return false;
}


void action_update()
{
	for(auto& [name, action] : g_ActionMap.map) {
		bool pressed = false;
		for(int key : action.keys) {
			if(input_is_key_pressed(key))
			{
				pressed = true;
				break;
			}
		}

		action.prev_status = action.curr_status;
		action.curr_status = pressed;
	}
}

#pragma once
#include <unordered_set>
#include <unordered_map>
#include <string>

#include "../input.h"

struct Action
{
	std::unordered_set<int> keys;
	bool prev_status = false;
	bool curr_status = false;
};

struct ActionMap
{
	std::unordered_map<std::string, Action> map;
};

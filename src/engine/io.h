#pragma once
#include <string>
#include <vector>

struct TxtFile
{
	std::string content;
	bool valid;
};

TxtFile io_load_txt_file(const char* filePath);
bool io_load_txt_file_lines(const char* filePath, std::vector<std::string>& lines);
void io_write_txt_file(const char* filePath, const std::string& content);

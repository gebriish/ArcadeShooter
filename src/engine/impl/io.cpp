#include "../io.h"
#include "../log.h"

#include <fstream>
#include <sstream>
#include <iostream>

TxtFile io_load_txt_file(const char* filePath) {
    TxtFile load_file;
    load_file.content = "";

    std::ifstream file(filePath);
    if (!file) {
        load_file.valid = false;
		LOG_SVER("IO Error: unable to open file: %s\n", filePath);
        return load_file;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    load_file.content = buffer.str();
    load_file.valid = true;

    return load_file;
}

bool io_load_txt_file_lines(const char* filePath, std::vector<std::string>& lines)
{
    if(!lines.empty())
        lines.clear();

    std::ifstream input_stream(filePath);
    if(!input_stream.is_open())
    {
        LOG_SVER("IO Error: unable to open file: %s\n", filePath);
        return false;
    }

    std::string word;
    while(std::getline(input_stream, word))
    {
        lines.push_back(word);
    }

    input_stream.close();
    return true;
}

void io_write_txt_file(const char* filePath, const std::string& content) {
    std::ofstream file(filePath);
    if (!file) {
		LOG_SVER("IO Error: could not open file for writing: %s\n", filePath);
        return;
    }

    file << content;
    if (!file) {
		LOG_SVER("IO Error: writing to file failed: %s\n", filePath);
    }

    file.close();
}

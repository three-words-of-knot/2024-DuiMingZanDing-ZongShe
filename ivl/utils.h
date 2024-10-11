#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <string>
std::string stringf(const char* fmt, ...);
std::string join_label_pieces(std::vector<std::string> pieces);
#endif
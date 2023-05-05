#include <fstream>

std::string stream_as_string(std::istream &stm) {
    std::string str;
    char c;
    while (stm.get(c))
        str += c;
    return str;
}
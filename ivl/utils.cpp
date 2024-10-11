#include "utils.h"
#include <stdio.h>
#include <stdarg.h>


inline std::string vstringf(const char* fmt, va_list ap)
{
    // For the common case of strings shorter than 128, save a heap
    // allocation by using a stack allocated buffer.
    const int kBufSize = 128;
    char buf[kBufSize];
    buf[0] = '\0';
    va_list apc;
    va_copy(apc, ap);
    int n = vsnprintf(buf, kBufSize, fmt, apc);
    va_end(apc);
    if (n < kBufSize)
        return std::string(buf);

    std::string string;
    char* str = NULL;
#if defined(_WIN32 )|| defined(__CYGWIN__)
    int sz = 2 * kBufSize, rc;
    while (1) {
        va_copy(apc, ap);
        str = (char*)realloc(str, sz);
        rc = vsnprintf(str, sz, fmt, apc);
        va_end(apc);
        if (rc >= 0 && rc < sz)
            break;
        sz *= 2;
    }
    if (str != NULL) {
        string = str;
        free(str);
    }
    return string;
#else
    if (vasprintf(&str, fmt, ap) < 0)
        str = NULL;
    if (str != NULL) {
        string = str;
        free(str);
    }
    return string;
#endif
}

std::string stringf(const char* fmt, ...)
{
    std::string string;
    va_list ap;

    va_start(ap, fmt);
    string = vstringf(fmt, ap);
    va_end(ap);

    return string;
}


// Return the pieces of a label joined by a '|' separator
std::string join_label_pieces(std::vector<std::string> pieces)
{
    std::string ret = "";
    bool first_piece = true;

    for (auto& piece : pieces) {
        if (!first_piece)
            ret += "|";
        ret += piece;
        first_piece = false;
    }

    return ret;
}
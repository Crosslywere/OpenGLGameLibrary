#pragma once

#ifdef DEBUG
#include <cstdio>
#define DEBUG_MSG(fmt, ...) std::printf(fmt, __VA_ARGS__)
#else
#define DEBUG_MSG(fmt, ...)
#endif
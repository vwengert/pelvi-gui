#pragma once

#if defined(_WIN32) || defined(_WIN64)
#if defined(BUILD_SHARED_LIB)
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT __declspec(dllimport)
#endif
#else
#define EXPORT
#endif

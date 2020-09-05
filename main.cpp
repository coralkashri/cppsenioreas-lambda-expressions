#include <iostream>

#if __cplusplus <= 201103L // C++11

#elif __cplusplus > 201103L && __cplusplus <= 201402L // C++14

#elif __cplusplus > 201402L && __cplusplus <= 201703L // C++17

#else // C++20

#endif

int main() {

#if __cplusplus <= 201103L // C++11

#elif __cplusplus > 201103L && __cplusplus <= 201402L // C++14

#elif __cplusplus > 201402L && __cplusplus <= 201703L // C++17

#else // C++20

#endif

    return EXIT_SUCCESS;
}
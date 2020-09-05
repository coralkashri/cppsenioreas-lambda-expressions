#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>

#if __cplusplus <= 201103L // C++11

class my_class {
public:
    void create_thread() {
        std::thread t(my_thread_function, std::ref(*this));
        t.join();
    }

    void create_thread_2() {
        std::thread t([this]() {
            std::cout << this->my_int << std::endl;
        });
        t.join();
    }

    void create_thread_3() {
        std::thread t([this]() {
            this->non_static_function();
        });
        t.join();
    }

private:
    int my_int;

    static void my_thread_function(my_class& mc) { // This function has to be a static function in order to used as a thread function.
        std::cout << mc.my_int << std::endl; // In order to access a class member variable, we have to accept a class reference as a function argument.
    }

    void non_static_function() const {
        std::cout << my_int << std::endl;
    }
};

#elif __cplusplus > 201103L && __cplusplus <= 201402L // C++14

#elif __cplusplus > 201402L && __cplusplus <= 201703L // C++17

#else // C++20

#endif

void thread_function(int a, int b) { std::cout << a + b << std::endl; }

int main() {

#if __cplusplus <= 201103L // C++11

    #define EXAMPLE_4

    #ifdef EXAMPLE_0
    [ /* capture */ ] ( /* params */ ) /* specifiers */ /* exceptions */ -> void /* return */ {
        /* body */
    };
    auto sum = [](int a, int b) [[]] -> int {
        return a + b;
    };
    #endif
    #ifdef EXAMPLE_1
    std::thread t(thread_function, 3, 5);
    t.join();
    #endif
    #ifdef EXAMPLE_2
    std::vector<int> vec = {1, 2, 3};
    std::for_each(vec.begin(), vec.end(), [](int &elem) {
        elem *= elem;
    });

    std::for_each(vec.begin(), vec.end(), [](int &elem) {
        std::cout << elem << " ";
    });
    std::cout << std::endl;
    #endif
    #ifdef EXAMPLE_3
    int a, b;
    a = 1; b = 2;
    auto lambda_1 = [=] { std::cout << a << " " << b << std::endl; };
    auto lambda_2 = [&] { std::cout << a << " " << b << std::endl; };
    lambda_1();
    lambda_2();
    a = 4; b = 5;
    lambda_1();
    lambda_2();
    #endif
    #ifdef EXAMPLE_4
    int a = 4;
    auto increase_local_a = [a]() mutable {
        std::cout << a << std::endl;
        a++;
    };
    auto decrease_ref_a = [&a]() mutable {
        std::cout << a << std::endl;
        a--;
    };
    increase_local_a(); // Prints: 4
    decrease_ref_a(); // Prints: 4
    increase_local_a(); // Prints: 5
    decrease_ref_a(); // Prints: 3
    increase_local_a(); // Prints: 6
    decrease_ref_a(); // Prints: 2
    std::cout << a << std::endl; // Prints: 1
    #endif

#elif __cplusplus > 201103L && __cplusplus <= 201402L // C++14

#elif __cplusplus > 201402L && __cplusplus <= 201703L // C++17

#else // C++20

#endif

    return EXIT_SUCCESS;
}
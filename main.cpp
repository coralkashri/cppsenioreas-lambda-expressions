#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <type_traits>

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
template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

template <typename T>
concept PlusOperator = requires(T type) {
    { type + type };
};
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
    #define EXAMPLE_2

    #ifdef EXAMPLE_1
    auto lambda = [](auto a, auto b) {
        return a + b;
    };

    lambda(1, 2.4); // int, double
    lambda(5.f, 3); // float, int
    #endif
    #ifdef EXAMPLE_2
    int a = 4, k = 7;
    auto lambda = [&b = a, k = a]() mutable {
        b++;
        std::cout << k << std::endl; // Prints: 4
    };
    lambda();
    std::cout << a << std::endl; // Prints: 5
    #endif
#elif __cplusplus > 201402L && __cplusplus <= 201703L // C++17
    struct my_struct {
        my_struct() {}
        my_struct(const my_struct &) { std::cout << "Copy" << std::endl; } // Called during this->func();
        void func() {
            [*this]() { // call copy constructor
            };
            [this] { // doesn't call copy constructor
            };
        }
    };
    my_struct ms;
    ms.func();
#else // C++20
    #define EXAMPLE_3

    #ifdef EXAMPLE_1
    auto sum = [] <typename T, Numeric U> (T num1, U num2) requires ( std::is_arithmetic_v<T> ) {
        return num1 + num2;
    };
    std::cout << sum(3.2, 5) << std::endl;
    #endif
    #ifdef EXAMPLE_2
    using namespace std::string_literals;

    auto plus = [] <typename T> (T arg1, T arg2) {
        return arg1 + arg2;
    };
    std::cout << plus("Hello "s, "World"s) << std::endl;
    #endif
    #ifdef EXAMPLE_3
    using namespace std::string_literals;

    auto plus = [] <PlusOperator T, PlusOperator ...Args> (T first, Args ...args) requires ( std::is_same_v<T, Args> && ... ) {
        return (first + ... + args);
    };
    std::cout << plus(1) << std::endl; // Prints: 1
    std::cout << plus(1, 4, 5) << std::endl; // Prints: 10
    std::cout << plus(2.3, 4.5, 5.6) << std::endl; // Prints: 12.4
    std::cout << plus("Template"s, " "s, "Lambda"s, " "s, "Expression"s) << std::endl; // Prints: Template Lambda Expression
    #endif
    #ifdef EXAMPLE_4
    #endif
#endif

    return EXIT_SUCCESS;
}
#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <type_traits>

// Example #
#define EXAMPLE_3



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

#ifdef EXAMPLE_4
class __lambda_4_16 {
public:
    template<class type_parameter_0_0, class type_parameter_0_1>
    inline auto operator()(type_parameter_0_0 a, type_parameter_0_1 b) const {
        return a + b;
    }

    // template<> // C++ doesn't allow explicit specialization in non-namespace scope. This workaround suggested by @bop on StackOverflow: https://stackoverflow.com/a/13018943/8038186
    inline double operator()(int a, double b) const {
        return static_cast<double>(a) + b;
    }


    // template<> // C++ doesn't allow explicit specialization in non-namespace scope. This workaround suggested by @bop on StackOverflow: https://stackoverflow.com/a/13018943/8038186
    inline float operator()(float a, int b) const {
        return a + static_cast<float>(b);
    }

private:
    template<class type_parameter_0_0, class type_parameter_0_1>
    static inline auto __invoke(type_parameter_0_0 a, type_parameter_0_1 b) {
        return a + b;
    }

public:
    inline constexpr __lambda_4_16(__lambda_4_16 &&) noexcept = default;
};
#endif

#ifdef EXAMPLE_5
#endif

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
    #ifdef EXAMPLE_5
    int a = 5;

    class __lambda_5_17 {
    public:
        inline int operator()(int n1, int n2) const {
            return a * (n1 + n2);
        }

    private:
        int &a;

    public:
        inline __lambda_5_17(const __lambda_5_17 &ref) noexcept : a(ref.a) {
            std::cout << "Copy CTOR" << std::endl;
        }

        inline __lambda_5_17(__lambda_5_17 && ref) noexcept : a(ref.a) {
            std::cout << "Move CTOR" << std::endl;
        };

        __lambda_5_17(int &_a) : a{_a} {
            std::cout << "Parametrize CTOR" << std::endl;
        }
    };

    __lambda_5_17 lambda = __lambda_5_17(__lambda_5_17{a});
    auto aaa = std::move(lambda);
    auto bbb = aaa;
    std::cout << aaa.operator()(5, 6) << std::endl;
    a++;
    std::cout << aaa.operator()(5, 6) << std::endl;
    std::cout << bbb.operator()(5, 6) << std::endl;
    #endif
    #ifdef EXAMPLE_6
    class __lambda_4_17 {
    public:
        inline int operator()(int n1, int n2) const {
            return n1 + n2;
        }

        using retType_4_17 = int (*)(int, int);

        inline operator retType_4_17() const noexcept {
            return __invoke;
        }

    private:
        static inline int __invoke(int n1, int n2) {
            return n1 + n2;
        }

    public:
        inline constexpr __lambda_4_17(const __lambda_4_17 &) noexcept = default;

        inline constexpr __lambda_4_17(__lambda_4_17 &&) noexcept = default;
    };

    __lambda_4_17 lambda = __lambda_4_17(__lambda_4_17{});
    __lambda_4_17 moved_lambda = __lambda_4_17(std::move(lambda));
    __lambda_4_17 copied_lambda = __lambda_4_17(moved_lambda);
    using FuncPtr_9 = int (*)(int, int);
    FuncPtr_9 direct_func = static_cast<int (*)(int, int)>(copied_lambda.operator __lambda_4_17::retType_4_17());

    // lambda(5, 6); // Usage of moved object may lead to UB
    moved_lambda(5, 6);
    copied_lambda(5, 6);
    direct_func(5, 6);
    #endif
    #ifdef EXAMPLE_7
    int number = 4;

    class __lambda_5_16 {
    public:
        inline int operator()(int n) const {
            return number + n;
        }

    private:
        int &number;
    public:
        inline constexpr __lambda_5_16(__lambda_5_16 &&) noexcept = default;
        __lambda_5_16(int &_number) : number{_number} {}
    };

    __lambda_5_16 lambda = __lambda_5_16(__lambda_5_16{number});
    // int (*func)(int) = lambda; // Won't compile - no visible conversion
    #endif
    #ifdef EXAMPLE_8
    int number1, number2;
    number1 = 1; number2 = 2;
    [number1, &number2]() mutable {
        number1++;
        number2++;
        return number1 * number2;
    }();

    class A {
        int n1;
        int &n2;
        int *n3;
        A () : n2(n1), n3(&n1) {}

        void func() const {
            //n1++;
            n2++; // OK
            //n3++;
            (*n3)++; // OK
        }
    };

    #endif
#elif __cplusplus > 201103L && __cplusplus <= 201402L // C++14
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
    #ifdef EXAMPLE_3
    // generic lambda, operator() is a template with one parameter
    auto vglambda = [](auto printer) {
        return [=](auto &&... ts) { // generic lambda, ts is a parameter pack
            printer(std::forward<decltype(ts)>(ts)...);
        };
    };
    auto triple_printer = vglambda([](auto v1, auto v2, auto v3) { std::cout << v1 << v2 << v3; });
    triple_printer(1, 'a', 3.14); // outputs 1a3.14
    #endif
    #ifdef EXAMPLE_4
    __lambda_4_16 lambda = __lambda_4_16(__lambda_4_16{});
    lambda.operator()(1, 2.3999999999999999);
    lambda.operator()(5.0F, 3);
    #endif
    #ifdef EXAMPLE_5
    #endif
#elif __cplusplus > 201402L && __cplusplus <= 201703L // C++17
    #ifdef EXAMPLE_1
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
    #endif
    #ifdef EXAMPLE_2
    class lambda_7_3
    {
    public:
        [[nodiscard]] inline int operator()() const
        {
            std::cout << "A" << std::endl;
            return 5;
        }

        using retType_7_3 = int (*)();
        [[nodiscard]] inline constexpr operator retType_7_3 () const noexcept
        {
            return invoke;
        };

    private:
        static inline int invoke()
        {
            std::cout << "B" << std::endl;
            return 5;
        }
    };

    lambda_7_3 a;
    a();
    auto c = a;
    int (*b)() = a;
    b();
    c();
    #endif
    #ifdef EXAMPLE_3
    auto Fwd = [](int(*fp)(int), auto a) { return fp(a); };
    auto C   = [](auto a) { return a; };
    static_assert(Fwd(C, 3) == 3); // OK

    auto NC = [](auto a) { static int s; return a; };
    // static_assert(Fwd(NC, 3) == 3); // Won't compile
    #endif
#else // C++20
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
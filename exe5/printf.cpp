#include <iostream>

// Exercise 1: Create a simple variadic template function 
// that returns the sum of all input parameters.
// The base case: we just have a single number.
template <typename T>
double sum(T t) {  // base function
    return t;
}
// The recursive case: we take a number, alongside
// some other numbers, and produce their sum.
template <typename T, typename... Rest>
double sum(T t, Rest... rest) { // recursive variadic function
    return t + sum(rest...);
}

// Exercise 2: Printf using compile time if. 
void ya_printf(const char* s) // base function
{
    std::cout << s;
}
template<typename T, typename... Args>
void ya_printf(const char *s, T value, Args... args) // recursive variadic function
{
    for ( ; *s != '\0'; s++ ) {
        if ( *s == '%' ) {
            std::cout << value;
            if constexpr(sizeof...(args) > 0 ) {
                ya_printf(s+1, args...); // recursive call
            }
            return;
        }
        std::cout << *s;
    }
}

int main(){
    // Exercise1 test
    std::cout << sum(2,5,62.5,0) << std::endl;
    
    // Exercise2 test
    ya_printf("Hello world % lala %", 42, 43);
    return 0;
}

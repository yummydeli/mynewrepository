//#include <iostream>
//
//int main() {
//    std::cout << "Hello, World!" << std::endl;
//    return 0;
//}
#include <cassert>
#include <type_traits>
template <typename T>
void lyxnb(T v)
{
    static_assert(std::is_same<T, int>::value, "T is not int !!!");
}

int main()
{
    lyxnb(1.);
}
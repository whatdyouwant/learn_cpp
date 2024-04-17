#include <functional>
#include <iostream>

void f(int& n1, int& n2, const int& n3)
{
    std::cout << "函数中: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    ++n1; // 增加存储于函数对象的 n1 副本
    ++n2; // 增加 main() 的 n2
    // ++n3; // 编译错误
}

int main()
{
    int n1 = 1, n2 = 2, n3 = 3;
    std::function<void()> bound_f = std::bind(f, n1, std::ref(n2), std::cref(n3));
    n1 = 10;
    n2 = 11;
    n3 = 12;
    std::cout << "函数前: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    bound_f();
    std::cout << "函数后: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
}
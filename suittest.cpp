#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <cwchar>

int main() {
#ifdef _WIN32
    _setmode(_fileno(stdout), _O_U16TEXT);
#endif
    std::wcout << L'\u2660' << std::endl;
    std::wcout << L'\u2665' << std::endl;
    std::wcout << L'\u2666' << std::endl;
    std::wcout << L'\u2663' << std::endl;
    return 0;
}

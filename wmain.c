// wmain.c
//   Define a virtual entry point for this app.

#include <stdio.h>
#include <wchar.h>
#include <locale.h>

// wmain()
int wmain(int argc, wchar_t* args[]) {
    // Set locale for wprintf().
    setlocale(LC_ALL, "");
    for (int i = 0; i < argc; i++) {
        wprintf(L"[%d] %ls: %d\n",
            i, args[i], wcslen(args[i]));
    }
    return 0;
}

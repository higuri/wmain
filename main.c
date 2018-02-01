// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

// array_remove()
static int array_remove(void** buf, int i, int c) {
    for (int j = i; j < c; j++) {
        if (j+1 < c) {
            buf[j] = buf[j+1];
        }
    }
    return (c-1);
}

// free_wargs()
static void free_wargs(
    int wargc, wchar_t** wargs) {
    for (int i = 0; i < wargc; i++) {
        if (wargs[i] != NULL) {
            free(wargs[i]);
            wargs[i] = NULL;
        }
    }
    free(wargs);
    return;
}

// alloc_wargs()
static wchar_t** alloc_wargs(
    int argc, char* args[]) {
    wchar_t** wargs =
        (wchar_t**)calloc(argc, sizeof(wchar_t*));
    for (int i = 0; i < argc; i++) {
        char* mbs = args[i];
        // Get the length for wide characters.
        size_t wcslen = mbstowcs(NULL, mbs, 0);
        if (wcslen == (size_t)-1) {
            free_wargs(argc, wargs);
            return NULL;
        }
        // Allocate mbs to wcs.
        wargs[i] = (wchar_t*)calloc(wcslen+1, sizeof(wchar_t));
        size_t ret = mbstowcs(wargs[i], mbs, wcslen+1);
        if (ret == (size_t)-1) {
            free_wargs(argc, wargs);
            return NULL;
        }
    }
    return wargs;
}

// alloc_wargs_with_locale()
static wchar_t** alloc_wargs_with_locale(
    int argc, char* args[], char* localeID) {
    char* old_locale = (char*)strdup(setlocale(LC_ALL, NULL));
    if (old_locale == NULL) {
        wprintf(L"Error: Getting current locale failed.");
        return NULL;
    }
    if (setlocale(LC_ALL, localeID) == NULL) {
        wprintf(L"Error: Invalid locale ID for this environment.\n");
        wprintf(L"| Can't set %hs to LC_ALL.\n", localeID);
        wprintf(L"| Check `locale -a` whether specified locale ID is available in this environment.\n");
        return NULL;
    }
    wchar_t** wargs = alloc_wargs(argc, args);
    setlocale(LC_ALL, old_locale);
    free(old_locale);
    return wargs;
}

// main()
extern int wmain(int, wchar_t**);
int main(int argc, char* args[]) {
    // Check locale option (-L).
    char* localeID = "";
    for (int i = 0; i < argc; i++) {
        char* arg = args[i];
        if (strcmp(arg, "-L") == 0) {
            argc = array_remove((void**)args, i, argc);
            if (i < argc) {
                localeID = args[i];
                argc = array_remove((void**)args, i, argc);
            }
        }
    }
    wchar_t** wargs = alloc_wargs_with_locale(argc, args, localeID);
    if (wargs == NULL) {
        wprintf(L"Error: Type Conversion Failed (char -> wchar_t).\n");
        wprintf(L"| Incorrect locale for command line arguments.\n");
        wprintf(L"| - Make sure that current locale is correct for command line encoding.\n");
        for (int i = 0; i < argc; i++) {
            wprintf(L"| args[%d]: ", i);
            char* arg = args[i];
            for(int j = 0; arg[j] != '\0'; j++){
                wprintf(L"0x%02X ", arg[j] & 0x000000FF);
            }
            wprintf(L"\n");
        }
        return -1;
    }
    int retval = wmain(argc, wargs);
    free_wargs(argc, wargs);
    return retval;
}

//
// wmain()
//
int wmain(int argc, wchar_t* args[]) {
    for (int i = 0; i < argc; i++) {
      wprintf(L"Length[%d]: %d\n", i, wcslen(args[i]));
    }
    return 0;
}

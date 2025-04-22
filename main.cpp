#include <iostream>
#include <cstdlib>

volatile int stack_size = 0;

void cause_stack_overflow() {
    volatile char buffer[4*1024];
    stack_size += 4*1024;
    buffer[0] = stack_size / 4*1024; 
    cause_stack_overflow();
    buffer[4*1024 - 1] = stack_size / 4*1024; 
}


#if defined(_WIN32) && defined(_MSC_VER)
    #include <windows.h>
    // MSVC — use SEH

    int main() {
        char stack_fence[4*1024];
        (void)stack_fence;

        __try {
            cause_stack_overflow();
        } __except(EXCEPTION_EXECUTE_HANDLER) {
            std::cout << "Caught structured exception (stack overflow)\n";
            std::cout << "Stack size estimated: " << stack_size / 1024 << "KB\n";
            return 0;
        }
    }
        
#else
    // Linux / macOS — GCC or Clang and MinGW (GCC on Windows) — use signal
    #include <csignal>
    #include <unistd.h>
    #include <execinfo.h>
    #include <cstdlib>

    void handler(int signum) {
        std::cout << "Caught signal " << signum << ": Stack overflow detected!\n";
        std::cout << "Stack size estimated: " << stack_size / 1024 << "KB\n";
        _exit(0);
    }

    int main() {
        char stack_fence[4*1024];
        (void)stack_fence;

        struct sigaction sa;
        sa.sa_handler = handler;
        sa.sa_flags = SA_SIGINFO; 
        sigaction(SIGSEGV, &sa, NULL);

        cause_stack_overflow();
    }
#endif

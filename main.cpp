#include <iostream>

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
    #include <cstdlib>
    #include <cstring>
    #include <unistd.h>

    void handler(int signum) {
        std::cout << "Caught signal " << signum << ": Stack overflow detected!\n";
        std::cout << "Stack size estimated: " << stack_size / 1024 << "KB\n";
        _exit(0);
    }

    int main() {
        // Set up the signal stack
        stack_t ss;
        ss.ss_sp = malloc(SIGSTKSZ);  // Allocate the alternate signal stack
        if (ss.ss_sp == nullptr) {
            std::cerr << "Failed to allocate signal stack." << std::endl;
            return 1;
        }
        ss.ss_size = SIGSTKSZ;
        ss.ss_flags = 0;
        if (sigaltstack(&ss, nullptr) == -1) {
            std::cerr << "Failed to set up alternate signal stack." << std::endl;
            return 1;
        }

        // Set up the signal handler for SIGSEGV
        struct sigaction sa;
        sa.sa_sigaction = handler;
        sa.sa_flags = SA_SIGINFO | SA_ONSTACK;  // Use the alternate signal stack
        sigemptyset(&sa.sa_mask);
        if (sigaction(SIGSEGV, &sa, nullptr) == -1) {
            std::cerr << "Failed to set signal handler." << std::endl;
            return 1;
        }

        cause_stack_overflow();
    }
#endif

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <signal.h>
#include <unistd.h>
#include <execinfo.h>
#endif

volatile int stack_size = 0;

void cause_stack_overflow() {
    volatile char buffer[4*1024];
    stack_size += 4*1024;
    buffer[0] = stack_size / 4*1024; 
    cause_stack_overflow();
    buffer[4*1024 - 1] = stack_size / 4*1024; 
}


#if defined(_WIN32) && defined(_MSC_VER)
void stack_overflow_handler() {
    __try {
        cause_stack_overflow();  // This will cause a stack overflow
    }
    __except (EXCEPTION_STACK_OVERFLOW) {
        std::cerr << "Stack overflow detected!" << std::endl;
    }
}
#else
void signal_handler(int sig) {
    void *array[10];
    size_t size;
    std::cerr << "Stack overflow detected!" << std::endl;

    // Print stack trace
    size = backtrace(array, 10);
    backtrace_symbols_fd(array, size, STDERR_FILENO);

    exit(1); // Exit after handling the stack overflow
}
#endif

int main() {
#ifdef _WIN32
    stack_overflow_handler();
#else
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &sa, NULL);  // Register signal handler

    cause_stack_overflow(0);  // This will cause a stack overflow
#endif

    return 0;
}
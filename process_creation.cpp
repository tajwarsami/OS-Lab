#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        std::cout << "Child process (PID: " << getpid() << ")\n";
    } else if (pid > 0) {
        std::cout << "Parent process (PID: " << getpid() << ")\n";
        wait(NULL);
        std::cout << "Child process terminated\n";
    } else {
        std::cerr << "Fork failed!\n";
        return 1;
    }
    return 0;
}

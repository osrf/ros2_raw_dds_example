#include <chrono>
#include <csignal>
#include <thread>

#include <unistd.h>

#include "UUIDSubscriber.hpp"

constexpr int BUFFER_SIZE = 1024;

volatile sig_atomic_t running = 1;

void signal_handler(int signum)
{
    (void)signum;
    running = 0;
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    ::signal(SIGINT, signal_handler);

    UUIDSubscriber uuid_sub;

    uuid_sub.init();

    while (running)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}

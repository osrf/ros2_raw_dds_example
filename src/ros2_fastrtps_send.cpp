#include <chrono>
#include <csignal>
#include <cstdio>
#include <thread>

#include <unistd.h>

#include "UUID.hpp"
#include "UUIDPublisher.hpp"

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

    UUIDPublisher uuid_pub;

    uuid_pub.init();

    unique_identifier_msgs::msg::UUID st;
    uint8_t count = 0;
    while (running)
    {
        fprintf(stderr, "Publishing\n");
        st.uuid()[0] = count++;
        uuid_pub.publish(&st);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}

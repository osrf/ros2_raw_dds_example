#include <chrono>
#include <csignal>
#include <cstdio>
#include <cstring>
#include <memory>
#include <thread>

#include <unistd.h>

#include <fastcdr/Cdr.h>

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
        while (uuid_sub.hasMsg())
        {
            char data_buffer[BUFFER_SIZE] = {};
            /* make room for the header to fill in later */
            eprosima::fastcdr::FastBuffer cdrbuffer(&data_buffer[0], sizeof(data_buffer));
            eprosima::fastcdr::Cdr scdr(cdrbuffer);
            unique_identifier_msgs::msg::UUID msg = uuid_sub.getMsg();
            msg.serialize(scdr);
            int length = scdr.getSerializedDataLength();
            fprintf(stderr, "Got a message of length %d\n", length);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}

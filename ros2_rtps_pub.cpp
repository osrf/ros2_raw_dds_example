#include <chrono>
#include <cstdio>
#include <thread>

#include "UUID.hpp"
#include "UUIDPublisher.hpp"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    UUIDPublisher uuid_pub;

    uuid_pub.init();

    unique_identifier_msgs::msg::UUID st;
    uint8_t count = 0;
    while (true) {
      fprintf(stderr, "Publishing\n");
      st.uuid()[0] = count++;
      uuid_pub.publish(&st);

      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}

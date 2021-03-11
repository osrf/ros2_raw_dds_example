#include <csignal>
#include <cstdio>
#include <string>
#include <thread>

#include <unistd.h>

#include "dds/dds.h"

volatile sig_atomic_t running = 1;

void signal_handler(int signum)
{
    (void)signum;
    running = 0;
}

typedef struct UUID
{
    uint8_t uuid[16];
} UUID;

static const uint32_t UUID_ops [] =
{
    DDS_OP_ADR | DDS_OP_TYPE_ARR | DDS_OP_SUBTYPE_1BY, offsetof (UUID, uuid), 16,
    DDS_OP_RTS
};

const dds_topic_descriptor_t UUID_desc =
{
    sizeof (UUID),
    sizeof (char *),
    DDS_TOPIC_NO_OPTIMIZE,
    0u,
    "unique_identifier_msgs::msg::dds_::UUID_",
    nullptr,
    2,
    UUID_ops,
    "<MetaData version=\"1.0.0\"><Module name=\"unique_identifier_msgs\"><Module name=\"msg\"><Struct name=\"UUID\"><Member name=\"uuid\"><Array size=\"16\"><Octet/></Array></Member></Struct></Module></Module></MetaData>"
};

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    ::signal(SIGINT, signal_handler);

    dds_return_t rc;

    /* Create a Participant. */
    dds_entity_t participant = dds_create_participant(DDS_DOMAIN_DEFAULT, NULL, NULL);
    if (participant < 0)
    {
        DDS_FATAL("dds_create_participant: %s\n", dds_strretcode(-participant));
    }

    /* Create a Topic. */
    dds_entity_t topic = dds_create_topic(participant, &UUID_desc, "rt/uuid_topic", nullptr, nullptr);
    if (topic < 0)
    {
        DDS_FATAL("dds_create_topic: %s\n", dds_strretcode(-topic));
    }

    /* Create a Writer. */
    dds_entity_t writer = dds_create_writer(participant, topic, nullptr, nullptr);
    if (writer < 0)
    {
        DDS_FATAL("dds_create_writer: %s\n", dds_strretcode(-writer));
    }

    /* Create a message to write. */
    UUID msg{};

    uint8_t count = 0;
    while (running)
    {
        msg.uuid[0] = count++;

        fprintf(stderr, "Writing\n");
        rc = dds_write(writer, &msg);
        if (rc != DDS_RETCODE_OK)
        {
            DDS_FATAL("dds_write: %s\n", dds_strretcode(-rc));
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    /* Deleting the participant will delete all its children recursively as well. */
    rc = dds_delete(participant);
    if (rc != DDS_RETCODE_OK)
    {
        DDS_FATAL("dds_delete: %s\n", dds_strretcode(-rc));
    }

    return 0;
}

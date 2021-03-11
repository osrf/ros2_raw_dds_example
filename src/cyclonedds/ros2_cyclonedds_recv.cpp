#include <chrono>
#include <csignal>
#include <thread>

#include <unistd.h>

#include "dds/dds.h"

/* An array of one message (aka sample in dds terms) will be used. */
#define MAX_SAMPLES 1

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

int main (int argc, char ** argv)
{
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

    dds_entity_t reader = dds_create_reader(participant, topic, nullptr, nullptr);
    if (reader < 0)
    {
        DDS_FATAL("dds_create_reader: %s\n", dds_strretcode(-reader));
    }

    void *samples[MAX_SAMPLES];

    /* Initialize sample buffer, by pointing the void pointer within
     * the buffer array to a valid sample memory location. */
    samples[0] = dds_alloc(sizeof(UUID));

    while (running)
    {
        dds_sample_info_t infos[MAX_SAMPLES];

        /* Do the actual read.
         * The return value contains the number of read samples. */
        rc = dds_take(reader, samples, infos, MAX_SAMPLES, MAX_SAMPLES);
        if (rc < 0)
        {
            DDS_FATAL("dds_read: %s\n", dds_strretcode(-rc));
        }

        /* Check if we read some data and it is valid. */
        if ((rc > 0) && (infos[0].valid_data))
        {
            /* Print Message. */
            UUID * msg = (UUID*) samples[0];
            fprintf(stderr, "Received UUID, first byte: %d\n", msg->uuid[0]);
        }
        else
        {
          std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    dds_sample_free(samples[0], &UUID_desc, DDS_FREE_ALL);

    /* Deleting the participant will delete all its children recursively as well. */
    rc = dds_delete (participant);
    if (rc != DDS_RETCODE_OK)
    {
        DDS_FATAL("dds_delete: %s\n", dds_strretcode(-rc));
    }

    return 0;
}

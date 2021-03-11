#include <csignal>
#include <cstdio>

#include "UUID.h"
#include "UUIDSupport.h"
#include "ndds/ndds_cpp.h"

volatile sig_atomic_t running = 1;

void signal_handler(int signum)
{
    (void)signum;
    running = 0;
}

/* Delete all entities */
static int publisher_shutdown(DDSDomainParticipant *participant)
{
  DDS_ReturnCode_t retcode;
  int status = 0;

  if (participant != NULL) {
    retcode = participant->delete_contained_entities();
    if (retcode != DDS_RETCODE_OK) {
      printf("delete_contained_entities error %d\n", retcode);
      status = -1;
    }

    retcode = DDSTheParticipantFactory->delete_participant(participant);
    if (retcode != DDS_RETCODE_OK) {
      printf("delete_participant error %d\n", retcode);
      status = -1;
    }
  }

  return status;
}

int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  DDSDomainParticipant *participant = NULL;
  DDSPublisher *publisher = NULL;
  DDSTopic *topic = NULL;
  DDSDataWriter *writer = NULL;
  unique_identifier_msgs_msg_UUIDDataWriter * uuid_writer = NULL;
  unique_identifier_msgs_msg_UUID *instance = NULL;
  DDS_ReturnCode_t retcode;
  DDS_InstanceHandle_t instance_handle = DDS_HANDLE_NIL;
  const char *type_name = NULL;
  /* Send a new sample every second */
  DDS_Duration_t send_period = {1,0};

  ::signal(SIGINT, signal_handler);

  participant = DDSTheParticipantFactory->create_participant(
    0, DDS_PARTICIPANT_QOS_DEFAULT,
    NULL /* listener */, DDS_STATUS_MASK_NONE);
  if (participant == NULL) {
    printf("create_participant error\n");
    publisher_shutdown(participant);
    return 1;
  }

  publisher = participant->create_publisher(
    DDS_PUBLISHER_QOS_DEFAULT, NULL /* listener */, DDS_STATUS_MASK_NONE);
  if (publisher == NULL) {
    printf("create_publisher error\n");
    publisher_shutdown(participant);
    return 1;
  }

  /* Register type before creating topic */
  type_name = unique_identifier_msgs_msg_UUIDTypeSupport::get_type_name();
  retcode = unique_identifier_msgs_msg_UUIDTypeSupport::register_type(participant, type_name);
  if (retcode != DDS_RETCODE_OK) {
    printf("register_type error %d\n", retcode);
    publisher_shutdown(participant);
    return 1;
  }

  topic = participant->create_topic(
    "rt/uuid_topic",
    type_name, DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
    DDS_STATUS_MASK_NONE);
  if (topic == NULL) {
    printf("create_topic error\n");
    publisher_shutdown(participant);
    return 1;
  }

  writer = publisher->create_datawriter(
    topic, DDS_DATAWRITER_QOS_DEFAULT, NULL /* listener */,
    DDS_STATUS_MASK_NONE);
  if (writer == NULL) {
    printf("create_datawriter error\n");
    publisher_shutdown(participant);
    return 1;
  }

  uuid_writer = unique_identifier_msgs_msg_UUIDDataWriter::narrow(writer);
  if (uuid_writer == NULL) {
    printf("DataWriter narrow error\n");
    publisher_shutdown(participant);
    return -1;
  }

  /* Create data sample for writing */

  instance = unique_identifier_msgs_msg_UUIDTypeSupport::create_data();
  if (instance == NULL) {
    printf("unique_identifier_msgs_msg_UUIDTypeSupport::create_data error\n");
    publisher_shutdown(participant);
    return -1;
  }

  /* Main loop */
  uint8_t count = 0;
  while (running) {
    instance->uuid[0] = count++;

    printf("Publishing with uuid[0] of %u\n", instance->uuid[0]);
    retcode = uuid_writer->write(*instance, instance_handle);
    if (retcode != DDS_RETCODE_OK) {
      printf("write error %d\n", retcode);
    }

    NDDSUtility::sleep(send_period);
  }

  /* Delete data sample */
  retcode = unique_identifier_msgs_msg_UUIDTypeSupport::delete_data(instance);
  if (retcode != DDS_RETCODE_OK) {
    printf("unique_identifier_msgs_msg_UUIDTypeSupport::delete_data error %d\n", retcode);
  }

  /* Delete all entities */
  return publisher_shutdown(participant);
}

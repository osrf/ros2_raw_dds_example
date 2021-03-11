#include <csignal>
#include <cstdio>
#include <stdlib.h>

#include "UUID.h"
#include "UUIDSupport.h"
#include "ndds/ndds_cpp.h"

volatile sig_atomic_t running = 1;

void signal_handler(int signum)
{
    (void)signum;
    running = 0;
}

class unique_identifier_msgs_msg_UUIDListener : public DDSDataReaderListener {
public:
  virtual void on_requested_deadline_missed(
    DDSDataReader* /*reader*/,
    const DDS_RequestedDeadlineMissedStatus& /*status*/) {}

  virtual void on_requested_incompatible_qos(
    DDSDataReader* /*reader*/,
    const DDS_RequestedIncompatibleQosStatus& /*status*/) {}

  virtual void on_sample_rejected(
    DDSDataReader* /*reader*/,
    const DDS_SampleRejectedStatus& /*status*/) {}

  virtual void on_liveliness_changed(
    DDSDataReader* /*reader*/,
    const DDS_LivelinessChangedStatus& /*status*/) {}

  virtual void on_sample_lost(
    DDSDataReader* /*reader*/,
    const DDS_SampleLostStatus& /*status*/) {}

  virtual void on_subscription_matched(
    DDSDataReader* /*reader*/,
    const DDS_SubscriptionMatchedStatus& /*status*/) {}

  virtual void on_data_available(DDSDataReader* reader);
};

void unique_identifier_msgs_msg_UUIDListener::on_data_available(DDSDataReader* reader)
{
  unique_identifier_msgs_msg_UUIDDataReader *unique_identifier_msgs_msg_UUID_reader = NULL;
  unique_identifier_msgs_msg_UUIDSeq data_seq;
  DDS_SampleInfoSeq info_seq;
  DDS_ReturnCode_t retcode;
  int i;

  unique_identifier_msgs_msg_UUID_reader = unique_identifier_msgs_msg_UUIDDataReader::narrow(reader);
  if (unique_identifier_msgs_msg_UUID_reader == NULL) {
    fprintf(stderr, "DataReader narrow error\n");
    return;
  }

  retcode = unique_identifier_msgs_msg_UUID_reader->take(
    data_seq, info_seq, DDS_LENGTH_UNLIMITED,
    DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);

  if (retcode == DDS_RETCODE_NO_DATA) {
    return;
  } else if (retcode != DDS_RETCODE_OK) {
    fprintf(stderr, "take error %d\n", retcode);
    return;
  }

  for (i = 0; i < data_seq.length(); ++i) {
    if (info_seq[i].valid_data) {
      printf("Received data\n");
      unique_identifier_msgs_msg_UUIDTypeSupport::print_data(&data_seq[i]);
    }
  }

  retcode = unique_identifier_msgs_msg_UUID_reader->return_loan(data_seq, info_seq);
  if (retcode != DDS_RETCODE_OK) {
    fprintf(stderr, "return loan error %d\n", retcode);
  }
}

/* Delete all entities */
static int subscriber_shutdown(DDSDomainParticipant *participant)
{
  DDS_ReturnCode_t retcode;
  int status = 0;

  if (participant != NULL) {
    retcode = participant->delete_contained_entities();
    if (retcode != DDS_RETCODE_OK) {
      fprintf(stderr, "delete_contained_entities error %d\n", retcode);
      status = -1;
    }

    retcode = DDSTheParticipantFactory->delete_participant(participant);
    if (retcode != DDS_RETCODE_OK) {
      fprintf(stderr, "delete_participant error %d\n", retcode);
      status = -1;
    }
  }

  return status;
}

int main(int argc, char * argv[])
{
  (void)argc;
  (void)argv;
  DDSDomainParticipant *participant = NULL;
  DDSSubscriber *subscriber = NULL;
  DDSTopic *topic = NULL;
  unique_identifier_msgs_msg_UUIDListener *reader_listener = NULL;
  DDSDataReader *reader = NULL;
  DDS_ReturnCode_t retcode;
  const char *type_name = NULL;
  int count = 0;
  DDS_Duration_t receive_period = {1,0};
  int status = 0;

  /* To customize the participant QoS, use
     the configuration file USER_QOS_PROFILES.xml */
  participant = DDSTheParticipantFactory->create_participant(
    0, DDS_PARTICIPANT_QOS_DEFAULT,
    NULL /* listener */, DDS_STATUS_MASK_NONE);
  if (participant == NULL) {
    fprintf(stderr, "create_participant error\n");
    subscriber_shutdown(participant);
    return -1;
  }

  /* To customize the subscriber QoS, use
     the configuration file USER_QOS_PROFILES.xml */
  subscriber = participant->create_subscriber(
    DDS_SUBSCRIBER_QOS_DEFAULT, NULL /* listener */, DDS_STATUS_MASK_NONE);
  if (subscriber == NULL) {
    fprintf(stderr, "create_subscriber error\n");
    subscriber_shutdown(participant);
    return -1;
  }

  /* Register the type before creating the topic */
  type_name = unique_identifier_msgs_msg_UUIDTypeSupport::get_type_name();
  retcode = unique_identifier_msgs_msg_UUIDTypeSupport::register_type(
    participant, type_name);
  if (retcode != DDS_RETCODE_OK) {
    fprintf(stderr, "register_type error %d\n", retcode);
    subscriber_shutdown(participant);
    return -1;
  }

  /* To customize the topic QoS, use
     the configuration file USER_QOS_PROFILES.xml */
  topic = participant->create_topic(
    "rt/uuid_topic",
    type_name, DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
    DDS_STATUS_MASK_NONE);
  if (topic == NULL) {
    fprintf(stderr, "create_topic error\n");
    subscriber_shutdown(participant);
    return -1;
  }

  /* Create a data reader listener */
  reader_listener = new unique_identifier_msgs_msg_UUIDListener();

  /* To customize the data reader QoS, use
     the configuration file USER_QOS_PROFILES.xml */
  reader = subscriber->create_datareader(
    topic, DDS_DATAREADER_QOS_DEFAULT, reader_listener,
    DDS_STATUS_MASK_ALL);
  if (reader == NULL) {
    fprintf(stderr, "create_datareader error\n");
    subscriber_shutdown(participant);
    delete reader_listener;
    return -1;
  }

  while (running) {
    NDDSUtility::sleep(receive_period);
  }

  /* Delete all entities */
  status = subscriber_shutdown(participant);
  delete reader_listener;

  return status;
}

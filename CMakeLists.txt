cmake_minimum_required(VERSION 3.5)

project(ros2_raw_dds_example)

find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)

add_executable(ros2_fastrtps_recv
  src/ros2_fastrtps_recv.cpp
  src/UUID.cxx
  src/UUIDPubSubTypes.cxx
  src/UUIDSubscriber.cxx
)
target_link_libraries(ros2_fastrtps_recv
  fastrtps
)

add_executable(ros2_fastrtps_send
  src/ros2_fastrtps_send.cpp
  src/UUID.cxx
  src/UUIDPubSubTypes.cxx
  src/UUIDPublisher.cxx
)
target_link_libraries(ros2_fastrtps_send
  fastrtps
)

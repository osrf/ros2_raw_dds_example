cmake_minimum_required(VERSION 3.5)

project(ros2_raw_dds_example)

find_package(CycloneDDS REQUIRED)
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

add_executable(ros2_cyclonedds_send
  src/ros2_cyclonedds_send.cpp
)
target_link_libraries(ros2_cyclonedds_send
  CycloneDDS::ddsc
)

add_executable(ros2_cyclonedds_recv
  src/ros2_cyclonedds_recv.cpp
)
target_link_libraries(ros2_cyclonedds_recv
  CycloneDDS::ddsc
)

cmake_minimum_required(VERSION 3.5)

project(ros2_raw_dds_example)

find_package(CycloneDDS REQUIRED)
find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)

add_executable(ros2_fastdds_recv
  src/fastdds/ros2_fastdds_recv.cpp
  src/fastdds/UUID.cxx
  src/fastdds/UUIDPubSubTypes.cxx
  src/fastdds/UUIDSubscriber.cxx
)
target_link_libraries(ros2_fastdds_recv
  fastrtps
)

add_executable(ros2_fastdds_send
  src/fastdds/ros2_fastdds_send.cpp
  src/fastdds/UUID.cxx
  src/fastdds/UUIDPubSubTypes.cxx
  src/fastdds/UUIDPublisher.cxx
)
target_link_libraries(ros2_fastdds_send
  fastrtps
)

add_executable(ros2_cyclonedds_send
  src/cyclonedds/ros2_cyclonedds_send.cpp
)
target_link_libraries(ros2_cyclonedds_send
  CycloneDDS::ddsc
)

add_executable(ros2_cyclonedds_recv
  src/cyclonedds/ros2_cyclonedds_recv.cpp
)
target_link_libraries(ros2_cyclonedds_recv
  CycloneDDS::ddsc
)

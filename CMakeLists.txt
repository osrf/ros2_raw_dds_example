cmake_minimum_required(VERSION 3.5)

project(ros2_raw_dds_example)

list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

find_package(CycloneDDS REQUIRED)
find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)
find_package(Connext QUIET MODULE)

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

if(Connext_FOUND)
  add_executable(ros2_connextdds_send
    src/connextdds/ros2_connextdds_send.cpp
    src/connextdds/UUID.cxx
    src/connextdds/UUIDSupport.cxx
    src/connextdds/UUIDPlugin.cxx
  )
  target_include_directories(ros2_connextdds_send PRIVATE ${Connext_INCLUDE_DIRS})
  target_compile_definitions(ros2_connextdds_send PRIVATE ${Connext_DEFINITIONS})
  target_link_libraries(ros2_connextdds_send PRIVATE ${Connext_LIBRARIES})

  add_executable(ros2_connextdds_recv
    src/connextdds/ros2_connextdds_recv.cpp
    src/connextdds/UUID.cxx
    src/connextdds/UUIDSupport.cxx
    src/connextdds/UUIDPlugin.cxx
  )
  target_include_directories(ros2_connextdds_recv PRIVATE ${Connext_INCLUDE_DIRS})
  target_compile_definitions(ros2_connextdds_recv PRIVATE ${Connext_DEFINITIONS})
  target_link_libraries(ros2_connextdds_recv PRIVATE ${Connext_LIBRARIES})
endif()

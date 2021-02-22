CXX=g++
CXXFLAGS=-g -Wall -Wextra -std=c++14 -I/home/ubuntu/ros2_ws/install/fastcdr/include -I/home/ubuntu/ros2_ws/install/fastrtps/include
LIBS=-L/home/ubuntu/ros2_ws/install/fastcdr/lib -L/home/ubuntu/ros2_ws/install/fastrtps/lib -lfastcdr -lfastrtps
RTPSRECV_OBJS=ros2_rtps_recv.o RtpsTopics.o UUID.o UUIDPubSubTypes.o UUIDPublisher.o UUIDSubscriber.o
RTPSPUB_OBJS=ros2_rtps_pub.o UUIDPublisher.o UUID.o UUIDPubSubTypes.o

all: ros2_rtps_recv ros2_rtps_pub

ros2_rtps_recv: $(RTPSRECV_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(RTPSRECV_OBJS) $(LIBS)

ros2_rtps_pub: $(RTPSPUB_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(RTPSPUB_OBJS) $(LIBS)

clean:
	rm -f *.o *~ ros2_rtps_recv ros2_rtps_pub

allclean: clean
	rm -rf install

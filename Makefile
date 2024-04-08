CC = g++
CFLAGS = -std=c++11 -Wall

SRCS = GRASP-algorithm/GRASP-algorithm.cc \
       greedy-algorithm/greedy-algorithm.cc \
       problem/problem.cc \
       solution/solution.cc \
       local-search/swap-local-search/swap-local-search.cc \
       main.cc

OBJS = $(SRCS:.cc=.o)

TARGET = PMSP

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

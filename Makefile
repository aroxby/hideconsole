DEMO_SRCS=demo.cpp
DEMO_OBJS=$(subst .cpp,.o,$(DEMO_SRCS))
DEMO=demo
DEMO_LDFLAGS='-Wl,--subsystem,console'

SRCS=main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
TARGET=hideconsole
LDFLAGS='-Wl,--subsystem,windows'

CPP=g++

.PHONY: all tidy clean

all: $(TARGET) $(DEMO)

%.o: %.cpp $(DEPENDS)
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(DEMO): $(DEMO_OBJS)
	$(CPP) $^ $(DEMO_LDFLAGS) -o $@

$(TARGET): $(OBJS)
	$(CPP) $^ $(LDFLAGS) -o $@

tidy:
	rm -f $(OBJS) $(DEMO_OBJS)

clean: tidy
	rm -f $(TARGET) $(DEMO)

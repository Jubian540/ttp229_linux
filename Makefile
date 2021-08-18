include Makefile.param

SRCS := $(wildcard *.c)
SRCSH := $(wildcard *.h)

TARGET := $(SRCS:%.c=%.o)

all: $(TARGET) $(OBJS)
	@cd android;     make
	@cd gpio;        make
	@cd ttp229;      make
	$(CC) $(TARGET) $(OBJS) -o $(PROJECT) $(CFLAGS)


$(TARGET): $(SRCS) $(SRCSH)
	$(CC) $(CFLAGS) -c $(SRCS) $(INCLUDE_PATH)

.PHONY: clean

clean:
	$(RM) $(TARGET)
	@cd android;		make clean
	@cd gpio;		make clean
	@cd ttp229;		make clean

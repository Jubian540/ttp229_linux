include ../Makefile.param

SRCS := $(wildcard *.c)
SRCSH := $(wildcard *.h)

TARGET := $(SRCS:%.c=%.o)
TARGET_PATH := $(PWD)

INCLUDE_PATH += -I $(TARGET_PATH)

LINK_TARGET += $(TARGET)

$(TARGET): $(SRCS) $(SRCSH)
	$(CC) $(CFLAGS) -c $(SRCS)

clean::
	$(RM) $(TARGET)

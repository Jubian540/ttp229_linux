include ../Makefile.param

SRCS := $(wildcard *.c)
SRCSH := $(wildcard *.h)

TARGET := $(SRCS:%.c=%.o)

$(TARGET): $(SRCS) $(SRCSH)
	$(CC) $(CFLAGS) -c $(SRCS) -I$(TOPDIR)/gpio

clean::
	$(RM) $(TARGET)

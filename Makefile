include Makefile.param

SRCS := $(wildcard *.c)
SRCSH := $(wildcard *.h)

TARGET := $(SRCS:%.c=%.o)
TOPDIR := $(PWD)

all: $(TARGET)
	$(MAKE) -C $(TOPDIR)/android
	$(MAKE) -C $(TOPDIR)/gpio
	$(MAKE) -C $(TOPDIR)/ttp229 TOPDIR=$(TOPDIR) 
	$(CC) $(TARGET) $(OBJS) -o $(PROJECT) $(CFLAGS)

.PHONY: push

push:

$(TARGET): $(SRCS) $(SRCSH)
	$(CC) $(CFLAGS) -c $(SRCS) $(INCLUDE_PATH)

.PHONY: clean

clean:
	$(RM) $(PROJECT)
	$(RM) $(TARGET)
	@cd android;	make clean
	@cd gpio;		make clean
	@cd ttp229;		make clean

.PHONY: push

push: $(PROJECT)
	@adb push $(PROJECT) /data/local/tmp

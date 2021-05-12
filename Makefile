CC=/data/build/rk3399_linux_release_v2.5.1_20210301/prebuilts/gcc/linux-x86/aarch64/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc

test: main.o gpio/gpio.o
	$(CC) main.o gpio/gpio.o -o test

gpio.o: gpio/gpio.c gpio/gpio.h
	$(CC) -c gpio/gpio.c

main.o: main.c gpio/gpio.h
	$(CC) -c main.c

clean:
	rm -rf *.o
	rm test

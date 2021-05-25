CC=/data/build/rk3399_linux_release_v2.5.1_20210301/prebuilts/gcc/linux-x86/aarch64/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc

test: main.o gpio/gpio.o android/android.o ttp229/ttp229.o
	$(CC) -static main.o gpio/gpio.o android/android.o ttp229/ttp229.o -o test

main.o: main.c gpio/gpio.h android/android.h ttp229/ttp229.h
	$(CC) -static -c main.c

gpio:
	cd gpio && $(MAKE)

android:
	cd android && $(MAKE)

ttp229:
	cd ttp229 && $(MAKE)

clean:
	rm -rf *.o
	rm -rf gpio/*.o
	rm -rf android/*.o
	rm -rf ttp229/*.o
	rm test

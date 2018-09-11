binary = hello_world
source = $(binary).c morse.c
optimize = s
partno-define = __AVR_ATmega328P__
f-cpu = 16000000UL
partno = m328p
programmer-id = arduino
port = /dev/ttyUSB0

CC = avr-gcc

$(binary): $(source) morse.h
	$(CC) $(CFLAGS) -D$(partno-define) -DF_CPU=$(f-cpu) -O$(optimize) -o \
		$(binary) $(source)

.PHONY: upload
upload: $(binary)
	sudo avrdude -c$(programmer-id) -p$(partno) -P$(port) \
		-Uflash:w:$(binary):e

.PHONY: view_asm
view_asm: $(binary)
	@avr-objdump -d $(binary) | less

.PHONY: clean
clean:
	$(RM) $(binary)

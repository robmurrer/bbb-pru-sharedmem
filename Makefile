CFLAGS+=-Wall -Werror
LDLIBS+= -lpthread -lprussdrv
TARGET=sharedmem


all: $(TARGET).bin $(TARGET) run

clean:
	rm -f $(TARGET) *.o *.bin

$(TARGET).bin: $(TARGET).p
	pasm -b $^

$(TARGET): $(TARGET).o

run:
	./$(TARGET)


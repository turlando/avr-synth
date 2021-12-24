################################################################################

CC      = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
CTAGS   = ctags
ETAGS   = ctags -e

AVRDUDE_PORT = /dev/ttyACM0
AVRDUDE_BAUD = 115200

################################################################################

MICROCONTROLLER := atmega328p
CPU_FREQUENCY   := 16000000

SRC_PATH     := src
INCLUDE_PATH := include

TARGET := main

################################################################################

DEFINES := -DF_CPU=$(CPU_FREQUENCY) \
           -D__AVR_ATmega328P__

INCLUDES := -I$(INCLUDE_PATH)

CFLAGS := -std=c11 -pedantic       \
          -Wall -Wextra            \
          -c                       \
          -Os                      \
          -flto                    \
          -ffunction-sections      \
          -fdata-sections          \
          -mmcu=$(MICROCONTROLLER) \
          $(DEFINES)               \
          $(INCLUDES)

LDFLAGS := -Wall -Wextra            \
           -Os                      \
           -flto                    \
           -fuse-linker-plugin      \
           -Wl,--gc-sections        \
           -mmcu=$(MICROCONTROLLER)

AVRDUDEFLAGS := -F -V                                 \
                -c arduino -p $(MICROCONTROLLER)      \
                -P $(AVRDUDE_PORT) -b $(AVRDUDE_BAUD)

################################################################################

C_SRCS := $(wildcard $(SRC_PATH)/*.c)
C_OBJS := $(C_SRCS:.c=.o)
C_DEPS := $(C_OBJS:.o=.d)

################################################################################

.PHONY: all
all: $(TARGET).hex

$(TARGET).elf: $(C_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

tags: $(C_SRCS)
	$(CTAGS) $^

TAGS: $(C_SRCS)
	$(ETAGS) $^

.PHONY: flash
flash: $(TARGET).hex
	$(AVRDUDE) $(AVRDUDEFLAGS) -U flash:w:$<

.PHONY: clean
clean:
	rm -f $(C_OBJS)
	rm -f $(C_DEPS)
	rm -f $(TARGET).elf
	rm -f tags TAGS

.PHONY: distclean
distclean: clean
	rm -f $(TARGET).hex

-include $(C_DEPS)

################################################################################

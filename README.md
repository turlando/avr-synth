# Embedded Systems Project

## Dependencies

### ArchLinux

- avr-gcc
- avr-libc
- make
- avrdude
- ctags (optional, for code completion in editors)
- screen (optional, for serial monitor)

## Makefile usage

### Variables

- `SERIAL_DEVICE` - Serial device used by `flash` and `serial` target.
  Default: `/dev/ttyACM0`
- `AVRDUDE_BAUD` - Baud rate used by avrdude. Default: 115200
- `SCREEN_BAUD` - Baud rate used by screen. Default: 9600

### Targets

- `all` - Compile everything
- `clean` - Remove object files, dependency files, ELF file and ctags
- `distclean` - `clean` and remove hex file
- `flash` - Flash the microcontroller
- `serial` - Start the serial monitor

BOARD?=arduino:avr:mega
PORT?=/dev/cu.usbmodem14*
BUILD=build

.PHONY: default lint all flash clean

default: lint all flash clean

all:
	arduino-cli compile --fqbn $(BOARD) --output-dir $(BUILD) ./

flash:
	arduino-cli upload --fqbn $(BOARD) --port $(PORT) --input-dir $(BUILD)

clean:
	rm -r build

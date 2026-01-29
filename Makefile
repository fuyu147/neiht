.PHONY: run build

build:
	clear
	cmake . -B build
	make -C build

run: build
	./build/sgrok

.PHONY: run build
run: build
	./build/sgrok

build:
	clear
	cmake . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	make -C build

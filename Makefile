obj-m := harpoon.o
harpoon-objs := src/main.o src/module/module.o

all:
	sudo make -C test_env/kernel M=$(PWD) modules
clean:
	sudo make -C test_env/kernel M=$(PWD) clean

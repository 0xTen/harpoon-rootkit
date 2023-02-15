obj-m := harpoon.o
harpoon-objs := src/main.o src/module/module.o src/hooking/hooking.o

all:
	sudo make -C $(KERNEL) M=$(PWD) modules
clean:
	sudo make -C $(KERNEL) M=$(PWD) clean

obj-m := harpoon.o
harpoon-objs := src/main.o src/module/module.o src/hooking/hooking.o src/backdoor/backdoor.o

all:
	sudo make -C $(KERNEL) M=$(PWD) modules
clean:
	sudo make -C $(KERNEL) M=$(PWD) clean

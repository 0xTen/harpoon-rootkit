cmd_/home/xten/Documents/projects/nu/harpoon-rootkit/harpoon.o := ld -m elf_x86_64 -z noexecstack --no-warn-rwx-segments   -r -o /home/xten/Documents/projects/nu/harpoon-rootkit/harpoon.o @/home/xten/Documents/projects/nu/harpoon-rootkit/harpoon.mod  ; ./tools/objtool/objtool --hacks=jump_label --hacks=noinstr --hacks=skylake --ibt --orc --retpoline --rethunk --static-call --uaccess --prefix=16  --link  --module /home/xten/Documents/projects/nu/harpoon-rootkit/harpoon.o

/home/xten/Documents/projects/nu/harpoon-rootkit/harpoon.o: $(wildcard ./tools/objtool/objtool)

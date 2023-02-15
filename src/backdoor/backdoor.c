#include <net/ip.h>

#include "backdoor.h"

extern int (*legit_ip_rcv)(struct sk_buff *skb, struct net_device *dev, struct packet_type *pt,
        struct net_device *orig_dev);

int harpoon_ip_rcv(struct sk_buff *skb, struct net_device *dev, struct packet_type *pt,
        struct net_device *orig_dev){

    printk(KERN_INFO "Hooked ip_rcv");
    return legit_ip_rcv(skb, dev, pt, orig_dev);
}
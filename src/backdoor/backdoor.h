#ifndef H_HARPOON_BD
#define H_HARPOON_BD

int harpoon_ip_rcv(struct sk_buff *skb, struct net_device *dev, struct packet_type *pt,
        struct net_device *orig_dev);

#endif
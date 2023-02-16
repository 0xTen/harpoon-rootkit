#ifndef H_HARPOON_BD
#define H_HARPOON_BD

#define HARPOON_MAGIC "\xff\xffHARPOON\xde\xad\xbe\xef"
#define HARPOON_MAGIC_LEN sizeof(HARPOON_MAGIC)

void harpoon_ip_rcv(struct sk_buff *skb, struct net_device *dev, struct packet_type *pt,
        struct net_device *orig_dev);

#endif
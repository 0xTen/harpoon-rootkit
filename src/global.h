#ifndef H_HARPOON_GL
#define H_HARPOON_GL

#include <linux/list.h>

/* Global container */
struct harpoon_struct {
    struct list_head module_list;
    struct list_head hook_list;
};

#endif
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include "inc/hello1.h" // Включаємо заголовковий файл

MODULE_AUTHOR ("Stanislav Osipov <stasosipov09092004@gmail.com>");
MODULE_DESCRIPTION ("Hello, this is LabWork №4 - Module 1");
MODULE_LICENSE("Dual BSD/GPL");

struct hello_event {
    struct list_head list;
    ktime_t time_before;
    ktime_t time_after; // Нове поле ktime_t
};

EXPORT_SYMBOL(print_hello); // Експортуємо функцію

static struct list_head hello_list_head;

void print_hello(uint count) {
    int i;
    struct hello_event *ptr;

    if (count == 0) {
        pr_warn("Count is 0.\n");
    }

    if (count >= 5 && count <= 10) {
        pr_warn("Count is between 5 and 10.\n");
    }

    if (count > 10) {
        pr_err("Count is greater than 10. \nExiting with error.\n");
        return;
    }

    INIT_LIST_HEAD(&hello_list_head);

    for (i = 0; i < count; ++i) {
        ptr = kmalloc(sizeof(*ptr), GFP_KERNEL);
        if (!ptr)
            return;

        ptr->time_before = ktime_get(); // Засікаємо час перед друком
        pr_info("Hello, world!\n");
        ptr->time_after = ktime_get(); // Засікаємо час після друку
        list_add_tail(&ptr->list, &hello_list_head);
    }
}

static int __init hello1_init(void) {
    pr_info("Hello1 module initialized.\n");
    return 0;
}

static void __exit hello1_exit(void) {
    struct hello_event *ptr, *temp;

    list_for_each_entry_safe(ptr, temp, &hello_list_head, list) {
        pr_info("Time taken: %lld ns\n", ktime_to_ns(ktime_sub(ptr->time_after, ptr->time_before)));
        list_del(&ptr->list);
        kfree(ptr);
    }

    pr_info("Hello1 module exited.\n");
}

module_init(hello1_init);
module_exit(hello1_exit);

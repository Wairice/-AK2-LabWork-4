#include <linux/init.h>
#include <linux/module.h>
#include "inc/hello1.h" // Включаємо заголовковий файл

MODULE_AUTHOR ("Stanislav Osipov <stasosipov09092004@gmail.com>");
MODULE_DESCRIPTION ("Hello, this is LabWork №4 - Module 2");
MODULE_LICENSE("Dual BSD/GPL");

void print_hello(uint count); // Декларація функції

static uint count = 1;
module_param(count, uint, S_IRUGO);
MODULE_PARM_DESC(count, "Count of times to print \"Hello, world!\"");

static int __init hello2_init(void) {
    pr_info("Hello2 module initialized.\n");
    print_hello(count); // Викликаємо функцію з hello1
    return 0;
}

static void __exit hello2_exit(void) {
    pr_info("Hello2 module exited.\n");
}

module_init(hello2_init);
module_exit(hello2_exit);

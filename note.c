
/*
 * name: the name of the entry that we want to create
 * mode: the permissions for the entry created
 * in the case the entry needs to be created in a sub directory under /proc, we will have to give the full path
 */
proc_dir_entry *create_proc_entry(const char *name, mode_t mode, struct proc_dir_entry *parent);


// init
// proc_dir_entry is defined in "linux/proc_fs.h"
proc_dir_entry *proc_write_entry = create_proc_entry("heelo", 0666, NULL); // rw- for everyone

// read, write
proc_write_entry->read_proc = read_proc;
proc_write_entry->write_proc = write_proc;


// their definition
// read
int read_proc(char *buf, char **start, off_t offset, int count, int *eof, void *data) {
    int len=0;
    len = sprintf(buf, "\n %s\n", proc_data);

    return len;
}

// write
int write_proc(struct file *file, const char *buf, int count, void *data) {
    if(count > MAX_PROC_SIZE)                   count = MAX_PROC_SIZE;
    if(copy_from_user(proce_data, buf, count))  return -EFAULT;
    return count;
}

/* Full Example */
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <linux/proc_fs.h>
#define MAX_PROC_SIZE 100
static char proc_data[MAX_PROC_SIZE];

static struct proc_dir_entry *proc_write_entry;

int read_proc(char *buf,char **start,off_t offset,int count,int *eof,void *data )
{
    int len=0;
    len = sprintf(buf,"\n %s\n ",proc_data);

    return len;
}

int write_proc(struct file *file,const char *buf,int count,void *data )
{

    if(count > MAX_PROC_SIZE)
        count = MAX_PROC_SIZE;
    if(copy_from_user(proc_data, buf, count))
        return -EFAULT;

    return count;
}

void create_new_proc_entry()
{
    proc_write_entry = create_proc_entry("proc_entry",0666,NULL);
    if(!proc_write_entry)
    {
        printk(KERN_INFO "Error creating proc entry");
        return -ENOMEM;
    }
    proc_write_entry->read_proc = read_proc ;
    proc_write_entry->write_proc = write_proc;
    printk(KERN_INFO "proc initialized");

}

int proc_init (void) {
    create_new_proc_entry();
    return 0;
}

void proc_cleanup(void) {
    printk(KERN_INFO " Inside cleanup_module\n");
    remove_proc_entry("proc_entry",NULL);
}
MODULE_LICENSE("GPL");   
module_init(proc_init);
module_exit(proc_cleanup);


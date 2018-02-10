//file for export system information to proc fs,/porc/icinfo iterm
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <asm/atomic.h>
#include <asm/uaccess.h>
#include <linux/seq_file.h>

#define IC_BUF 512
static char icinfo_buf[IC_BUF]={0};
static int watcher= 0;




int iccopy(const char *fmt, ...)
{
	va_list args;
	int i;
	if(strstr(icinfo_buf,fmt))
		return;
	//we should add buffer overflow check here
	va_start(args, fmt);
	i = vsnprintf(icinfo_buf+watcher, INT_MAX, fmt, args);
	va_end(args);

	watcher+=i;
	return i;
}

EXPORT_SYMBOL(iccopy);

static int icinfo_proc_show(struct seq_file *m, void *v)
{
  seq_write(m, icinfo_buf,watcher);
  return 0;
}

static int icinfo_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, icinfo_proc_show, NULL);
}

static const struct file_operations icinfo_fops = {
	.owner = THIS_MODULE,
	.open  = icinfo_proc_open,
	.read =  seq_read,
};

static int __init icinfo_init(void)
{
	static struct proc_dir_entry *icproc = NULL;
	icproc = proc_create("icinfo", 0644, NULL,&icinfo_fops);
	if (icproc == NULL)
	    {
		printk(KERN_ERR "create_proc_entry ecompass_status failed!\n");
	    }
	return 0;
}


device_initcall(icinfo_init);


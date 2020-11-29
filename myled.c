/*
 *
 *
 *
 * Copyright　(c) 2020 KentaObata. All rights reseved
 *
 *
 *
 *
 *
 * This program is free software: you can redistribute it and/or modifyy
 * it under the terms of the GNU General Public LIcense as published by 
 * the Free software Fundation, either version 3 of the License. or
 * (at your option) any later version.
 *
 * This program is distributed in hope that it will be usiful,
 * but WITHOUT ANY WARRNTY; without even the implied warranty of
 * MERCANTBILITY or  FITNESS FOR A PARTICULAR PURPOSE. See the 
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>/
 *
 * 
 *
*/


#include  <linux/module.h>
#include  <linux/fs.h>
#include  <linux/cdev.h>
#include  <linux/device.h>
#include  <linux/uaccess.h>
#include  <linux/io.h>
#include <linux/delay.h>

MODULE_AUTHOR("kenta Obata and Ryuichi Ueda");
MODULE_DESCRIPTION("drive for LED contral");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;

static volatile u32 *gpio_base = NULL;

static int LED[3] = {16, 23, 24};
int i;

static ssize_t  led_write(struct file* filp, const char* buf, size_t count, loff_t* pos)
{
	
	char c;
	if(copy_from_user(&c,buf,sizeof(char)))
		return -EFAULT;

	if(c == 'r') {
        	int ib = 0;
		while (ib < 5) {
			gpio_base[7] = 1 << 16;
			mdelay(2000);
			gpio_base[10] = 1 << 16;
			mdelay(500);
			ib++;
		}
	}

	 else if (c == 'g') { 
		int ig = 0;
		while (ig < 5) {
			gpio_base[7] = 1 << 24;
			mdelay(2000);
			gpio_base[10] = 1 << 24;
			mdelay(500);
			ig++;
		}
	}

 	else if (c == 'b') {
		int ib = 0;
		while(ib < 5) {
			gpio_base[7] = 1 << 23;
			mdelay(2000);
			gpio_base[10] = 1 << 23;
			mdelay(500);
			ib++;
		}
	}

	else if(c == 'A') {
		int iA = 0;
		while(iA < 10) {
			gpio_base[7] = 1 << 16;
			gpio_base[7] = 1 << 24;
			gpio_base[7] = 1 << 23;
			mdelay(200);
			gpio_base[10] = 1 << 16;
			gpio_base[10] = 1 << 24;
			gpio_base[10] = 1 << 23;
			mdelay(200);
			iA++;
		}
	}

return 1;

}

static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.write = led_write,
       
};

static int __init init_mod(void)
{	
	int retval;

	retval = alloc_chrdev_region(&dev,  0, 1, "myled");
	if(retval < 0)  {	
		printk(KERN_ERR "alloc _chrdev_region faile:d \n");
		return retval;
	}

	printk(KERN_INFO "%s is loaded major:%d\n", __FILE__, MAJOR(dev));
	
	cdev_init(&cdv, &led_fops);
	cdv.owner = THIS_MODULE;
	retval = cdev_add(&cdv, dev, 1);
	if(retval < 0) {
		printk(KERN_ERR "cdev_add failed, major:%d, minor:%d", MAJOR(dev), MINOR(dev));
		return retval;
	}

	cls = class_create(THIS_MODULE, "myled");
	if(IS_ERR(cls)) {
		printk(KERN_ERR"class_create failed");
		return PTR_ERR(cls);
	}

	device_create(cls, NULL, dev, NULL, "myled%d", MINOR(dev));
	
	gpio_base = ioremap_nocache(0xfe200000, 0x0A);
	

	for (i = 0; i < 2; i++) {
	const u32 led = LED[i];
	const u32 index = led/10;
	const u32 shift = (led%10)*3;
	const u32 mask = ~(0x7 << shift);
	gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift);
	}

	return 0;
}



static void __exit cleanup_mod(void)
{
	cdev_del(&cdv);
	device_destroy(cls, dev);
	class_destroy(cls);
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "%s is unloaded. magor:%d\n", __FILE__, MAJOR(dev));

}

module_init(init_mod);
module_exit(cleanup_mod);

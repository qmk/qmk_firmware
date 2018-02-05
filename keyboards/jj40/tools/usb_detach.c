/* Found at https://www.linuxquestions.org/questions/linux-hardware-18/how-to-unclaim-usb-device-558138/#post3406986 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/ioctl.h>
#include <linux/usbdevice_fs.h>

int main(int argc, char**argv)
{
        struct usbdevfs_ioctl command;
        int ret;
        int fd;
        int i;
        if (argc>1) {
                fd = open(argv[1],O_RDWR);
                if (fd<1){
                        perror("unable to open file");
                        return 1;
                }
                for (i=0;i<255;i++){ // hack: should fetch how many interface there is.
                        command.ifno = i;
                        command.ioctl_code = USBDEVFS_DISCONNECT;
                        command.data = NULL;
                        ret = ioctl(fd, USBDEVFS_IOCTL, &command);
                        if(ret!=-1)
                                printf("un claimed interface %d %d\n",i,ret);
                }
        } else {
                printf ("usage: %s /dev/bus/usb/BUS/DEVICE\n",argv[0]);
                printf("Release all interfaces of this usb device for usage in virtualisation\n");
        }
}
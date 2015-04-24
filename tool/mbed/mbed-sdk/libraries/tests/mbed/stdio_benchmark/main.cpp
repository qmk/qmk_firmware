#include "mbed.h"

#define TEST_STDIO 0

int main() {
    printf("\r\n\r\n*** Start of memory write test (2K bytes) ***\r\n");

    // dummy data
    char buf[2048];
    int index = 0;
    for (index = 0; index < 2048; index++) {
        buf[index] = ~index & 0xFF;
    }

    // Run the timed write test
    float starttime, duration;
    Timer t;
    t.start();
    starttime = t.read();

#if TEST_STDIO
    LocalFileSystem local("local");
    FILE *fp = fopen("/local/test.dat", "w");
    fwrite(buf, sizeof(buf[0]), sizeof(buf)/sizeof(buf[0]), fp);
    fclose(fp);
#else
    FILEHANDLE fh = local_file_open("test.dat", O_WRONLY);
    LocalFileHandle lfh(fh);
    lfh.write(buf, sizeof(buf));
    lfh.close();
#endif

    duration = t.read() - starttime;
    printf("Write completed in %.2f seconds. Average throughput = %.0f bytes/second.\r\n", duration, 2048/duration);
}

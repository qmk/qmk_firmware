#include <algorithm>
#include "mbed.h"
#include "EthernetInterface.h"
#include "test_env.h"

namespace {
    // Test connection information
    const char *HTTP_SERVER_NAME = "developer.mbed.org";
    const char *HTTP_SERVER_FILE_PATH = "/media/uploads/mbed_official/hello.txt";
    const int HTTP_SERVER_PORT = 80;
    const int RECV_BUFFER_SIZE = 512;

    // Test related data
    const char *HTTP_OK_STR = "200 OK";
    const char *HTTP_HELLO_STR = "Hello world!";

    // Test buffers
    char buffer[RECV_BUFFER_SIZE] = {0};
}

bool find_substring(const char *first, const char *last, const char *s_first, const char *s_last) {
    const char *f = std::search(first, last, s_first, s_last);
    return (f != last);
}

int main() {
    MBED_HOSTTEST_TIMEOUT(20);
    MBED_HOSTTEST_SELECT(default_auto);
    MBED_HOSTTEST_DESCRIPTION(TCP client hello world);
    MBED_HOSTTEST_START("NET_1");

    bool result = false;
    EthernetInterface eth;
    eth.init(); //Use DHCP
    eth.connect();
    printf("TCP client IP Address is %s\r\n", eth.getIPAddress());

    TCPSocketConnection sock;
    if (sock.connect(HTTP_SERVER_NAME, HTTP_SERVER_PORT) == 0) {
        printf("HTTP: Connected to %s:%d\r\n", HTTP_SERVER_NAME, HTTP_SERVER_PORT);

        // We are constructing GET command like this:
        // GET http://developer.mbed.org/media/uploads/mbed_official/hello.txt HTTP/1.0\n\n
        strcpy(buffer, "GET http://");
        strcat(buffer, HTTP_SERVER_NAME);
        strcat(buffer, HTTP_SERVER_FILE_PATH);
        strcat(buffer, " HTTP/1.0\n\n");
        // Send GET command
        sock.send_all(buffer, strlen(buffer));

        // Server will respond with HTTP GET's success code
        bool found_200_ok = false;
        {
            const int ret = sock.receive(buffer, sizeof(buffer) - 1);
            buffer[ret] = '\0';
            // Find 200 OK HTTP status in reply
            found_200_ok = find_substring(buffer, buffer + ret, HTTP_OK_STR, HTTP_OK_STR + strlen(HTTP_OK_STR));
            printf("HTTP: Received %d chars from server\r\n", ret);
            printf("HTTP: Received 200 OK status ... %s\r\n", found_200_ok ? "[OK]" : "[FAIL]");
            printf("HTTP: Received massage:\r\n\r\n");
            printf("%s", buffer);
        }

        // Server will respond with requested file content
        bool found_hello = false;
        {
            const int ret = sock.receive(buffer, sizeof(buffer) - 1);
            buffer[ret] = '\0';
            // Find Hello World! in reply
            found_hello = find_substring(buffer, buffer + ret, HTTP_HELLO_STR, HTTP_HELLO_STR + strlen(HTTP_HELLO_STR));
            printf("HTTP: Received %d chars from server\r\n", ret);
            printf("HTTP: Received '%s' status ... %s\r\n", HTTP_HELLO_STR, found_hello ? "[OK]" : "[FAIL]");
            printf("HTTP: Received massage:\r\n\r\n");
            printf("%s", buffer);
        }

        if (found_200_ok && found_hello) {
            result = true;
        }
    }

    sock.close();
    eth.disconnect();
    MBED_HOSTTEST_RESULT(result);
}

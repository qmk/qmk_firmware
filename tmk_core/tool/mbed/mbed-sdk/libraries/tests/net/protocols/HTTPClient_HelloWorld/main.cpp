#include "mbed.h"
#include "test_env.h"
#include "EthernetInterface.h"
#include "HTTPClient.h"


namespace {
    const int BUFFER_SIZE = 512;
}

int main() {
    MBED_HOSTTEST_TIMEOUT(15);
    MBED_HOSTTEST_SELECT(default_auto);
    MBED_HOSTTEST_DESCRIPTION(HTTP client hello world);
    MBED_HOSTTEST_START("NET_7");

    char http_request_buffer[BUFFER_SIZE + 1] = {0};
    HTTPClient http;
    EthernetInterface eth;
    eth.init(); //Use DHCP
    eth.connect();

    //GET data
    {
        bool result = true;
        const char *url_hello_txt = "http://developer.mbed.org/media/uploads/donatien/hello.txt";
        printf("HTTP_GET: Trying to fetch page '%s'...\r\n", url_hello_txt);
        HTTPResult ret = http.get(url_hello_txt, http_request_buffer, BUFFER_SIZE);
        if (ret == HTTP_OK) {
            printf("HTTP_GET: Read %d chars: '%s' ... [OK]\r\n", strlen(http_request_buffer), http_request_buffer);
        } else {
            printf("HTTP_GET: Error(%d). HTTP error(%d) ... [FAIL]\r\n", ret, http.getHTTPResponseCode());
            result = false;
        }

        if (result == false) {
            eth.disconnect();
            MBED_HOSTTEST_RESULT(false);
        }
    }

    //POST data
    {
        bool result = true;
        const char *url_httpbin_post = "http://httpbin.org/post";
        HTTPText text(http_request_buffer, BUFFER_SIZE);
        HTTPMap map;
        map.put("Hello", "World");
        map.put("test", "1234");
        printf("HTTP_POST: Trying to post data to '%s' ...\r\n", url_httpbin_post);
        HTTPResult ret = http.post(url_httpbin_post, map, &text);
        if (ret == HTTP_OK) {
            printf("HTTP_POST: Read %d chars ... [OK]\r\n", strlen(http_request_buffer));
            printf("HTTP_POST: %s\r\n", http_request_buffer);
        } else {
            printf("HTTP_GET: Error(%d). HTTP error(%d) ... [FAIL]\r\n", ret, http.getHTTPResponseCode());
            result = false;
        }

        if (result == false) {
            eth.disconnect();
            MBED_HOSTTEST_RESULT(false);
        }
    }
    eth.disconnect();
    MBED_HOSTTEST_RESULT(true);
}

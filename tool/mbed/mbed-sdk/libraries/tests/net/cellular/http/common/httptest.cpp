#include "mbed.h"
#include "CellularModem.h"
#include "HTTPClient.h"
#include "httptest.h"

int httptest(CellularModem& modem, const char* apn, const char* username, const char* password)
{
    printf("Connecting...\n");

    HTTPClient http;
    char str[512];

    modem.power(true);
    Thread::wait(1000);
    int ret = modem.connect(apn, username, password);
    if(ret)
    {
      printf("Could not connect\n");
      return false;
    }

    //GET data
    printf("Trying to fetch page...\n");
    ret = http.get("http://mbed.org/media/uploads/donatien/hello.txt", str, 128);
    if (!ret)
    {
      printf("Page fetched successfully - read %d characters\n", strlen(str));
      printf("Result: %s\n", str);
    }
    else
    {
      printf("Error - ret = %d - HTTP return code = %d\n", ret, http.getHTTPResponseCode());
      modem.disconnect();
      return false;
    }

    //POST data
    HTTPMap map;
    HTTPText text(str, 512);
    map.put("Hello", "World");
    map.put("test", "1234");
    printf("Trying to post data...\n");
    ret = http.post("http://httpbin.org/post", map, &text);
    if (!ret)
    {
      printf("Executed POST successfully - read %d characters\n", strlen(str));
      printf("Result: %s\n", str);
    }
    else
    {
      printf("Error - ret = %d - HTTP return code = %d\n", ret, http.getHTTPResponseCode());
      modem.disconnect();
      return false;
    }

    modem.disconnect();
    return true;
}

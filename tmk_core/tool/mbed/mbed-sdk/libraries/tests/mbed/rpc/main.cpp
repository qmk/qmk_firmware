#include "mbed.h"
#include "test_env.h"
#include "mbed_rpc.h"

void foo(Arguments *args, Reply *reply) {
    reply->putData<float>(args->getArg<float>() * 3.3);
}

bool rpc_test(const char *input, const char *expected) {
    char outbuf[RPC_MAX_STRING] = {0};
    bool result = RPC::call(input, outbuf);
    printf("RPC: %s -> ", input);

    if (result == false) {
        printf("Procedure call ... [FAIL]\r\n");
    } else if (strncmp(outbuf, expected, RPC_MAX_STRING) != 0) {
        printf("'%s' != '%s' ... [FAIL]\r\n", outbuf, expected);
        result = false;
    } else {
        printf("'%s' ... [OK]\r\n", outbuf);
    }
    return result;
}

#define RPC_TEST(INPUT,EXPECTED) result = result && rpc_test(INPUT,EXPECTED); if (result == false) { notify_completion(result); exit(1); }

int main() {
    float f = 0;
    bool result = true;
    // Variable
    RPCVariable<float> rpc_f(&f, "f");
    RPC_TEST("/f/write 1", "");
    RPC_TEST("/f/read", "1");

    // Function
    RPCFunction rpc_foo(&foo, "foo");
#if defined(TOOLCHAIN_ARM_MICRO)
    RPC_TEST("/foo/run 1", "3.299999952316284");
#else
    RPC_TEST("/foo/run 1", "3.2999999523162842");
#endif

    // Class
    RPC::add_rpc_class<RpcDigitalOut>();
    RPC_TEST("/DigitalOut/new LED2 led2", "led2");
    RPC_TEST("/led2/write 1", "");
    RPC_TEST("/led2/read", "1");

    // Instance
    RpcDigitalOut rpc_led(LED1, "led1");
    RPC_TEST("/led1/write 1", "");
    RPC_TEST("/led1/read", "1");

    // Introspection
    RPC_TEST("/", "led1 led2 foo f DigitalOut RPC");
    RPC_TEST("/f", "read write delete");
    RPC_TEST("/foo", "run delete");
    RPC_TEST("/DigitalOut", "new");
    RPC_TEST("/led1", "write read delete");

    // Delete instance
    RPC_TEST("/led2/delete", "");
    RPC_TEST("/", "led1 foo f DigitalOut RPC");

    notify_completion(result);
    return 0;
}

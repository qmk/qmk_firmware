/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MBED_CLASSES_H
#define MBED_CLASSES_H

#include "rpc.h"

namespace mbed {

class RpcDigitalOut : public RPC {
public:
    RpcDigitalOut(PinName a0, const char *name=NULL) : RPC(name), o(a0) {}

    void write(int a0) {o.write(a0);}
    int read(void) {return o.read();}

    virtual const struct rpc_method *get_rpc_methods() {
        static const rpc_method rpc_methods[] = {
            {"write", rpc_method_caller<RpcDigitalOut, int, &RpcDigitalOut::write>},
            {"read", rpc_method_caller<int, RpcDigitalOut, &RpcDigitalOut::read>},
            RPC_METHOD_SUPER(RPC)
        };
        return rpc_methods;
    }
    static struct rpc_class *get_rpc_class() {
        static const rpc_function funcs[] = {
            {"new", rpc_function_caller<const char*, PinName, const char*, &RPC::construct<RpcDigitalOut, PinName, const char*> >},
            RPC_METHOD_END
        };
        static rpc_class c = {"DigitalOut", funcs, NULL};
        return &c;
    }
private:
    DigitalOut o;
};

class RpcDigitalIn : public RPC {
public:
    RpcDigitalIn(PinName a0, const char *name=NULL) : RPC(name), o(a0) {}

    int read(void) {return o.read();}

    virtual const struct rpc_method *get_rpc_methods() {
        static const rpc_method rpc_methods[] = {
            {"read", rpc_method_caller<int, RpcDigitalIn, &RpcDigitalIn::read>},
            RPC_METHOD_SUPER(RPC)
        };
        return rpc_methods;
    }
    static struct rpc_class *get_rpc_class() {
        static const rpc_function funcs[] = {
            {"new", rpc_function_caller<const char*, PinName, const char*, &RPC::construct<RpcDigitalIn, PinName, const char*> >},
            RPC_METHOD_END
        };
        static rpc_class c = {"DigitalIn", funcs, NULL};
        return &c;
    }
private:
    DigitalIn o;
};

class RpcDigitalInOut : public RPC {
public:
    RpcDigitalInOut(PinName a0, const char *name=NULL) : RPC(name), o(a0) {}

    int read(void) {return o.read();}
    void write(int a0) {o.write(a0);}
    void input(void) {o.input();}
    void output(void) {o.output();}

    virtual const struct rpc_method *get_rpc_methods() {
        static const rpc_method rpc_methods[] = {
            {"read", rpc_method_caller<int, RpcDigitalInOut, &RpcDigitalInOut::read>},
            {"write", rpc_method_caller<RpcDigitalInOut, int, &RpcDigitalInOut::write>},
            {"input", rpc_method_caller<RpcDigitalInOut, &RpcDigitalInOut::input>},
            {"output", rpc_method_caller<RpcDigitalInOut, &RpcDigitalInOut::output>},
            RPC_METHOD_SUPER(RPC)
        };
        return rpc_methods;
    }
    static struct rpc_class *get_rpc_class() {
        static const rpc_function funcs[] = {
            {"new", rpc_function_caller<const char*, PinName, const char*, &RPC::construct<RpcDigitalInOut, PinName, const char*> >},
            RPC_METHOD_END
        };
        static rpc_class c = {"DigitalInOut", funcs, NULL};
        return &c;
    }
private:
    DigitalInOut o;
};

#if DEVICE_ANALOGIN
class RpcAnalogIn : public RPC {
public:
    RpcAnalogIn(PinName a0, const char *name=NULL) : RPC(name), o(a0) {}

    float read(void) {return o.read();}
    unsigned short read_u16(void) {return o.read_u16();}

    virtual const struct rpc_method *get_rpc_methods() {
        static const rpc_method rpc_methods[] = {
            {"read", rpc_method_caller<float, RpcAnalogIn, &RpcAnalogIn::read>},
            {"read_u16", rpc_method_caller<unsigned short, RpcAnalogIn, &RpcAnalogIn::read_u16>},
            RPC_METHOD_SUPER(RPC)
        };
        return rpc_methods;
    }
    static struct rpc_class *get_rpc_class() {
        static const rpc_function funcs[] = {
            {"new", rpc_function_caller<const char*, PinName, const char*, &RPC::construct<RpcAnalogIn, PinName, const char*> >},
            RPC_METHOD_END
        };
        static rpc_class c = {"AnalogIn", funcs, NULL};
        return &c;
    }
private:
    AnalogIn o;
};
#endif

#if DEVICE_ANALOGOUT
class RpcAnalogOut : public RPC {
public:
    RpcAnalogOut(PinName a0, const char *name=NULL) : RPC(name), o(a0) {}

    float read(void) {return o.read();}
    void write(float a0) {o.write(a0);}
    void write_u16(unsigned short a0) {o.write_u16(a0);}

    virtual const struct rpc_method *get_rpc_methods() {
        static const rpc_method rpc_methods[] = {
            {"read", rpc_method_caller<float, RpcAnalogOut, &RpcAnalogOut::read>},
            {"write", rpc_method_caller<RpcAnalogOut, float, &RpcAnalogOut::write>},
            {"write_u16", rpc_method_caller<RpcAnalogOut, unsigned short, &RpcAnalogOut::write_u16>},
            RPC_METHOD_SUPER(RPC)
        };
        return rpc_methods;
    }
    static struct rpc_class *get_rpc_class() {
        static const rpc_function funcs[] = {
            {"new", rpc_function_caller<const char*, PinName, const char*, &RPC::construct<RpcAnalogOut, PinName, const char*> >},
            RPC_METHOD_END
        };
        static rpc_class c = {"AnalogOut", funcs, NULL};
        return &c;
    }
private:
    AnalogOut o;
};
#endif

#if DEVICE_PWMOUT
class RpcPwmOut : public RPC {
public:
    RpcPwmOut(PinName a0, const char *name=NULL) : RPC(name), o(a0) {}

    float read(void) {return o.read();}
    void write(float a0) {o.write(a0);}
    void period(float a0) {o.period(a0);}
    void period_ms(int a0) {o.period_ms(a0);}
    void pulsewidth(float a0) {o.pulsewidth(a0);}
    void pulsewidth_ms(int a0) {o.pulsewidth_ms(a0);}

    virtual const struct rpc_method *get_rpc_methods() {
        static const rpc_method rpc_methods[] = {
            {"read", rpc_method_caller<float, RpcPwmOut, &RpcPwmOut::read>},
            {"write", rpc_method_caller<RpcPwmOut, float, &RpcPwmOut::write>},
            {"period", rpc_method_caller<RpcPwmOut, float, &RpcPwmOut::period>},
            {"period_ms", rpc_method_caller<RpcPwmOut, int, &RpcPwmOut::period_ms>},
            {"pulsewidth", rpc_method_caller<RpcPwmOut, float, &RpcPwmOut::pulsewidth>},
            {"pulsewidth_ms", rpc_method_caller<RpcPwmOut, int, &RpcPwmOut::pulsewidth_ms>},
            RPC_METHOD_SUPER(RPC)
        };
        return rpc_methods;
    }
    static struct rpc_class *get_rpc_class() {
        static const rpc_function funcs[] = {
            {"new", rpc_function_caller<const char*, PinName, const char*, &RPC::construct<RpcPwmOut, PinName, const char*> >},
            RPC_METHOD_END
        };
        static rpc_class c = {"PwmOut", funcs, NULL};
        return &c;
    }
private:
    PwmOut o;
};
#endif

#if DEVICE_SPI
class RpcSPI : public RPC {
public:
    RpcSPI(PinName a0, PinName a1, PinName a2, const char *name=NULL) : RPC(name), o(a0, a1, a2) {}

    void format(int a0, int a1) {o.format(a0, a1);}
    void frequency(int a0) {o.frequency(a0);}
    int write(int a0) {return o.write(a0);}

    virtual const struct rpc_method *get_rpc_methods() {
        static const rpc_method rpc_methods[] = {
            {"format", rpc_method_caller<RpcSPI, int, int, &RpcSPI::format>},
            {"frequency", rpc_method_caller<RpcSPI, int, &RpcSPI::frequency>},
            {"write", rpc_method_caller<int, RpcSPI, int, &RpcSPI::write>},
            RPC_METHOD_SUPER(RPC)
        };
        return rpc_methods;
    }
    static struct rpc_class *get_rpc_class() {
        static const rpc_function funcs[] = {
            {"new", rpc_function_caller<const char*, PinName, PinName, PinName, const char*, &RPC::construct<RpcSPI, PinName, PinName, PinName, const char*> >},
            RPC_METHOD_END
        };
        static rpc_class c = {"SPI", funcs, NULL};
        return &c;
    }
private:
    SPI o;
};
#endif

#if DEVICE_SERIAL
class RpcSerial : public RPC {
public:
    RpcSerial(PinName a0, PinName a1, const char *name=NULL) : RPC(name), o(a0, a1) {}

    void baud(int a0) {o.baud(a0);}
    int readable(void) {return o.readable();}
    int writeable(void) {return o.writeable();}
    int putc(int a0) {return o.putc(a0);}
    int getc(void) {return o.getc();}
    int puts(const char * a0) {return o.puts(a0);}

    virtual const struct rpc_method *get_rpc_methods() {
        static const rpc_method rpc_methods[] = {
            {"baud", rpc_method_caller<RpcSerial, int, &RpcSerial::baud>},
            {"readable", rpc_method_caller<int, RpcSerial, &RpcSerial::readable>},
            {"writeable", rpc_method_caller<int, RpcSerial, &RpcSerial::writeable>},
            {"putc", rpc_method_caller<int, RpcSerial, int, &RpcSerial::putc>},
            {"getc", rpc_method_caller<int, RpcSerial, &RpcSerial::getc>},
            {"puts", rpc_method_caller<int, RpcSerial, const char *, &RpcSerial::puts>},
            RPC_METHOD_SUPER(RPC)
        };
        return rpc_methods;
    }
    static struct rpc_class *get_rpc_class() {
        static const rpc_function funcs[] = {
            {"new", rpc_function_caller<const char*, PinName, PinName, const char*, &RPC::construct<RpcSerial, PinName, PinName, const char*> >},
            RPC_METHOD_END
        };
        static rpc_class c = {"Serial", funcs, NULL};
        return &c;
    }
private:
    Serial o;
};
#endif

class RpcTimer : public RPC {
public:
    RpcTimer(const char *name=NULL) : RPC(name), o() {}

    void start(void) {o.start();}
    void stop(void) {o.stop();}
    void reset(void) {o.reset();}
    float read(void) {return o.read();}
    int read_ms(void) {return o.read_ms();}
    int read_us(void) {return o.read_us();}

    virtual const struct rpc_method *get_rpc_methods() {
        static const rpc_method rpc_methods[] = {
            {"start", rpc_method_caller<RpcTimer, &RpcTimer::start>},
            {"stop", rpc_method_caller<RpcTimer, &RpcTimer::stop>},
            {"reset", rpc_method_caller<RpcTimer, &RpcTimer::reset>},
            {"read", rpc_method_caller<float, RpcTimer, &RpcTimer::read>},
            {"read_ms", rpc_method_caller<int, RpcTimer, &RpcTimer::read_ms>},
            {"read_us", rpc_method_caller<int, RpcTimer, &RpcTimer::read_us>},
            RPC_METHOD_SUPER(RPC)
        };
        return rpc_methods;
    }
    static struct rpc_class *get_rpc_class() {
        static const rpc_function funcs[] = {
            {"new", rpc_function_caller<const char*, const char*, &RPC::construct<RpcTimer, const char*> >},
            RPC_METHOD_END
        };
        static rpc_class c = {"Timer", funcs, NULL};
        return &c;
    }
private:
    Timer o;
};

}

#endif

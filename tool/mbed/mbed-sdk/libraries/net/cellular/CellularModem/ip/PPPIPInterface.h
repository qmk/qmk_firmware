/* PPPIPInterface.h */
/* Copyright (C) 2012 mbed.org, MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef PPPIPINTERFACE_H_
#define PPPIPINTERFACE_H_

#include "core/fwk.h"

#include "LwIPInterface.h"

#include "lwip/sio.h"

namespace rtos {
class Semaphore;
}
using namespace rtos;

#define DEFAULT_MSISDN_GSM    "*99#"
#define DEFAULT_MSISDN_CDMA   "#777"

/** Interface using PPP to connect to an IP-based network
 *
 */
class PPPIPInterface : public LwIPInterface
{
public:
    PPPIPInterface(IOStream* pStream);
    virtual ~PPPIPInterface();

    int init(); //Init PPP-specific stuff, create the right bindings, etc
    int setup(const char* user, const char* pw, const char* msisdn); //Setup authentication
    virtual int connect();
    virtual int disconnect();

private:
    int cleanupLink();

    static void linkStatusCb(void *ctx, int errCode, void *arg); //PPP link status
    Semaphore m_linkStatusSphre;
    int m_pppErrCode;

    IOStream* m_pStream; //Serial stream
    bool m_streamAvail;
    const char* m_msisdn;

    int m_pppd;

    friend u32_t sio_write(sio_fd_t fd, u8_t *data, u32_t len);
    friend u32_t sio_read(sio_fd_t fd, u8_t *data, u32_t len);
    friend void sio_read_abort(sio_fd_t fd);
};

#endif /* PPPIPINTERFACE_H_ */

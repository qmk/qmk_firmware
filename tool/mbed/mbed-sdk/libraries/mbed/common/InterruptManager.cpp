#include "cmsis.h"
#if defined(NVIC_NUM_VECTORS)

#include "InterruptManager.h"
#include <string.h>

#define CHAIN_INITIAL_SIZE    4

namespace mbed {

typedef void (*pvoidf)(void);

InterruptManager* InterruptManager::_instance = (InterruptManager*)NULL;

InterruptManager* InterruptManager::get() {
    if (NULL == _instance)
        _instance = new InterruptManager();
    return _instance;
}

InterruptManager::InterruptManager() {
    memset(_chains, 0, NVIC_NUM_VECTORS * sizeof(CallChain*));
}

void InterruptManager::destroy() {
    // Not a good idea to call this unless NO interrupt at all
    // is under the control of the handler; otherwise, a system crash
    // is very likely to occur
    if (NULL != _instance) {
        delete _instance;
        _instance = (InterruptManager*)NULL;
    }
}

InterruptManager::~InterruptManager() {
    for(int i = 0; i < NVIC_NUM_VECTORS; i++)
        if (NULL != _chains[i])
            delete _chains[i];
}

bool InterruptManager::must_replace_vector(IRQn_Type irq) {
    int irq_pos = get_irq_index(irq);

    if (NULL == _chains[irq_pos]) {
        _chains[irq_pos] = new CallChain(CHAIN_INITIAL_SIZE);
        _chains[irq_pos]->add((pvoidf)NVIC_GetVector(irq));
        return true;
    }
    return false;
}

pFunctionPointer_t InterruptManager::add_common(void (*function)(void), IRQn_Type irq, bool front) {
    int irq_pos = get_irq_index(irq);
    bool change = must_replace_vector(irq);

    pFunctionPointer_t pf = front ? _chains[irq_pos]->add_front(function) : _chains[irq_pos]->add(function);
    if (change)
        NVIC_SetVector(irq, (uint32_t)&InterruptManager::static_irq_helper);
    return pf;
}

bool InterruptManager::remove_handler(pFunctionPointer_t handler, IRQn_Type irq) {
    int irq_pos = get_irq_index(irq);

    if (NULL == _chains[irq_pos])
        return false;
    if (!_chains[irq_pos]->remove(handler))
        return false;
    // If there's a single function left in the chain, swith the interrupt vector
    // to call that function directly. This way we save both time and space.
    if (_chains[irq_pos]->size() == 1 && NULL != _chains[irq_pos]->get(0)->get_function()) {
        NVIC_SetVector(irq, (uint32_t)_chains[irq_pos]->get(0)->get_function());
        delete _chains[irq_pos];
        _chains[irq_pos] = (CallChain*) NULL;
    }
    return true;
}

void InterruptManager::irq_helper() {
    _chains[__get_IPSR()]->call();
}

int InterruptManager::get_irq_index(IRQn_Type irq) {
    return (int)irq + NVIC_USER_IRQ_OFFSET;
}

void InterruptManager::static_irq_helper() {
    InterruptManager::get()->irq_helper();
}

} // namespace mbed

#endif

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
#include "rpc.h"

using namespace std;

namespace mbed {

RPC::RPC(const char *name) {
    _from_construct = false;
    if (name != NULL) {
        _name = new char[strlen(name) + 1];
        strcpy(_name, name);
    } else {
        _name = new char[12];
        sprintf(_name, "obj%p", this);
    }
    // put this object at head of the list
    _next = _head;
    _head = this;
}

RPC::~RPC() {
    // remove this object from the list
    if (_head == this) { // first in the list, so just drop me
        _head = _next;
    } else {            // find the object before me, then drop me
        RPC* p = _head;
        while (p->_next != this) {
            p = p->_next;
        }
        p->_next = _next;
    }
}

const rpc_method *RPC::get_rpc_methods() {
    static const rpc_method methods[] = {
        {"delete", rpc_method_caller<RPC, &RPC::delete_self> },
        RPC_METHOD_END
    };
    return methods;
}

RPC *RPC::lookup(const char *name) {
    size_t len = strlen(name);
    for (RPC *p = _head; p != NULL; p = p->_next) {
        /* Check that p->_name matches name and is the correct length */
        if (strncmp(p->_name, name, len) == 0 && (strlen(p->_name) == len)) {
            return p;
        }
    }
    return NULL;
}

void RPC::delete_self() {
    delete[] _name;
    if (_from_construct) {
        delete this;
    }
}

void RPC::list_objs(Arguments *args, Reply *result) {
    for (RPC *ptr = RPC::_head; ptr != NULL; ptr = ptr->_next) {
        if (ptr->_from_construct) {
            result->putData<const char*>(ptr->_name);
        }
    }
}

void RPC::clear(Arguments*, Reply*) {
    RPC *ptr = RPC::_head;
    while (ptr != NULL) {
        RPC *tmp = ptr;
        ptr = ptr->_next;
        delete[] tmp->_name;
        if (tmp->_from_construct) {
            delete tmp;
        }
    }
}

const rpc_function RPC::_RPC_funcs[] = {
    {"clear", &RPC::clear },
    { "objects", &RPC::list_objs },
    RPC_METHOD_END
};

rpc_class RPC::_RPC_class = { "RPC", _RPC_funcs, NULL };

RPC *RPC::_head = NULL;

rpc_class *RPC::_classes = &_RPC_class;

bool RPC::call(const char *request, char *reply) {
    if (request == NULL) return false;

    Arguments args(request);
    Reply r(reply);

    /* If there's no name print object and class names to result */
    if (args.obj_name == NULL) {
        for (RPC *p = RPC::_head; p != NULL; p = p->_next) {
            r.putData<const char*>(p->_name);
        }
        for (rpc_class *c = RPC::_classes; c != NULL; c = c->next) {
            r.putData<const char*>(c->name);
        }
        return true;
    }

    /* First try matching an instance */
    RPC *p = lookup(args.obj_name);
    if (p != NULL) {
        /* Get the list of methods we support */
        const rpc_method *cur_method = p->get_rpc_methods();

        /* When there's no method print method names to result */
        if (args.method_name == NULL) {
            while (true) {
                for (; cur_method->name != NULL; cur_method++) {
                    r.putData<const char*>(cur_method->name);
                }

                /* write_name_arr's args are references, so result and cur_method will have changed */
                if (cur_method->super != 0) {
                    cur_method = cur_method->super(p);
                } else {
                    return true;
                }
            }
        }

        /* Look through the methods for the one whose name matches */
        while (true) {
            for (; cur_method->name != NULL; cur_method++) {
                if (strcmp(cur_method->name, args.method_name) == 0) {
                    (cur_method->method_caller)(p, &args, &r);
                    return true;
                }
            }

            if (cur_method->super != 0) {
                cur_method = cur_method->super(p);
            } else {
                /* end of methods and no match */
                return false;
            }

        }
    }

    /* Then try a class */
    for (const rpc_class *q = _classes; q != NULL; q = q->next) {
        if (strcmp(q->name, args.obj_name) == 0) {
            /* Matched the class name, so get its functions */
            const rpc_function *cur_func = q->static_functions;
            if (args.method_name == NULL) {
                for (; cur_func->name != NULL; cur_func++) {
                    r.putData<const char*>(cur_func->name);
                }
                return true;
            } else {
                /* Otherwise call the appropriate function */
                for (; cur_func->name != NULL; cur_func++) {
                    if (strcmp(cur_func->name, args.method_name) == 0) {
                        (cur_func->function_caller)(&args, &r);
                        return true;
                    }
                }
                return false;
            }
        }
    }

    return false;
}

} // namespace mbed

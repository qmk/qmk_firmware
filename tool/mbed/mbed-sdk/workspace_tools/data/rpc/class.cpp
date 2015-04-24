class Rpc{{name}} : public RPC {
public:
    Rpc{{name}}({{cons_proto}}) : RPC(name), o({{cons_call}}) {}

    {{methods}}

    virtual const struct rpc_method *get_rpc_methods() {
        static const rpc_method rpc_methods[] = {
            {{rpc_methods}},
            RPC_METHOD_SUPER(RPC)
        };
        return rpc_methods;
    }
    static struct rpc_class *get_rpc_class() {
        static const rpc_function funcs[] = {
            {"new", rpc_function_caller<const char*, {{cons_type}}, &RPC::construct<Rpc{{name}}, {{cons_type}}> >},
            RPC_METHOD_END
        };
        static rpc_class c = {"{{name}}", funcs, NULL};
        return &c;
    }
private:
    {{name}} o;
};

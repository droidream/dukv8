//
// Created by Jiang Lu on 6/3/15.
//

#ifndef DUKV8_DUKSTACKSCOPE_H
#define DUKV8_DUKSTACKSCOPE_H

#include <duktape.h>

#define DUK_STACK_SCOPE(ctx) v8::internal::DukStackScope __dss_##__LINE__(ctx)

namespace v8 {
namespace internal {

class DukStackScope {
public:
    DukStackScope(duk_context *ctx) :
            ctx_(ctx), top_(duk_get_top(ctx)) {
    }

    ~DukStackScope() {
        duk_set_top(ctx_, top_);
    }

private:
    duk_context *ctx_;
    duk_idx_t top_;
};

}
}

#endif //DUKV8_DUKSTACKSCOPE_H

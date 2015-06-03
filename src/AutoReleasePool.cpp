//
// Created by Jiang Lu on 6/3/15.
//

#include <duktape.h>
#include <dukv8/AutoReleasePool.h>
#include <dukv8/Isolate.h>

namespace v8 {
namespace internal {

void *AutoReleasePool::AutoRelease(void *heap_ptr) {
    Isolate *isolate = Isolate::GetCurrent();
    duk_context *ctx = isolate->GetDukContext();

    duk_push_global_stash(ctx);
    duk_get_prop_string(ctx, -1, "__auto_releases");
    if (duk_is_undefined(ctx, -1)) {
        duk_pop(ctx);
        duk_push_array(ctx);
        duk_dup_top(ctx);
        duk_put_prop_string(ctx, -3, "__auto_releases");
    }

    duk_size_t len = duk_get_length(ctx, -1);
    duk_push_heapptr(ctx, heap_ptr);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) len);
    duk_pop_2(ctx);

    return heap_ptr;
}

void AutoReleasePool::Release() {
    Isolate *isolate = Isolate::GetCurrent();
    duk_context *ctx = isolate->GetDukContext();
    duk_push_global_stash(ctx);
    duk_del_prop_string(ctx, -1, "__auto_releases");
    duk_pop(ctx);
}

}
}

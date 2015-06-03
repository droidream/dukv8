//
// Created by Jiang Lu on 6/2/15.
//

#include <dukv8/GlobalStash.h>
#include <dukv8/Isolate.h>

namespace v8 {
namespace internal {

GlobalStash::GlobalStash(const char *name) : name_(name) {
    Isolate *isolate = Isolate::GetCurrent();
    duk_context *ctx = isolate->GetDukContext();

    // 每个 global 对象对应一个 stash 对象
    duk_push_global_stash(ctx);
    duk_get_prop_string(ctx, -1, name_);

    if (duk_is_undefined(ctx, -1)) {
        duk_pop(ctx);

        // Create a new array with one `0` at index `0`.
        duk_push_array(ctx);
        duk_push_int(ctx, 0);
        duk_put_prop_index(ctx, -2, 0);

        // Store it as "name_" in the heap stash
        duk_put_prop_string(ctx, -2, name_);
    } else {
        duk_pop(ctx);
    }

    duk_pop(ctx);
}

int GlobalStash::AddObject(void *ptr) {
    Isolate *isolate = Isolate::GetCurrent();
    duk_context *ctx = isolate->GetDukContext();

    // Get the "refs" array in the heap stash
    duk_push_global_stash(ctx);
    duk_get_prop_string(ctx, -1, name_);
    duk_remove(ctx, -2);

    int type = duk_get_type(ctx, -1);

    int freeSlot;

    // freeSlot = scopeList[0]
    duk_get_prop_index(ctx, -1, 0);                                // <scopeList> <scopeList[0]>
    freeSlot = duk_get_int(ctx, -1);
    duk_pop(ctx);                                                  // <scopeList>

    if (freeSlot != 0) {
        // scopeList[0] = scopeList[freeSlot]
        duk_get_prop_index(ctx, -1, (duk_uarridx_t) freeSlot);    // <scopeList> <scopeList[freeSlot]>
        duk_put_prop_index(ctx, -2, 0);                            // <scopeList>
    } else {
        // freeSlot = scopeList.length;
        freeSlot = (int) duk_get_length(ctx, -1);
    }

    duk_push_heapptr(ctx, ptr);                                   // <scopeList> <scope>

    // scopeList[freeSlot] = scope
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) freeSlot);        // <scopeList>

    // Remove the refs array from the stack.
    duk_pop(ctx);                                                  //

    return freeSlot;
}

void GlobalStash::RemoveObject(int index) {
    if (!index) return;

    Isolate *isolate = Isolate::GetCurrent();
    duk_context *ctx = isolate->GetDukContext();

    // Get the "refs" array in the heap stash
    duk_push_global_stash(ctx);
    duk_get_prop_string(ctx, -1, name_);
    duk_remove(ctx, -2);

    // scopeList[scopeIndex] = scopeList[0]
    duk_get_prop_index(ctx, -1, 0);                                // <scopeList> <scopeList[0]>
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) index);

    // scopeList[0] = scopeIndex
    duk_push_int(ctx, index);                                      // <scopeList> <scopeIndex>
    duk_put_prop_index(ctx, -2, 0);                                // <scopeList>

    duk_pop(ctx);                                                  //
}

}
}

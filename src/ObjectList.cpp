//
// Created by Jiang Lu on 5/31/15.
//

#include <dukv8/ObjectList.h>
#include <dukv8/Isolate.h>

namespace v8 {
namespace internal {

ObjectList::ObjectList() {
    EnsureObjectList();
    addNewList();
}

ObjectList::~ObjectList() {
    removeList();
}

void ObjectList::EnsureObjectList() {
    Isolate *isolate = Isolate::GetCurrent();
    duk_context *ctx = isolate->GetDukContext();

    // 每个 global 对象对应一个 stash 对象
    duk_push_global_stash(ctx);
    duk_get_prop_string(ctx, -1, "__object_list");

    if (duk_is_undefined(ctx, -1)) {
        duk_pop(ctx);

        // Create a new array with one `0` at index `0`.
        duk_push_array(ctx);
        duk_push_int(ctx, 0);
        duk_put_prop_index(ctx, -2, 0);

        duk_dup_top(ctx);

        // Store it as "name_" in the heap stash
        duk_put_prop_string(ctx, -3, "__object_list");
    }

    duk_pop_2(ctx);
}

void ObjectList::addNewList() {
    Isolate *isolate = Isolate::GetCurrent();
    duk_context *ctx = isolate->GetDukContext();

    // Get the "refs" array in the heap stash
    duk_push_global_stash(ctx);
    duk_get_prop_string(ctx, -1, "__object_list");
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

    duk_push_array(ctx);
    list_ptr_ = duk_get_heapptr(ctx, -1);                         // <scopeList> <scope>

    // scopeList[freeSlot] = scope
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) freeSlot);        // <scopeList>

    // Remove the refs array from the stack.
    duk_pop(ctx);                                                  //

    list_idx_ = freeSlot;
}

void ObjectList::removeList() {
    Isolate *isolate = Isolate::GetCurrent();
    duk_context *ctx = isolate->GetDukContext();

    // Get the "refs" array in the heap stash
    duk_push_global_stash(ctx);
    duk_get_prop_string(ctx, -1, "__object_list");
    duk_remove(ctx, -2);

    // scopeList[scopeIndex] = scopeList[0]
    duk_get_prop_index(ctx, -1, 0);                                // <scopeList> <scopeList[0]>
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) list_idx_);

    // scopeList[0] = scopeIndex
    duk_push_int(ctx, list_idx_);                                  // <scopeList> <scopeIndex>
    duk_put_prop_index(ctx, -2, 0);                                // <scopeList>

    duk_pop(ctx);                                                  //
}

void ObjectList::AddObject(void *val) {
    Isolate *isolate = Isolate::GetCurrent();
    duk_context *ctx = isolate->GetDukContext();

    duk_push_heapptr(ctx, list_ptr_);
    duk_push_heapptr(ctx, val);
    duk_size_t len = duk_get_length(ctx, -1);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) len);
    duk_pop(ctx);
}

}
}
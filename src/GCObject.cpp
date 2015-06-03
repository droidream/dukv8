//
// Created by Jiang Lu on 6/3/15.
//

#include <dukv8/GCObject.h>
#include <dukv8/GlobalStash.h>
#include <dukv8/Isolate.h>
#include <dukv8/DukStackScope.h>

namespace v8 {
namespace internal {

#define THIS_INDEX 0

RTTI_IMPLEMENT_ROOT(v8::internal::GCObject);

GCObject::GCObject() :
        gcobject_heap_ptr_(NULL) {
    Isolate *isolate = Isolate::GetCurrent();
    DukContextRef ctx = isolate->GetDukContext();

    auto finalizer = [](duk_context *ctx) {
        DUK_STACK_SCOPE(ctx);
        duk_get_prop_index(ctx, -1, THIS_INDEX);
        delete static_cast<GCObject *>(duk_get_pointer(ctx, -1));
        return DUK_ERR_NONE;
    };

    duk_push_object(ctx);

    duk_push_pointer(ctx, this);
    duk_put_prop_index(ctx, -2, THIS_INDEX);

    duk_push_c_lightfunc(ctx, finalizer, 1, 1, 1);
    duk_set_finalizer(ctx, -2);

    gcobject_heap_ptr_ = duk_get_heapptr(ctx, -1);

    isolate->GetAutoReleasePool()->AutoRelease(gcobject_heap_ptr_);

    duk_pop(ctx);
}

GCObject::~GCObject() {
}

void GCObject::AddToObjectPool(GCObjectPool *pool) const {
    pool->AddObject(gcobject_heap_ptr_);
}

void GCObject::AddToGlobalStash(v8::internal::GlobalStash *stash) const {
    const_cast<GCObject *>(this)->gcobject_stash_index_
            = stash->AddObject(gcobject_heap_ptr_);
}

void GCObject::RemoveFromGlobalStash(v8::internal::GlobalStash *stash) const {
    stash->RemoveObject(gcobject_stash_index_);
    const_cast<GCObject *>(this)->gcobject_stash_index_ = 0;
}

}
}


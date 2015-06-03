//
// Created by Jiang Lu on 6/2/15.
//

#include <cassert>
#include <dukv8/Object.h>
#include <dukv8/Local.h>
#include <dukv8/Boolean.h>
#include <dukv8/String.h>
#include <dukv8/DukStackScope.h>

namespace v8 {

RTTI_IMPLEMENT(v8::Object, v8::Value);

Object::Object(duk_context *duk_ctx) :
        Value(duk_ctx), HeapObject() {
//    printf("%s\n", __PRETTY_FUNCTION__);
}

Object::Object(duk_context *duk_ctx, void *heap_ptr) :
        Value(duk_ctx), HeapObject() {
//    printf("%s\n", __PRETTY_FUNCTION__);
    AttachDuktapeObject(heap_ptr);
}

Object::~Object() {
    if (duk_obj_heapptr_) {
        DukObjectRelease(duk_obj_index_);
    }
//    printf("%s\n", __PRETTY_FUNCTION__);
}

void Object::AttachDuktapeObject(void *heap_ptr) {
    assert(duk_obj_heapptr_ == NULL);
    duk_obj_heapptr_ = heap_ptr;
    duk_obj_index_ = DukObjectRetain(duk_obj_heapptr_);
}

bool Object::Set(Handle<Value> key,
                 Handle<Value> value,
                 PropertyAttribute attrib) {
    Push();
    key->Push();
    value->Push();

    if (attrib == None) {
        duk_put_prop(duk_ctx_, -3);

    } else {
        duk_uint_t flags = DUK_DEFPROP_HAVE_VALUE;

        flags |= DUK_DEFPROP_HAVE_WRITABLE;
        if ((attrib & ReadOnly) == 0) {
            flags |= DUK_DEFPROP_WRITABLE;
        }

        flags |= DUK_DEFPROP_HAVE_ENUMERABLE;
        if ((attrib & DontEnum) == 0) {
            flags |= DUK_DEFPROP_ENUMERABLE;
        }

        flags |= DUK_DEFPROP_HAVE_CONFIGURABLE;
        if ((attrib & DontDelete) == 0) {
            flags |= DUK_DEFPROP_CONFIGURABLE;
        }

        duk_def_prop(duk_ctx_, -3, flags);
    }

    return true;
}

Local<Value> Object::Get(Handle<Value> key) {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    key->Push();
    duk_get_prop(duk_ctx_, -2);
    return Local<Value>::New(Value::FromStack(duk_ctx_, -1));
}

void Object::Push() const {
    duk_push_heapptr(duk_ctx_, duk_obj_heapptr_);
}

}
//
// Created by Jiang Lu on 6/2/15.
//

#include <cassert>
#include <dukv8/String.h>
#include <dukv8/Local.h>
#include <dukv8/Isolate.h>
#include <dukv8/DukStackScope.h>

namespace v8 {

RTTI_IMPLEMENT(v8::String, v8::Primitive);

String::String(duk_context *duk_ctx, const char *data, int length) :
        Primitive(duk_ctx) {
    DUK_STACK_SCOPE(duk_ctx);
    if (length >= 0) {
        duk_push_lstring(duk_ctx, data, length);
    } else {
        duk_push_string(duk_ctx, data);
    }
    duk_obj_heapptr_ = duk_get_heapptr(duk_ctx, -1);
    duk_obj_index_ = DukObjectRetain(duk_obj_heapptr_);
//    printf("%s\n", __PRETTY_FUNCTION__);
}

String::String(duk_context *duk_ctx, void *heap_ptr) :
        Primitive(duk_ctx) {
    DUK_STACK_SCOPE(duk_ctx);
    duk_push_heapptr(duk_ctx, heap_ptr);
    assert(duk_is_string(duk_ctx, -1));
    duk_obj_heapptr_ = duk_get_heapptr(duk_ctx, -1);
    duk_obj_index_ = DukObjectRetain(duk_obj_heapptr_);
//    printf("%s\n", __PRETTY_FUNCTION__);
}

String::~String() {
    DukObjectRelease(duk_obj_index_);
//    printf("%s\n", __PRETTY_FUNCTION__);
}

void String::Push() const {
    duk_push_heapptr(duk_ctx_, duk_obj_heapptr_);
}

/**
 * Allocates a new string from either UTF-8 encoded or ASCII data.
 * The second parameter 'length' gives the buffer length.
 * If the data is UTF-8 encoded, the caller must
 * be careful to supply the length parameter.
 * If it is not given, the function calls
 * 'strlen' to determine the buffer length, it might be
 * wrong if 'data' contains a null character.
 */
Local<String> String::New(const char *data, int length) {
    duk_context *ctx = Isolate::GetCurrent()->GetDukContext();
    return Local<String>::New(Handle<String>(new String(ctx, data, length)));
}

/** Creates a symbol. Returns one if it exists already.*/
Local<String> String::NewSymbol(const char *data, int length) {
    return String::New(data, length);
}

String::Utf8Value::Utf8Value(Handle<v8::Value> obj) {
    DukContextRef ctx = obj->GetDukContext();
    DUK_STACK_SCOPE(ctx);
    obj->Push();
    str_ = strdup(duk_safe_to_string(ctx, -1));
}

String::Utf8Value::~Utf8Value() {
    if (str_) {
        delete[] str_;
        str_ = NULL;
    }
}

}
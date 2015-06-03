//
// Created by Jiang Lu on 6/3/15.
//

#include <cassert>
#include <dukv8/Function.h>
#include <dukv8/Isolate.h>
#include <dukv8/String.h>
#include <dukv8/FunctionTemplate.h>
#include <dukv8/DukStackScope.h>
#include <dukv8/Local.h>
#include <dukv8/Arguments.h>

namespace v8 {

RTTI_IMPLEMENT(v8::Function, v8::Object);

Function::Function(DukContextRef duk_ctx, void *heap_ptr) :
        Object(duk_ctx) {
    DUK_STACK_SCOPE(duk_ctx);
    if (heap_ptr) {
        duk_obj_heapptr_ = heap_ptr;
        duk_obj_index_ = DukObjectRetain(duk_obj_heapptr_);
    }
//    printf("%s\n", __PRETTY_FUNCTION__);
}

Function::~Function() {
//    printf("%s\n", __PRETTY_FUNCTION__);
}

Function *Function::Cast(Value *value) {
    if (RTTI_IsKindOf(Function, value)) {
        return RTTI_StaticCast(Function, value);
    }

    if (value) {
        if (value->IsFunction()) {
            DukContextRef ctx = value->GetDukContext();
            DUK_STACK_SCOPE(ctx);
            value->Push();
            return new Function(ctx, duk_get_heapptr(ctx, -1));
        }
    }
    return NULL;
}

Local<Value> Function::Call(Handle<Object> that, int argc, Handle<Value> argv[]) {

    if (!function_template_.IsEmpty() && function_template_->callback_) {
        // C++ 函数

        Arguments args(Isolate::GetCurrent(),
                       Handle<Function>(this),
                       that,
                       that,
                       function_template_->data_,
                       argc,
                       argv,
                       false); // TODO: holder?

        Handle<Value> result = function_template_->callback_(args);

        return Local<Value>::New(result);

    } else {
        // JavaScript 函数
        Push();
        assert(duk_is_function(duk_ctx_, -1));

        for (int i = 0; i < argc; i++) {
            argv[i]->Push();
        }

        duk_int_t rc = duk_pcall(duk_ctx_, argc);
        if (rc == DUK_EXEC_SUCCESS) {
            return Local<Value>::New(Value::FromStack(duk_ctx_, -1));
        } else {
            printf("error: %s\n", duk_to_string(duk_ctx_, -1));
            return Local<Value>();
        }
    }
}

void Function::SetName(Handle<String> name) {
    name_ = name;
}

Handle<Value> Function::GetName() const {
    return name_;
}

}
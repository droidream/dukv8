//
// Created by Jiang Lu on 6/3/15.
//

#include <dukv8/Arguments.h>
#include <dukv8/Handle.h>
#include <dukv8/Local.h>
#include <dukv8/Value.h>
#include <dukv8/Object.h>
#include <dukv8/Function.h>
#include <dukv8/Primitive.h>

namespace v8 {

Arguments::Arguments(Isolate *isolate,
                     Handle<Function> callee,
                     Handle<Object> that,
                     Handle<Object> holder,
                     Handle<Value> data,
                     int argc,
                     Handle<Value> *argv,
                     bool is_construct_call) :
        isolate_(isolate),
        callee_(callee),
        that_(that),
        holder_(holder),
        data_(data),
        argc_(argc),
        argv_(argv),
        is_construct_call_(is_construct_call) {
}

Arguments::~Arguments() {
    isolate_ = NULL;
    argc_ = 0;
    argv_ = NULL;
    is_construct_call_ = false;
}

Isolate *Arguments::GetIsolate() const {
    return isolate_;
}

int Arguments::Length() const {
    return argc_;
}

Local<Value> Arguments::operator[](int i) const {
    if ((0 <= i) && (i < Length())) {
        return Local<Value>::New(argv_[i]);
    }
    return Local<Value>::New(Undefined());
}

Local<Function> Arguments::Callee() const {
    return Local<Function>::New(callee_);
}

Local<Object> Arguments::This() const {
    return Local<Object>::New(that_);
}

Local<Object> Arguments::Holder() const {
    return Local<Object>::New(holder_);
}

bool Arguments::IsConstructCall() const {
    return is_construct_call_;
}

Local<Value> Arguments::Data() const {
    return Local<Value>::New(data_);
}

}
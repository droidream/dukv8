//
// Created by Jiang Lu on 6/3/15.
//

#ifndef DUKV8_ARGUMENTS_H
#define DUKV8_ARGUMENTS_H

#include "Base.h"
#include "Handle.h"

namespace v8 {


/**
 * The argument information given to function call callbacks.  This
 * class provides access to information about the context of the call,
 * including the receiver, the number and values of arguments, and
 * the holder of the function.
 */
class Arguments {
public:
    int Length() const;
    Local<Value> operator[](int i) const;
    Local<Function> Callee() const;
    Local<Object> This() const;
    Local<Object> Holder() const;
    bool IsConstructCall() const;
    Local<Value> Data() const;
    Isolate *GetIsolate() const;

    Arguments(Isolate *isolate,
              Handle<Function> callee,
              Handle<Object> that,
              Handle<Object> holder,
              Handle<Value> data,
              int argc,
              Handle<Value> *argv,
              bool is_construct_call);

    ~Arguments();

private:
    Isolate *isolate_;
    Handle<Function> callee_;
    Handle<Object> that_;
    Handle<Object> holder_;
    Handle<Value> data_;
    int argc_;
    Handle<Value> *argv_;
    bool is_construct_call_;

private:
//    static const int kIsolateIndex = 0;
//    static const int kDataIndex = -1;
//    static const int kCalleeIndex = -2;
//    static const int kHolderIndex = -3;
//
//    friend class ImplementationUtilities;
//    inline Arguments(internal::Object **implicit_args,
//                     internal::Object **values,
//                     int length,
//                     bool is_construct_call);
//    internal::Object **implicit_args_;
//    internal::Object **values_;
//    int length_;
//    bool is_construct_call_;
};

}

#endif //DUKV8_ARGUMENTS_H

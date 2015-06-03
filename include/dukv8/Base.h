//
// Created by Jiang Lu on 6/1/15.
//
// @formatter:off

#ifndef DUKV8_BASE_H
#define DUKV8_BASE_H

#include <duktape.h>
#include "RTTI.h"

namespace v8 {

#define TODO() printf("%s:%d TODO: %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__)

typedef duk_context* DukContextRef;

#define V8EXPORT
#define V8_EXPORT
#define INTERNAL

class Context;
class String;
class StringObject;
class Value;
class Utils;
class Number;
class NumberObject;
class Object;
class Array;
class Int32;
class Uint32;
class External;
class Primitive;
class Boolean;
class BooleanObject;
class Integer;
class Function;
class Date;
class ImplementationUtilities;
class Signature;
class AccessorSignature;
template <class T> class Handle;
template <class T> class Local;
template <class T> class Persistent;
class FunctionTemplate;
class ObjectTemplate;
class Data;
class AccessorInfo;
class StackTrace;
class StackFrame;
class Isolate;
class Arguments;
class Message;
class TryCatch;

namespace internal {
class Object;
class ObjectList;
class GCObject;
}

namespace i = v8::internal;

enum PropertyAttribute {
    None       = 0,
    ReadOnly   = 1 << 0,
    DontEnum   = 1 << 1,
    DontDelete = 1 << 2
};

typedef Handle<Value> (*InvocationCallback)(const Arguments &args);


// --- Weak Handles ---

/**
 * A weak reference callback function.
 *
 * This callback should either explicitly invoke Dispose on |object| if
 * V8 wrapper is not needed anymore, or 'revive' it by invocation of MakeWeak.
 *
 * \param object the weak global object to be reclaimed by the garbage collector
 * \param parameter the value passed in when making the weak global object
 */
typedef void (*WeakReferenceCallback)(Persistent<Value> object,
                                      void *parameter);

}

#endif //DUKV8_BASE_H

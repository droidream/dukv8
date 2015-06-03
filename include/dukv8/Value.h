//
// Created by Jiang Lu on 6/2/15.
//

#ifndef DUKV8_VALUE_H
#define DUKV8_VALUE_H

#include <duktape.h>
#include "Base.h"
#include "Data.h"

namespace v8 {

int DukObjectRetain(void *heapptr);

void DukObjectRelease(int index);

class HeapObject {
public:
    HeapObject() :
            duk_obj_index_(0),
            duk_obj_heapptr_(NULL) {
    }

    void *GetHeapPtr() {
        return duk_obj_heapptr_;
    }

    int duk_obj_index_;
    void *duk_obj_heapptr_;
};

class Value : public Data {
public:
    RTTI_DECLARE();

    /**
     * Returns true if this value is the undefined value.  See ECMA-262
     * 4.3.10.
     */
    V8EXPORT bool IsUndefined() const;

    /**
     * Returns true if this value is the null value.  See ECMA-262
     * 4.3.11.
     */
    V8EXPORT bool IsNull() const;

    /**
    * Returns true if this value is true.
    */
    V8EXPORT bool IsTrue() const;

    /**
     * Returns true if this value is false.
     */
    V8EXPORT bool IsFalse() const;

    /**
     * Returns true if this value is an instance of the String type.
     * See ECMA-262 8.4.
     */
    V8EXPORT bool IsString() const;

    /**
     * Returns true if this value is a function.
     */
    V8EXPORT bool IsFunction() const;

    /**
     * Returns true if this value is an array.
     */
    V8EXPORT bool IsArray() const;

    /**
     * Returns true if this value is an object.
     */
    V8EXPORT bool IsObject() const;

    /**
     * Returns true if this value is boolean.
     */
    V8EXPORT bool IsBoolean() const;

    /**
     * Returns true if this value is a number.
     */
    V8EXPORT bool IsNumber() const;

    /**
     * Returns true if this value is external.
     */
    V8EXPORT bool IsExternal() const;

    /**
     * Returns true if this value is a 32-bit signed integer.
     */
    V8EXPORT bool IsInt32() const;

    /**
     * Returns true if this value is a 32-bit unsigned integer.
     */
    V8EXPORT bool IsUint32() const;

    /**
     * Returns true if this value is a Date.
     */
    V8EXPORT bool IsDate() const;

    /**
     * Returns true if this value is a Boolean object.
     */
    V8EXPORT bool IsBooleanObject() const;

    /**
     * Returns true if this value is a Number object.
     */
    V8EXPORT bool IsNumberObject() const;

    /**
     * Returns true if this value is a String object.
     */
    V8EXPORT bool IsStringObject() const;

    /**
     * Returns true if this value is a NativeError.
     */
    V8EXPORT bool IsNativeError() const;

    /**
     * Returns true if this value is a RegExp.
     */
    V8EXPORT bool IsRegExp() const;

    V8EXPORT Local<Boolean> ToBoolean() const;
    V8EXPORT Local<Number> ToNumber() const;
    V8EXPORT Local<String> ToString() const;
    V8EXPORT Local<String> ToDetailString() const;
    V8EXPORT Local<Object> ToObject() const;
    V8EXPORT Local<Integer> ToInteger() const;
    V8EXPORT Local<Uint32> ToUint32() const;
    V8EXPORT Local<Int32> ToInt32() const;

    /**
     * Attempts to convert a string to an array index.
     * Returns an empty handle if the conversion fails.
     */
    V8EXPORT Local<Uint32> ToArrayIndex() const;

    V8EXPORT bool BooleanValue() const;
    V8EXPORT double NumberValue() const;
    V8EXPORT int64_t IntegerValue() const;
    V8EXPORT uint32_t Uint32Value() const;
    V8EXPORT int32_t Int32Value() const;

    /** JS == */
    V8EXPORT bool Equals(Handle<Value> that) const;
    V8EXPORT bool StrictEquals(Handle<Value> that) const;

    virtual void Push() const = 0;

    inline DukContextRef GetDukContext() const {
        return duk_ctx_;
    }

    static Handle<Value> FromStack(DukContextRef ctx, int index);

protected:
    Value(duk_context *duk_ctx) :
            duk_ctx_(duk_ctx) { }

    virtual ~Value() { };

protected:
    duk_context *duk_ctx_;
};

}

#endif //DUKV8_VALUE_H

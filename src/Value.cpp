//
// Created by Jiang Lu on 6/2/15.
//

#include <cassert>
#include <dukv8/Value.h>
#include <dukv8/GlobalStash.h>
#include <dukv8/DukStackScope.h>
#include <dukv8/Local.h>
#include <dukv8/Boolean.h>
#include <dukv8/String.h>
#include <dukv8/Object.h>
#include <dukv8/Number.h>

namespace v8 {

int DukObjectRetain(void *heapptr) {
    return internal::GlobalStash("objs").AddObject(heapptr);
}

void DukObjectRelease(int index) {
    internal::GlobalStash("objs").RemoveObject(index);
}

RTTI_IMPLEMENT(v8::Value, v8::Data);

/**
 * Returns true if this value is the undefined value.  See ECMA-262
 * 4.3.10.
 */
bool Value::IsUndefined() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    return (bool) duk_is_undefined(duk_ctx_, -1);
}

/**
 * Returns true if this value is the null value.  See ECMA-262
 * 4.3.11.
 */
bool Value::IsNull() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    return (bool) duk_is_null(duk_ctx_, -1);
}

/**
* Returns true if this value is true.
*/
bool Value::IsTrue() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    return duk_is_boolean(duk_ctx_, -1) != 0;
}

/**
 * Returns true if this value is false.
 */
bool Value::IsFalse() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    return duk_is_boolean(duk_ctx_, -1) == 0;
}

/**
 * Returns true if this value is an instance of the String type.
 * See ECMA-262 8.4.
 */
bool Value::IsString() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    return (bool) duk_is_string(duk_ctx_, -1);
}

/**
 * Returns true if this value is a function.
 */
bool Value::IsFunction() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    return (bool) duk_is_function(duk_ctx_, -1);
}

/**
 * Returns true if this value is an array.
 */
bool Value::IsArray() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    return (bool) duk_is_array(duk_ctx_, -1);
}

/**
 * Returns true if this value is an object.
 */
bool Value::IsObject() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    return (bool) duk_is_object(duk_ctx_, -1);
}

/**
 * Returns true if this value is boolean.
 */
bool Value::IsBoolean() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    return (bool) duk_is_boolean(duk_ctx_, -1);
}

/**
 * Returns true if this value is a number.
 */
bool Value::IsNumber() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    return (bool) duk_is_number(duk_ctx_, -1);
}

/**
 * Returns true if this value is external.
 */
bool Value::IsExternal() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    return (bool) duk_is_pointer(duk_ctx_, -1);
}

/**
 * Returns true if this value is a 32-bit signed integer.
 */
bool Value::IsInt32() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    return (bool) duk_is_number(duk_ctx_, -1);
}

/**
 * Returns true if this value is a 32-bit unsigned integer.
 */
bool Value::IsUint32() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    return (bool) duk_is_number(duk_ctx_, -1);
}

/**
 * Returns true if this value is a Date.
 */
bool Value::IsDate() const {
    DUK_STACK_SCOPE(duk_ctx_);
    duk_push_global_object(duk_ctx_);
    duk_get_prop_string(duk_ctx_, -1, "Date");
    duk_remove(duk_ctx_, -2);
    return (bool) duk_instanceof(duk_ctx_, 0, 1);
}

/**
 * Returns true if this value is a Boolean object.
 */
bool Value::IsBooleanObject() const {
    return false;
}

/**
 * Returns true if this value is a Number object.
 */
bool Value::IsNumberObject() const {
    return false;
}

/**
 * Returns true if this value is a String object.
 */
bool Value::IsStringObject() const {
    return false;
}

/**
 * Returns true if this value is a NativeError.
 */
bool Value::IsNativeError() const {
    return false;
}

/**
 * Returns true if this value is a RegExp.
 */
bool Value::IsRegExp() const {
    DUK_STACK_SCOPE(duk_ctx_);
    duk_push_global_object(duk_ctx_);
    duk_get_prop_string(duk_ctx_, -1, "RegExp");
    duk_remove(duk_ctx_, -2);
    return (bool) duk_instanceof(duk_ctx_, 0, 1);
}

Local<Boolean> Value::ToBoolean() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    bool value = static_cast<bool>(duk_to_boolean(duk_ctx_, -1));
    return Local<Boolean>(new Boolean(duk_ctx_, value));
}

Local<Number> Value::ToNumber() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    double value = static_cast<bool>(duk_to_number(duk_ctx_, -1));
    return Local<Number>::New(Handle<Number>(
            new Number(duk_ctx_, value)));
}

Local<String> Value::ToString() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    duk_size_t len;
    const char *data = duk_get_lstring(duk_ctx_, -1, &len);
    return Local<String>::New(Handle<String>(
            new String(duk_ctx_, data, len)));
}

Local<String> Value::ToDetailString() const {
    return Value::ToString();
}

Local<Object> Value::ToObject() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    void *heap_ptr = duk_get_heapptr(duk_ctx_, -1);
    return Local<Object>::New(Handle<Object>(
            new Object(duk_ctx_, heap_ptr)));
}

Local<Integer> Value::ToInteger() const {
    return Local<Integer>();
}

Local<Uint32> Value::ToUint32() const {
    return Local<Uint32>();
}

Local<Int32> Value::ToInt32() const {
    return Local<Int32>();
}

Local<Uint32> Value::ToArrayIndex() const {
    return Local<Uint32>();
}

bool Value::BooleanValue() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    return (bool) duk_get_boolean(duk_ctx_, -1);
}

double Value::NumberValue() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    return duk_get_number(duk_ctx_, -1);
}

int64_t Value::IntegerValue() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    return duk_get_int(duk_ctx_, -1);
}

uint32_t Value::Uint32Value() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    return duk_get_uint(duk_ctx_, -1);
}

int32_t Value::Int32Value() const {
    DUK_STACK_SCOPE(duk_ctx_);
    Push();
    return duk_get_int(duk_ctx_, -1);
}

bool Value::Equals(Handle<Value> that) const {
    return false;
}

bool Value::StrictEquals(Handle<Value> that) const {
    return false;
}

Handle<Value> Value::FromStack(DukContextRef ctx, int index) {

    // #define DUK_TYPE_NONE                     0    /* no value, e.g. invalid index */
    // #define DUK_TYPE_UNDEFINED                1    /* Ecmascript undefined */
    // #define DUK_TYPE_NULL                     2    /* Ecmascript null */
    // #define DUK_TYPE_BOOLEAN                  3    /* Ecmascript boolean: 0 or 1 */
    // #define DUK_TYPE_NUMBER                   4    /* Ecmascript number: double */
    // #define DUK_TYPE_STRING                   5    /* Ecmascript string: CESU-8 / extended UTF-8 encoded */
    // #define DUK_TYPE_OBJECT                   6    /* Ecmascript object: includes objects, arrays, functions, threads */
    // #define DUK_TYPE_BUFFER                   7    /* fixed or dynamic, garbage collected byte buffer */
    // #define DUK_TYPE_POINTER                  8    /* raw void pointer */
    // #define DUK_TYPE_LIGHTFUNC                9    /* lightweight function pointer */

    if (duk_check_type(ctx, index, DUK_TYPE_NONE)) {
        return Local<Value>::New(Handle<Value>());
    }

    if (duk_check_type(ctx, index, DUK_TYPE_UNDEFINED)) {
        return Local<Value>::New(Handle<Value>(Undefined()));
    }

    if (duk_check_type(ctx, index, DUK_TYPE_NULL)) {
        return Local<Value>::New(Handle<Value>());
    }

    if (duk_check_type(ctx, index, DUK_TYPE_BOOLEAN)) {
        bool value = static_cast<bool>(duk_get_boolean(ctx, index));
        return Local<Value>::New(Handle<Value>(
                new Boolean(ctx, value)));
    }

    if (duk_check_type(ctx, index, DUK_TYPE_NUMBER)) {
        double value = duk_get_number(ctx, index);
        return Local<Value>::New(Handle<Value>(
                new Number(ctx, value)));
    }

    if (duk_check_type(ctx, index, DUK_TYPE_STRING)) {
        return Local<Value>::New(Handle<Value>(
                new String(ctx, duk_get_heapptr(ctx, index))));
    }

    void *heap_ptr = duk_get_heapptr(ctx, index);
    if (heap_ptr) {
        return Local<Value>::New(Handle<Value>(
                new Object(ctx, duk_get_heapptr(ctx, index))));
    }

    assert(true);

    return Local<Value>();
}

}
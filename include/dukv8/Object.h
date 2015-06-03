//
// Created by Jiang Lu on 6/2/15.
//

#ifndef DUKV8_OBJECT_H
#define DUKV8_OBJECT_H

#include "Base.h"
#include "Handle.h"
#include "Value.h"

namespace v8 {

/**
 * A JavaScript object (ECMA-262, 4.3.3)
 */
class Object : public Value, public HeapObject {
public:
    RTTI_DECLARE();

    Object(duk_context *duk_ctx);
    Object(duk_context *duk_ctx, void *heap_ptr);

    virtual ~Object();

    V8EXPORT bool Set(Handle<Value> key,
                      Handle<Value> value,
                      PropertyAttribute attrib = None);

    V8EXPORT Local<Value> Get(Handle<Value> key);

    virtual void Push() const;

    void AttachDuktapeObject(void *heap_ptr);
};

}

#endif //DUKV8_OBJECT_H

//
// Created by Jiang Lu on 6/3/15.
//

#ifndef DUKV8_STRINGOBJECT_H
#define DUKV8_STRINGOBJECT_H

#include "Base.h"
#include "Object.h"

namespace v8 {

class V8EXPORT StringObject : public Object {
public:
    RTTI_DECLARE();

    V8EXPORT static Local<Value> New(Handle<String> value);

    /**
     * Returns the String held by the object.
     */
    V8EXPORT Local<String> StringValue() const;

    static inline StringObject *Cast(v8::Value *obj);

protected:

    StringObject(DukContextRef duk_ctx, Handle<String> value);

    virtual ~StringObject();

private:
    V8EXPORT static void CheckCast(v8::Value *obj);
};

}


#endif //DUKV8_STRINGOBJECT_H

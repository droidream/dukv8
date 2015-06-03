//
// Created by Jiang Lu on 6/2/15.
//

#include <dukv8/Primitive.h>
#include <dukv8/Handle.h>
#include <dukv8/Isolate.h>

namespace v8 {

RTTI_IMPLEMENT(v8::Primitive, v8::Value);

namespace internal {

class Undefined : public Primitive {
public:
    RTTI_DECLARE();

    Undefined(DukContextRef duk_ctx) : Primitive(duk_ctx) { }

    virtual void Push() const {
        duk_push_undefined(duk_ctx_);
    }
};

RTTI_IMPLEMENT(v8::internal::Undefined, v8::Primitive);

}

Handle<Primitive> Undefined() {
    DukContextRef ctx = Isolate::GetCurrent()->GetDukContext();
    return Handle<Primitive>(new i::Undefined(ctx));
}

}

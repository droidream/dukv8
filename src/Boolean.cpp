//
// Created by Jiang Lu on 6/3/15.
//

#include <dukv8/Boolean.h>
#include <dukv8/Isolate.h>
#include <dukv8/Handle.h>

namespace v8 {

RTTI_IMPLEMENT(v8::Boolean, v8::Primitive);

Boolean::Boolean(duk_context *duk_ctx, bool value) :
        Primitive(duk_ctx), value_(value) {
    printf("%s\n", __PRETTY_FUNCTION__);
}

Boolean::~Boolean() {
    printf("%s\n", __PRETTY_FUNCTION__);
}

bool Boolean::Value() const {
    return value_;
}

void Boolean::Push() const {
    duk_push_boolean(duk_ctx_, value_);
}

Handle<Boolean> Boolean::New(bool value) {
    DukContextRef ctx = Isolate::GetCurrent()->GetDukContext();
    return Handle<Boolean>(new Boolean(ctx, value));
}

}


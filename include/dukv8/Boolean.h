//
// Created by Jiang Lu on 6/3/15.
//

#ifndef DUKV8_BOOLEAN_H
#define DUKV8_BOOLEAN_H

#include "Base.h"
#include "Primitive.h"

namespace v8 {

class V8EXPORT Boolean : public Primitive {
public:
    RTTI_DECLARE();

    V8EXPORT bool Value() const;

    static Handle<Boolean> New(bool value);

    virtual void Push() const;

protected:
    Boolean(duk_context *duk_ctx, bool value);

    virtual ~Boolean();

private:
    bool value_;

    friend class Value;
};

}

#endif //DUKV8_BOOLEAN_H

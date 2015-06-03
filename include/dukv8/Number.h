//
// Created by Jiang Lu on 6/3/15.
//

#ifndef DUKV8_NUMBER_H
#define DUKV8_NUMBER_H

#include "Base.h"
#include "Primitive.h"

namespace v8 {

/**
 * A JavaScript number value (ECMA-262, 4.3.20)
 */
class Number : public Primitive {
public:
    RTTI_DECLARE();

    V8EXPORT double Value() const;

    V8EXPORT static Local<Number> New(double value);

    static Number *Cast(v8::Value *obj);

    virtual void Push() const;

    V8EXPORT Number(DukContextRef ctx, double value);
    V8EXPORT static void CheckCast(v8::Value *value);

private:
    double value_;
};

}

#endif //DUKV8_NUMBER_H

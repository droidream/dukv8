//
// Created by Jiang Lu on 6/2/15.
//

#ifndef DUKV8_FUNCTIONTEMPLATE_H
#define DUKV8_FUNCTIONTEMPLATE_H

#include "Template.h"
#include "Handle.h"
#include "Function.h"

namespace v8 {

class FunctionTemplate : public Template {
public:
    RTTI_DECLARE();

    /** Creates a function template.*/
    static Local<FunctionTemplate> New(
            InvocationCallback callback = 0,
            Handle<Value> data = Handle<Value>(),
            Handle<Signature> signature = Handle<Signature>());

    /** Returns the unique function instance in the current execution context.*/
    Local<Function> GetFunction();

protected:
    FunctionTemplate(InvocationCallback callback,
                     Handle<Value> data,
                     Handle<Signature> signature);

    virtual ~FunctionTemplate();

private:
    InvocationCallback callback_;

    Handle<Value> data_;
    Handle<Signature> signature_;

    Handle<String> class_name_;
    Handle<Function> function_;

    friend class Function;
};

}

#endif //DUKV8_FUNCTIONTEMPLATE_H

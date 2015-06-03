//
// Created by Jiang Lu on 6/2/15.
//

#include <dukv8/FunctionTemplate.h>
#include <dukv8/Function.h>
#include <dukv8/Signature.h>
#include <dukv8/Local.h>
#include <dukv8/Isolate.h>

namespace v8 {

RTTI_IMPLEMENT(v8::FunctionTemplate, v8::Template);

FunctionTemplate::FunctionTemplate(InvocationCallback callback,
                                   Handle<Value> data,
                                   Handle<Signature> signature) :
        callback_(callback),
        data_(data),
        signature_(signature) {
//    printf("%s\n", __PRETTY_FUNCTION__);
}

FunctionTemplate::~FunctionTemplate() {
//    printf("%s\n", __PRETTY_FUNCTION__);
}

/** Creates a function template.*/
Local<FunctionTemplate> FunctionTemplate::New(InvocationCallback callback,
                                              Handle<Value> data,
                                              Handle<Signature> signature) {
    return Local<FunctionTemplate>::New(
            Handle<FunctionTemplate>(new FunctionTemplate(callback, data, signature)));
}

/** Returns the unique function instance in the current execution context.*/
Local<Function> FunctionTemplate::GetFunction() {
    if (function_.IsEmpty()) {
        DukContextRef ctx = Isolate::GetCurrent()->GetDukContext();
        function_ = Handle<Function>(new Function(ctx, NULL));
        Template::ApplyToObject(function_);
        function_->function_template_ = Handle<FunctionTemplate>(this);
        function_->SetName(class_name_);
    }
    return Local<Function>::New(function_);
}

}
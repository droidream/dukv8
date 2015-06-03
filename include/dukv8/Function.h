//
// Created by Jiang Lu on 6/3/15.
//

#ifndef DUKV8_FUNCTION_H
#define DUKV8_FUNCTION_H

#include "Base.h"
#include "Object.h"
#include "Handle.h"
#include "ScriptOrigin.h"

namespace v8 {

/**
 * A JavaScript function object (ECMA-262, 15.3).
 */
class Function : public Object {
public:
    RTTI_DECLARE();

    V8EXPORT Local<Object> NewInstance() const;
    V8EXPORT Local<Object> NewInstance(int argc, Handle<Value> argv[]) const;
    V8EXPORT Local<Value> Call(Handle<Object> recv,
                               int argc,
                               Handle<Value> argv[]);
    V8EXPORT void SetName(Handle<String> name);
    V8EXPORT Handle<Value> GetName() const;

    /**
     * Name inferred from variable or property assignment of this function.
     * Used to facilitate debugging and profiling of JavaScript code written
     * in an OO style, where many functions are anonymous but are assigned
     * to object properties.
     */
    V8EXPORT Handle<Value> GetInferredName() const;

    /**
     * Returns zero based line number of function body and
     * kLineOffsetNotFound if no information available.
     */
    V8EXPORT int GetScriptLineNumber() const;
    /**
     * Returns zero based column number of function body and
     * kLineOffsetNotFound if no information available.
     */
    V8EXPORT int GetScriptColumnNumber() const;
    V8EXPORT Handle<Value> GetScriptId() const;
    V8EXPORT ScriptOrigin GetScriptOrigin() const;
    static Function *Cast(Value *obj);
    V8EXPORT static const int kLineOffsetNotFound;

public:
    V8EXPORT Function(DukContextRef duk_ctx, void *heap_ptr);
    virtual ~Function();

private:
    V8EXPORT Function();
    V8EXPORT static void CheckCast(Value *obj);

private:
    Handle<String> name_;
    Handle<FunctionTemplate> function_template_;

    friend class FunctionTemplate;
};

}

#endif //DUKV8_FUNCTION_H

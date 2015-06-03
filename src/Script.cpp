//
// Created by Jiang Lu on 6/3/15.
//

#include <dukv8/Script.h>
#include <dukv8/Local.h>
#include <dukv8/String.h>
#include <dukv8/DukStackScope.h>
#include <dukv8/Isolate.h>
#include <dukv8/Context.h>
#include <dukv8/Function.h>
#include <dukv8/Boolean.h>

namespace v8 {

Script::Script(Handle<String> source,
               Handle<Value> file_name,
               Handle<Integer> line_number,
               Handle<String> script_data) :
        source_(source),
        file_name_(file_name),
        line_number_(line_number),
        script_data_(script_data) {
}

Local<Script> Script::New(Handle<String> source,
                          ScriptOrigin *origin,
                          ScriptData *pre_data,
                          Handle<String> script_data) {
    return Local<Script>();
}

Local<Script> Script::New(Handle<String> source,
                          Handle<Value> file_name) {
    return Local<Script>();
}

Local<Script> Script::Compile(Handle<String> source,
                              ScriptOrigin *origin,
                              ScriptData *pre_data,
                              Handle<String> script_data) {
    Handle<Script> script(new Script(source,
                                     origin->resource_name_,
                                     origin->resource_line_offset_,
                                     script_data));

    // 绑定到当前上下文中
    script->context_ = Context::GetCurrent();
    script->TryCompile();
    return Local<Script>::New(script);
}


Local<Script> Script::Compile(Handle<String> source,
                              Handle<Value> file_name,
                              Handle<String> script_data) {
    ScriptOrigin origin(file_name);
    return Script::Compile(source, &origin, NULL, script_data);
}

Local<Value> Script::Run() {
    Isolate *isolate = Isolate::GetCurrent();
    auto ctx = isolate->GetDukContext();

    Handle<Context> context = context_;
    if (context.IsEmpty()) {
        context = Context::GetCurrent();
    }

    Context::Scope context_scope(context);

    Handle<Object> global_object = context->Global();

    DUK_STACK_SCOPE(ctx);

    function_->Push();
    global_object->Push();

    if (duk_pcall_method(ctx, 0) == DUK_ERR_NONE) {
        return Local<Value>::New(Value::FromStack(ctx, -1));
    } else {
        // 发生错误, 转换成 Message 放入最近的 TryCatch
        return Local<Value>::New(Value::FromStack(ctx, -1));
    }
}

void Script::TryCompile() {
    Isolate *isolate = Isolate::GetCurrent();
    auto ctx = isolate->GetDukContext();

    DUK_STACK_SCOPE(ctx);

    source_->Push();
    file_name_->Push();

    if (duk_pcompile(ctx, DUK_COMPILE_EVAL) == DUK_ERR_NONE) {
        // success
        // duk_call(ctx, 0);      /* [ func ] -> [ result ] */
        // printf("Compile Type: %d\n", duk_get_type(ctx, -1));
        function_ = Local<Function>::New(Handle<Function>(
                new Function(ctx, duk_get_heapptr(ctx, -1))));
    } else {
        // failure
        printf("compile failed: %s\n", duk_safe_to_string(ctx, -1));

        // 获得最顶端的 TryCatch 对象
        // TryCatch *try_catch = Context::GetCurrent()->GetTopTryCatch();
        // try_catch->setErrorObject();
    }
}

}

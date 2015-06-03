//
// Created by Jiang Lu on 6/2/15.
//

#include <cassert>
#include <dukv8/Context.h>
#include <dukv8/Persistent.h>
#include <dukv8/Isolate.h>
#include <dukv8/Local.h>
#include <dukv8/Object.h>

namespace v8 {

Context *Context::s_current_context_ = NULL;

Context::Context() :
        previous_context_(NULL) {
//    printf("%s\n", __PRETTY_FUNCTION__);
}

Context::~Context() {
//    printf("%s\n", __PRETTY_FUNCTION__);
}

/**
 * Returns the global proxy object or global object itself for
 * detached contexts.
 *
 * Global proxy object is a thin wrapper whose prototype points to
 * actual context's global object with the properties like Object, etc.
 * This is done that way for security reasons (for more details see
 * https://wiki.mozilla.org/Gecko:SplitWindow).
 *
 * Please note that changes to global proxy object prototype most probably
 * would break VM---v8 expects only global object as a prototype of
 * global proxy object.
 *
 * If DetachGlobal() has been invoked, Global() would return actual global
 * object until global is reattached with ReattachGlobal().
 */
Local<Object> Context::Global() {
    Isolate *isolate = Isolate::GetCurrent();
    duk_context *ctx = isolate->GetDukContext();
    duk_push_global_object(ctx);
    void *obj_heap_ptr = duk_get_heapptr(ctx, -1);
    duk_pop(ctx);
    return Local<Object>::New(Handle<Object>(new Object(ctx, obj_heap_ptr)));
}

/** Creates a new context.
 *
 * Returns a persistent handle to the newly allocated context. This
 * persistent handle has to be disposed when the context is no
 * longer used so the context can be garbage collected.
 *
 * \param extensions An optional extension configuration containing
 * the extensions to be installed in the newly created context.
 *
 * \param global_template An optional object template from which the
 * global object for the newly created context will be created.
 *
 * \param global_object An optional global object to be reused for
 * the newly created context. This global object must have been
 * created by a previous call to Context::New with the same global
 * template. The state of the global object will be completely reset
 * and only object identify will remain.
 */
Persistent<Context> Context::New(
        ExtensionConfiguration *extensions,
        Handle<ObjectTemplate> global_template,
        Handle<Value> global_object) {

    Handle<Context> context(new Context());

//    Handle<Object> global;
//
//    if (!global_object.IsEmpty() && global_object->IsObject()) {
//        global = context->external_global_object_ = global_object->ToObject();
//    } else {
//        global = context->global_object_;
//    }

    // apply global object template to global object
    if (!global_template.IsEmpty() && !global_object.IsEmpty()) {
        // global_template->ApplyToObject(global_object);
        // internal::Helper *helper = global_object->GetHelper();
        // helper->m_object_template = global_template;
        // helper->SetInternalFieldCount(global_template->m_internal_field_count);
    }

    return Persistent<Context>::New(context);
}

void Context::Enter() {
    previous_context_ = s_current_context_;
    s_current_context_ = this;
//    printf("%s\n", __PRETTY_FUNCTION__);
}

void Context::Exit() {
//    printf("%s\n", __PRETTY_FUNCTION__);
    assert(s_current_context_ == this);
    s_current_context_ = previous_context_;
}

Local<Context> Context::GetCurrent() {
    if (s_current_context_) {
        return Local<Context>::New(Handle<Context>(s_current_context_));
    }
    return Local<Context>();
}

}
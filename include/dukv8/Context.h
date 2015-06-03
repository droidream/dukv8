//
// Created by Jiang Lu on 6/2/15.
//

#ifndef DUKV8_CONTEXT_H
#define DUKV8_CONTEXT_H

#include <dukv8/Base.h>
#include <dukv8/Handle.h>
#include "GCObject.h"

namespace v8 {

/**
 * Ignore
 */
class V8EXPORT ExtensionConfiguration {
public:
    ExtensionConfiguration(int name_count, const char *names[])
            : name_count_(name_count), names_(names) { }
private:
    friend class ImplementationUtilities;
    int name_count_;
    const char **names_;
};


/**
 * A sandboxed execution context with its own set of built-in objects
 * and functions.
 */
class V8EXPORT Context : public i::GCObject {
public:
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
    Local<Object> Global();

    /**
     * Detaches the global object from its context before
     * the global object can be reused to create a new context.
     */
    void DetachGlobal();

    /**
     * Reattaches a global object to a context.  This can be used to
     * restore the connection between a global object and a context
     * after DetachGlobal has been called.
     *
     * \param global_object The global object to reattach to the
     *   context.  For this to work, the global object must be the global
     *   object that was associated with this context before a call to
     *   DetachGlobal.
     */
    void ReattachGlobal(Handle<Object> global_object);

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
    static Persistent<Context> New(
            ExtensionConfiguration *extensions = NULL,
            Handle<ObjectTemplate> global_template = Handle<ObjectTemplate>(),
            Handle<Value> global_object = Handle<Value>());

    /** Returns the last entered context. */
    static Local<Context> GetEntered();

    /** Returns the context that is on the top of the stack. */
    static Local<Context> GetCurrent();

    /**
     * Returns the context of the calling JavaScript code.  That is the
     * context of the top-most JavaScript frame.  If there are no
     * JavaScript frames an empty handle is returned.
     */
    static Local<Context> GetCalling();

    /**
     * Sets the security token for the context.  To access an object in
     * another context, the security tokens must match.
     */
    void SetSecurityToken(Handle<Value> token);

    /** Restores the security token to the default value. */
    void UseDefaultSecurityToken();

    /** Returns the security token of this context.*/
    Handle<Value> GetSecurityToken();

    /**
     * Enter this context.  After entering a context, all code compiled
     * and run is compiled and run in this context.  If another context
     * is already entered, this old context is saved so it can be
     * restored when the new context is exited.
     */
    void Enter();

    /**
     * Exit this context.  Exiting the current context restores the
     * context that was in place when entering the current context.
     */
    void Exit();

    /** Returns true if the context has experienced an out of memory situation. */
    bool HasOutOfMemoryException();

    /** Returns true if V8 has a current context. */
    static bool InContext();

    /**
     * Associate an additional data object with the context. This is mainly used
     * with the debugger to provide additional information on the context through
     * the debugger API.
     */
    void SetData(Handle<Value> data);
    Local<Value> GetData();

    /**
     * Control whether code generation from strings is allowed. Calling
     * this method with false will disable 'eval' and the 'Function'
     * constructor for code running in this context. If 'eval' or the
     * 'Function' constructor are used an exception will be thrown.
     *
     * If code generation from strings is not allowed the
     * V8::AllowCodeGenerationFromStrings callback will be invoked if
     * set before blocking the call to 'eval' or the 'Function'
     * constructor. If that callback returns true, the call will be
     * allowed, otherwise an exception will be thrown. If no callback is
     * set an exception will be thrown.
     */
    void AllowCodeGenerationFromStrings(bool allow);

    /**
     * Returns true if code generation from strings is allowed for the context.
     * For more details see AllowCodeGenerationFromStrings(bool) documentation.
     */
    bool IsCodeGenerationFromStringsAllowed();

    /**
     * Sets the error description for the exception that is thrown when
     * code generation from strings is not allowed and 'eval' or the 'Function'
     * constructor are called.
     */
    void SetErrorMessageForCodeGenerationFromStrings(Handle<String> message);

    /**
     * Stack-allocated class which sets the execution context for all
     * operations executed within a local scope.
     */
    class Scope {
    public:
        explicit inline Scope(Handle<Context> context) : context_(context) {
            context_->Enter();
        }
        inline ~Scope() { context_->Exit(); }
    private:
        Handle<Context> context_;
    };

private:
    friend class Value;
    friend class Script;
    friend class Object;
    friend class Function;

private:
    Context();
    ~Context();

    static Context* s_current_context_;
    Context *previous_context_;
};

}

#endif //DUKV8_CONTEXT_H

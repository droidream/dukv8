//
// Created by Jiang Lu on 6/3/15.
//

#ifndef DUKV8_TRYCATCH_H
#define DUKV8_TRYCATCH_H

#include "Base.h"

namespace v8 {

/**
 * An external exception handler.
 */
class V8EXPORT TryCatch {
public:
    /**
     * Creates a new try/catch block and registers it with v8.
     */
    TryCatch();

    /**
     * Unregisters and deletes this try/catch block.
     */
    ~TryCatch();

    /**
     * Returns true if an exception has been caught by this try/catch block.
     */
    bool HasCaught() const;

    /**
     * For certain types of exceptions, it makes no sense to continue
     * execution.
     *
     * Currently, the only type of exception that can be caught by a
     * TryCatch handler and for which it does not make sense to continue
     * is termination exception.  Such exceptions are thrown when the
     * TerminateExecution methods are called to terminate a long-running
     * script.
     *
     * If CanContinue returns false, the correct action is to perform
     * any C++ cleanup needed and then return.
     */
    bool CanContinue() const;

    /**
     * Throws the exception caught by this TryCatch in a way that avoids
     * it being caught again by this same TryCatch.  As with ThrowException
     * it is illegal to execute any JavaScript operations after calling
     * ReThrow; the caller must return immediately to where the exception
     * is caught.
     */
    Handle<Value> ReThrow();

    /**
     * Returns the exception caught by this try/catch block.  If no exception has
     * been caught an empty handle is returned.
     *
     * The returned handle is valid until this TryCatch block has been destroyed.
     */
    Local<Value> Exception() const;

    /**
     * Returns the .stack property of the thrown object.  If no .stack
     * property is present an empty handle is returned.
     */
    Local<Value> StackTrace() const;

    /**
     * Returns the message associated with this exception.  If there is
     * no message associated an empty handle is returned.
     *
     * The returned handle is valid until this TryCatch block has been
     * destroyed.
     */
    Local<v8::Message> Message() const;

    /**
     * Clears any exceptions that may have been caught by this try/catch block.
     * After this method has been called, HasCaught() will return false.
     *
     * It is not necessary to clear a try/catch block before using it again; if
     * another exception is thrown the previously caught exception will just be
     * overwritten.  However, it is often a good idea since it makes it easier
     * to determine which operation threw a given exception.
     */
    void Reset();

    /**
     * Set verbosity of the external exception handler.
     *
     * By default, exceptions that are caught by an external exception
     * handler are not reported.  Call SetVerbose with true on an
     * external exception handler to have exceptions caught by the
     * handler reported as if they were not caught.
     */
    void SetVerbose(bool value);

    /**
     * Set whether or not this TryCatch should capture a Message object
     * which holds source information about where the exception
     * occurred.  True by default.
     */
    void SetCaptureMessage(bool value);
};

}

#endif //DUKV8_TRYCATCH_H

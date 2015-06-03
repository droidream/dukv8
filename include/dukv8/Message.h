//
// Created by Jiang Lu on 6/2/15.
//

#ifndef DUKV8_MESSAGE_H
#define DUKV8_MESSAGE_H

#include <dukv8/Base.h>
#include "GCObject.h"

namespace v8 {

/**
 * An error message.
 */
class V8EXPORT Message : public i::GCObject {
public:
    Local<String> Get() const;
    Local<String> GetSourceLine() const;

    /**
     * Returns the resource name for the script from where the function causing
     * the error originates.
     */
    Handle<Value> GetScriptResourceName() const;

    /**
     * Returns the resource data for the script from where the function causing
     * the error originates.
     */
    Handle<Value> GetScriptData() const;

    /**
     * Exception stack trace. By default stack traces are not captured for
     * uncaught exceptions. SetCaptureStackTraceForUncaughtExceptions allows
     * to change this option.
     */
    Handle<StackTrace> GetStackTrace() const;

    /**
     * Returns the number, 1-based, of the line where the error occurred.
     */
    int GetLineNumber() const;

    /**
     * Returns the index within the script of the first character where
     * the error occurred.
     */
    int GetStartPosition() const;

    /**
     * Returns the index within the script of the last character where
     * the error occurred.
     */
    int GetEndPosition() const;

    /**
     * Returns the index within the line of the first character where
     * the error occurred.
     */
    int GetStartColumn() const;

    /**
     * Returns the index within the line of the last character where
     * the error occurred.
     */
    int GetEndColumn() const;

    // TODO(1245381): Print to a string instead of on a FILE.
    static void PrintCurrentStackTrace(FILE *out);

    static const int kNoLineNumberInfo = 0;
    static const int kNoColumnInfo = 0;
};


}

#endif //DUKV8_MESSAGE_H

//
// Created by Jiang Lu on 6/2/15.
//

#ifndef DUKV8_STACKTRACE_H
#define DUKV8_STACKTRACE_H

#include "Base.h"

namespace v8 {

class V8EXPORT StackTrace {
public:
    /**
     * Flags that determine what information is placed captured for each
     * StackFrame when grabbing the current stack trace.
     */
    enum StackTraceOptions {
        kLineNumber = 1,
        kColumnOffset = 1 << 1 | kLineNumber,
        kScriptName = 1 << 2,
        kFunctionName = 1 << 3,
        kIsEval = 1 << 4,
        kIsConstructor = 1 << 5,
        kScriptNameOrSourceURL = 1 << 6,
        kOverview = kLineNumber | kColumnOffset | kScriptName | kFunctionName,
        kDetailed = kOverview | kIsEval | kIsConstructor | kScriptNameOrSourceURL
    };
};

}

#endif //DUKV8_STACKTRACE_H

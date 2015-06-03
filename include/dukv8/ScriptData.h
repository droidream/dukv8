//
// Created by Jiang Lu on 6/3/15.
//

#ifndef DUKV8_SCRIPTDATA_H
#define DUKV8_SCRIPTDATA_H

#include "Base.h"

namespace v8 {


/**
 * Pre-compilation data that can be associated with a script.  This
 * data can be calculated for a script in advance of actually
 * compiling it, and can be stored between compilations.  When script
 * data is given to the compile method compilation will be faster.
 */
class V8EXPORT ScriptData {  // NOLINT
public:
    virtual ~ScriptData() { }

    /**
     * Pre-compiles the specified script (context-independent).
     *
     * \param input Pointer to UTF-8 script source code.
     * \param length Length of UTF-8 script source code.
     */
    static ScriptData *PreCompile(const char *input, int length);

    /**
     * Pre-compiles the specified script (context-independent).
     *
     * NOTE: Pre-compilation using this method cannot happen on another thread
     * without using Lockers.
     *
     * \param source Script source code.
     */
    static ScriptData *PreCompile(Handle<String> source);

    /**
     * Load previous pre-compilation data.
     *
     * \param data Pointer to data returned by a call to Data() of a previous
     *   ScriptData. Ownership is not transferred.
     * \param length Length of data.
     */
    static ScriptData *New(const char *data, int length);

    /**
     * Returns the length of Data().
     */
    virtual int Length() = 0;

    /**
     * Returns a serialized representation of this ScriptData that can later be
     * passed to New(). NOTE: Serialized data is platform-dependent.
     */
    virtual const char *Data() = 0;

    /**
     * Returns true if the source code could not be parsed.
     */
    virtual bool HasError() = 0;
};

}

#endif //DUKV8_SCRIPTDATA_H

//
// Created by Jiang Lu on 6/3/15.
//

#ifndef DUKV8_SCRIPT_H
#define DUKV8_SCRIPT_H

#include "Base.h"
#include "Handle.h"
#include "ScriptOrigin.h"
#include "ScriptData.h"
#include "GCObject.h"

namespace v8 {

/**
 * A compiled JavaScript script.
 */
class V8EXPORT Script : i::GCObject {
public:
    /**
     * Compiles the specified script (context-independent).
     *
     * \param source Script source code.
     * \param origin Script origin, owned by caller, no references are kept
     *   when New() returns
     * \param pre_data Pre-parsing data, as obtained by ScriptData::PreCompile()
     *   using pre_data speeds compilation if it's done multiple times.
     *   Owned by caller, no references are kept when New() returns.
     * \param script_data Arbitrary data associated with script. Using
     *   this has same effect as calling SetData(), but allows data to be
     *   available to compile event handlers.
     * \return Compiled script object (context independent; when run it
     *   will use the currently entered context).
     */
    static Local<Script> New(Handle<String> source,
                             ScriptOrigin *origin = NULL,
                             ScriptData *pre_data = NULL,
                             Handle<String> script_data = Handle<String>());

    /**
     * Compiles the specified script using the specified file name
     * object (typically a string) as the script's origin.
     *
     * \param source Script source code.
     * \param file_name file name object (typically a string) to be used
     *   as the script's origin.
     * \return Compiled script object (context independent; when run it
     *   will use the currently entered context).
     */
    static Local<Script> New(Handle<String> source,
                             Handle<Value> file_name);

    /**
     * Compiles the specified script (bound to current context).
     *
     * \param source Script source code.
     * \param origin Script origin, owned by caller, no references are kept
     *   when Compile() returns
     * \param pre_data Pre-parsing data, as obtained by ScriptData::PreCompile()
     *   using pre_data speeds compilation if it's done multiple times.
     *   Owned by caller, no references are kept when Compile() returns.
     * \param script_data Arbitrary data associated with script. Using
     *   this has same effect as calling SetData(), but makes data available
     *   earlier (i.e. to compile event handlers).
     * \return Compiled script object, bound to the context that was active
     *   when this function was called.  When run it will always use this
     *   context.
     */
    static Local<Script> Compile(Handle<String> source,
                                 ScriptOrigin *origin = NULL,
                                 ScriptData *pre_data = NULL,
                                 Handle<String> script_data = Handle<String>());

    /**
     * Compiles the specified script using the specified file name
     * object (typically a string) as the script's origin.
     *
     * \param source Script source code.
     * \param file_name File name to use as script's origin
     * \param script_data Arbitrary data associated with script. Using
     *   this has same effect as calling SetData(), but makes data available
     *   earlier (i.e. to compile event handlers).
     * \return Compiled script object, bound to the context that was active
     *   when this function was called.  When run it will always use this
     *   context.
     */
    static Local<Script> Compile(Handle<String> source,
                                 Handle<Value> file_name,
                                 Handle<String> script_data = Handle<String>());

    /**
     * Runs the script returning the resulting value.  If the script is
     * context independent (created using ::New) it will be run in the
     * currently entered context.  If it is context specific (created
     * using ::Compile) it will be run in the context in which it was
     * compiled.
     */
    Local<Value> Run();

    /**
     * Returns the script id value.
     */
    Local<Value> Id();

    /**
     * Associate an additional data object with the script. This is mainly used
     * with the debugger as this data object is only available through the
     * debugger API.
     */
    void SetData(Handle<String> data);


protected:
    Script(Handle<String> source,
           Handle<Value> file_name,
           Handle<Integer> line_unmber,
           Handle<String> script_data = Handle<String>());

    void TryCompile();

private:
    Handle<Context> context_;
    Handle<String> source_;
    Handle<Value> file_name_;
    Handle<Integer> line_number_;
    Handle<String> script_data_;

    Handle<Function> function_;
};

}

#endif //DUKV8_SCRIPT_H

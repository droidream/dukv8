//
// Created by Jiang Lu on 6/3/15.
//

#ifndef DUKV8_SCRIPTORIGIN_H
#define DUKV8_SCRIPTORIGIN_H

#include "Base.h"
#include "Handle.h"

namespace v8 {

/**
 * The origin, within a file, of a script.
 */
class ScriptOrigin {
public:
    inline ScriptOrigin(
            Handle<Value> resource_name,
            Handle<Integer> resource_line_offset = Handle<Integer>(),
            Handle<Integer> resource_column_offset = Handle<Integer>())
            : resource_name_(resource_name),
              resource_line_offset_(resource_line_offset),
              resource_column_offset_(resource_column_offset) { }
    inline Handle<Value> ResourceName() const;
    inline Handle<Integer> ResourceLineOffset() const;
    inline Handle<Integer> ResourceColumnOffset() const;

private:
    Handle<Value> resource_name_;
    Handle<Integer> resource_line_offset_;
    Handle<Integer> resource_column_offset_;

    friend class Script;
};

}


#endif //DUKV8_SCRIPTORIGIN_H

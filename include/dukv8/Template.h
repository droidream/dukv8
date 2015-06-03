//
// Created by Jiang Lu on 6/2/15.
//

#ifndef DUKV8_TEMPLATE_H
#define DUKV8_TEMPLATE_H

#include <map>
#include "Base.h"
#include "Handle.h"
#include "Data.h"
#include "String.h"

namespace v8 {

namespace internal {

class TemplateProperty {
public:
    Handle<Data> value_;
    PropertyAttribute attrib_;

public:
    TemplateProperty() :
            attrib_(None) { }
    TemplateProperty(Handle<Data> value, PropertyAttribute attrib) :
            value_(value), attrib_(attrib) { }
    TemplateProperty(const TemplateProperty &other) :
            value_(other.value_), attrib_(other.attrib_) { }
    TemplateProperty &operator=(const TemplateProperty &other) {
        value_ = other.value_;
        attrib_ = other.attrib_;
        return *this;
    }
};

struct StringCompare {
    bool operator()(const Handle<String> &key1, const Handle<String> &key2) const;
};

class TemplatePropertyMap : public std::map<Handle<String>, TemplateProperty, StringCompare> {
};

}

// --- Templates ---

/**
 * The superclass of object and function templates.
 */
class V8EXPORT Template : public Data {
public:
    RTTI_DECLARE();

    /** Adds a property to each instance created by this template.*/
    void Set(Handle<String> name,
             Handle<Data> value,
             PropertyAttribute attributes = None);

    void Set(const char *name, Handle<Data> value);

    virtual void ApplyToObject(Handle<Object> object);

private:
    Template();

    internal::TemplatePropertyMap template_property_map_;

    friend class ObjectTemplate;
    friend class FunctionTemplate;
};

}


#endif //DUKV8_TEMPLATE_H

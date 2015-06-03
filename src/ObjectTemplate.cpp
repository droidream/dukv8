//
// Created by Jiang Lu on 6/2/15.
//

#include <dukv8/ObjectTemplate.h>
#include <dukv8/Local.h>
#include <dukv8/Object.h>
#include <dukv8/Isolate.h>
#include <dukv8/DukStackScope.h>

namespace v8 {

RTTI_IMPLEMENT(v8::ObjectTemplate, v8::Template);

ObjectTemplate::ObjectTemplate() {
}

ObjectTemplate::~ObjectTemplate() {
}

/** Creates an ObjectTemplate. */
Local<ObjectTemplate> ObjectTemplate::New() {
    return Local<ObjectTemplate>::New(
            Handle<ObjectTemplate>(new ObjectTemplate()));
}

/** Creates a new instance of this template.*/
Local<Object> ObjectTemplate::NewInstance() {
    DukContextRef ctx = Isolate::GetCurrent()->GetDukContext();
    DUK_STACK_SCOPE(ctx);
    duk_push_object(ctx);
    Handle<Object> object(new Object(ctx, duk_get_heapptr(ctx, -1)));
    ObjectTemplate::ApplyToObject(object);
    // internal::Helper *helper = object->GetHelper();
    // helper->m_object_template = Handle<ObjectTemplate>(this);
    // helper->SetInternalFieldCount(m_internal_field_count);
    return Local<Object>::New(object);
}

void ObjectTemplate::ApplyToObject(Handle<Object> object) {
    Template::ApplyToObject(object);
}

//
// 设置属性拦截器
//
void ObjectTemplate::SetNamedPropertyHandler(NamedPropertyGetter getter,
                                             NamedPropertySetter setter,
                                             NamedPropertyQuery query,
                                             NamedPropertyDeleter deleter,
                                             NamedPropertyEnumerator enumerator,
                                             Handle<Value> data) {
}

/**
 * Gets the number of internal fields for objects generated from
 * this template.
 */
int ObjectTemplate::InternalFieldCount() {
    return 0;
}

/**
 * Sets the number of internal fields for objects generated from
 * this template.
 */
void ObjectTemplate::SetInternalFieldCount(int value) {
}

}
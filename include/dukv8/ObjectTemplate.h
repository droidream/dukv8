//
// Created by Jiang Lu on 6/2/15.
//

#ifndef DUKV8_OBJECTTEMPLATE_H
#define DUKV8_OBJECTTEMPLATE_H

#include <dukv8/Base.h>
#include <dukv8/Template.h>

namespace v8 {

/**
 * The information passed to an accessor callback about the context
 * of the property access.
 */
class V8EXPORT AccessorInfo {
public:
    inline AccessorInfo(internal::Object **args)
            : args_(args) { }
    inline Isolate *GetIsolate() const;
    inline Local<Value> Data() const;
    inline Local<Object> This() const;
    inline Local<Object> Holder() const;

private:
    internal::Object **args_;
};

/**
 * NamedProperty[Getter|Setter] are used as interceptors on object.
 * See ObjectTemplate::SetNamedPropertyHandler.
 */
typedef Handle<Value> (*NamedPropertyGetter)(Local<String> property,
                                             const AccessorInfo &info);


/**
 * Returns the value if the setter intercepts the request.
 * Otherwise, returns an empty handle.
 */
typedef Handle<Value> (*NamedPropertySetter)(Local<String> property,
                                             Local<Value> value,
                                             const AccessorInfo &info);

/**
 * Returns a non-empty handle if the interceptor intercepts the request.
 * The result is an integer encoding property attributes (like v8::None,
 * v8::DontEnum, etc.)
 */
typedef Handle<Integer> (*NamedPropertyQuery)(Local<String> property,
                                              const AccessorInfo &info);

/**
 * Returns a non-empty handle if the deleter intercepts the request.
 * The return value is true if the property could be deleted and false
 * otherwise.
 */
typedef Handle<Boolean> (*NamedPropertyDeleter)(Local<String> property,
                                                const AccessorInfo &info);

/**
 * Returns an array containing the names of the properties the named
 * property getter intercepts.
 */
typedef Handle<Array> (*NamedPropertyEnumerator)(const AccessorInfo &info);

/**
 * Returns the value of the property if the getter intercepts the
 * request.  Otherwise, returns an empty handle.
 */
typedef Handle<Value> (*IndexedPropertyGetter)(uint32_t index,
                                               const AccessorInfo &info);


/**
 * Returns the value if the setter intercepts the request.
 * Otherwise, returns an empty handle.
 */
typedef Handle<Value> (*IndexedPropertySetter)(uint32_t index,
                                               Local<Value> value,
                                               const AccessorInfo &info);


/**
 * Returns a non-empty handle if the interceptor intercepts the request.
 * The result is an integer encoding property attributes.
 */
typedef Handle<Integer> (*IndexedPropertyQuery)(uint32_t index,
                                                const AccessorInfo &info);

/**
 * Returns a non-empty handle if the deleter intercepts the request.
 * The return value is true if the property could be deleted and false
 * otherwise.
 */
typedef Handle<Boolean> (*IndexedPropertyDeleter)(uint32_t index,
                                                  const AccessorInfo &info);

/**
 * Returns an array containing the indices of the properties the
 * indexed property getter intercepts.
 */
typedef Handle<Array> (*IndexedPropertyEnumerator)(const AccessorInfo &info);

/**
 * Access type specification.
 */
enum AccessType {
    ACCESS_GET,
    ACCESS_SET,
    ACCESS_HAS,
    ACCESS_DELETE,
    ACCESS_KEYS
};

/**
 * Returns true if cross-context access should be allowed to the named
 * property with the given key on the host object.
 */
typedef bool (*NamedSecurityCallback)(Local<Object> host,
                                      Local<Value> key,
                                      AccessType type,
                                      Local<Value> data);

/**
 * Returns true if cross-context access should be allowed to the indexed
 * property with the given index on the host object.
 */
typedef bool (*IndexedSecurityCallback)(Local<Object> host,
                                        uint32_t index,
                                        AccessType type,
                                        Local<Value> data);

/**
 * 对象模板
 * 属性拦截器 SetNamedPropertyHandler 使用 Proxy 实现
 */
class ObjectTemplate : public Template {
public:
    RTTI_DECLARE();

    /** Creates an ObjectTemplate. */
    static Local<ObjectTemplate> New();

    /** Creates a new instance of this template.*/
    Local<Object> NewInstance();

    /**
     * Sets an accessor on the object template.
     *
     * Whenever the property with the given name is accessed on objects
     * created from this ObjectTemplate the getter and setter callbacks
     * are called instead of getting and setting the property directly
     * on the JavaScript object.
     *
     * \param name The name of the property for which an accessor is added.
     * \param getter The callback to invoke when getting the property.
     * \param setter The callback to invoke when setting the property.
     * \param data A piece of data that will be passed to the getter and setter
     *   callbacks whenever they are invoked.
     * \param settings Access control settings for the accessor. This is a bit
     *   field consisting of one of more of
     *   DEFAULT = 0, ALL_CAN_READ = 1, or ALL_CAN_WRITE = 2.
     *   The default is to not allow cross-context access.
     *   ALL_CAN_READ means that all cross-context reads are allowed.
     *   ALL_CAN_WRITE means that all cross-context writes are allowed.
     *   The combination ALL_CAN_READ | ALL_CAN_WRITE can be used to allow all
     *   cross-context access.
     * \param attribute The attributes of the property for which an accessor
     *   is added.
     * \param signature The signature describes valid receivers for the accessor
     *   and is used to perform implicit instance checks against them. If the
     *   receiver is incompatible (i.e. is not an instance of the constructor as
     *   defined by FunctionTemplate::HasInstance()), an implicit TypeError is
     *   thrown and no callback is invoked.
     */

//    void SetAccessor(Handle<String> name,
//                     AccessorGetter getter,
//                     AccessorSetter setter = 0,
//                     Handle<Value> data = Handle<Value>(),
//                     AccessControl settings = DEFAULT,
//                     PropertyAttribute attribute = None,
//                     Handle<AccessorSignature> signature =
//                     Handle<AccessorSignature>());

    /**
     * Sets a named property handler on the object template.
     *
     * Whenever a named property is accessed on objects created from
     * this object template, the provided callback is invoked instead of
     * accessing the property directly on the JavaScript object.
     *
     * \param getter The callback to invoke when getting a property.
     * \param setter The callback to invoke when setting a property.
     * \param query The callback to invoke to check if a property is present,
     *   and if present, get its attributes.
     * \param deleter The callback to invoke when deleting a property.
     * \param enumerator The callback to invoke to enumerate all the named
     *   properties of an object.
     * \param data A piece of data that will be passed to the callbacks
     *   whenever they are invoked.
     */

    void SetNamedPropertyHandler(NamedPropertyGetter getter,
                                 NamedPropertySetter setter = 0,
                                 NamedPropertyQuery query = 0,
                                 NamedPropertyDeleter deleter = 0,
                                 NamedPropertyEnumerator enumerator = 0,
                                 Handle<Value> data = Handle<Value>());

    /**
     * Sets an indexed property handler on the object template.
     *
     * Whenever an indexed property is accessed on objects created from
     * this object template, the provided callback is invoked instead of
     * accessing the property directly on the JavaScript object.
     *
     * \param getter The callback to invoke when getting a property.
     * \param setter The callback to invoke when setting a property.
     * \param query The callback to invoke to check if an object has a property.
     * \param deleter The callback to invoke when deleting a property.
     * \param enumerator The callback to invoke to enumerate all the indexed
     *   properties of an object.
     * \param data A piece of data that will be passed to the callbacks
     *   whenever they are invoked.
     */

    void SetIndexedPropertyHandler(IndexedPropertyGetter getter,
                                   IndexedPropertySetter setter = 0,
                                   IndexedPropertyQuery query = 0,
                                   IndexedPropertyDeleter deleter = 0,
                                   IndexedPropertyEnumerator enumerator = 0,
                                   Handle<Value> data = Handle<Value>());

    /**
     * Sets the callback to be used when calling instances created from
     * this template as a function.  If no callback is set, instances
     * behave like normal JavaScript objects that cannot be called as a
     * function.
     */
    void SetCallAsFunctionHandler(InvocationCallback callback,
                                  Handle<Value> data = Handle<Value>());

    /**
     * Mark object instances of the template as undetectable.
     *
     * In many ways, undetectable objects behave as though they are not
     * there.  They behave like 'undefined' in conditionals and when
     * printed.  However, properties can be accessed and called as on
     * normal objects.
     */
    void MarkAsUndetectable();

    /**
     * Sets access check callbacks on the object template.
     *
     * When accessing properties on instances of this object template,
     * the access check callback will be called to determine whether or
     * not to allow cross-context access to the properties.
     * The last parameter specifies whether access checks are turned
     * on by default on instances. If access checks are off by default,
     * they can be turned on on individual instances by calling
     * Object::TurnOnAccessCheck().
     */
    void SetAccessCheckCallbacks(NamedSecurityCallback named_handler,
                                 IndexedSecurityCallback indexed_handler,
                                 Handle<Value> data = Handle<Value>(),
                                 bool turned_on_by_default = true);

    /**
     * Gets the number of internal fields for objects generated from
     * this template.
     */
    int InternalFieldCount();

    /**
     * Sets the number of internal fields for objects generated from
     * this template.
     */
    void SetInternalFieldCount(int value);

    // v8 API

public:
    virtual void ApplyToObject(Handle<Object> object);

public:

    ObjectTemplate();

    virtual ~ObjectTemplate();

    friend class FunctionTemplate;

private:

    // @formatter:off
    NamedPropertyGetter     named_property_getter_;
    NamedPropertySetter     named_property_setter_;
    NamedPropertyQuery      named_property_query_;
    NamedPropertyDeleter    named_property_deleter_;
    NamedPropertyEnumerator named_property_enumerator_;
    Handle<Value>           named_property_data_;


//    InvocationCallback      call_as_function_invocation_callback_;
//    Handle<Value>           call_as_function_data_;

    // @formatter:on
};

}

#endif //DUKV8_OBJECTTEMPLATE_H

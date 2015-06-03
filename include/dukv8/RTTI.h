//
// Created by Jiang Lu on 5/31/15.
//

#ifndef DUKV8_RTTI_H
#define DUKV8_RTTI_H

#include <cstddef>

namespace v8 {
namespace internal {

/// v8::internal::RTTI

class RTTI {
public:
    RTTI(const char *name, const RTTI *base_rtti) :
            name_(name), base_rtti_(base_rtti) { }

    const char *GetName() const { return name_; }
    const RTTI *GetBaseRTTI() const { return base_rtti_; }

protected:
    const char *name_;
    const RTTI *base_rtti_;
};

// add to root class declaration
#define RTTI_DECLARE_ROOT(classname) \
    static const internal::RTTI rtti_; \
    virtual const internal::RTTI* GetRTTI() const { return &rtti_; } \
    virtual const char* GetTypeName() const { return rtti_.GetName(); } \
    static bool IsExactKindOf(const internal::RTTI* rtti, const classname* object) \
    { \
        return (object != NULL)?(object->IsExactKindOf(rtti)):(false); \
    } \
    bool IsExactKindOf(const internal::RTTI* rtti) const \
    { \
        return (GetRTTI() == rtti); \
    } \
    static bool IsKindOf(const internal::RTTI* rtti, const classname* object) \
    { \
        return (object != NULL)?(object->IsKindOf(rtti)):(false); \
    } \
    bool IsKindOf(const internal::RTTI* rtti) const \
    { \
        const internal::RTTI* tmp = GetRTTI(); \
        while (tmp != NULL) \
        { \
            if (tmp == rtti) \
            { \
                return true; \
            } \
            tmp = tmp->GetBaseRTTI(); \
        } \
        return false; \
    } \
    static classname* DynamicCast(const internal::RTTI* rtti, const classname* object) \
    { \
        return (object != NULL)?(object->DynamicCast(rtti)):(NULL); \
    } \
    classname* DynamicCast(const internal::RTTI* rtti) const \
    { \
        return (IsKindOf(rtti) ? (classname*) this : NULL ); \
    }

// add to class declaration
#define RTTI_DECLARE() \
    static const internal::RTTI rtti_; \
    virtual const internal::RTTI* GetRTTI() const { return &rtti_; } \
    virtual const char* GetTypeName() const { return rtti_.GetName(); }

// add to root class source file
#define RTTI_IMPLEMENT_ROOT(rootclassname) \
    const internal::RTTI rootclassname::rtti_(#rootclassname, NULL);

// add to class source file
#define RTTI_IMPLEMENT(classname, baseclassname) \
    const internal::RTTI classname::rtti_(#classname, &baseclassname::rtti_);

#define RTTI_GetRTTI(classname) \
    (&classname::rtti_)

#define RTTI_GetTypeName(classname) \
    (classname::rtti_.GetName())

#define RTTI_IsExactKindOf(classname, object) \
    classname::IsExactKindOf(&classname::rtti_, object)

#define RTTI_IsKindOf(classname, object) \
    classname::IsKindOf(&classname::rtti_, object)

#define RTTI_StaticCast(classname, object) \
    ((classname *) object)

#define RTTI_DynamicCast(classname, object) \
    ((classname *) classname::DynamicCast(&classname::rtti_, object))

}
}

#endif //DUKV8_RTTI_H

//
// Created by Jiang Lu on 6/2/15.
//

#ifndef DUKV8_DATA_H
#define DUKV8_DATA_H

#include "Base.h"
#include "GCObject.h"

namespace v8 {

class Data : public i::GCObject {
public:
    RTTI_DECLARE();

protected:
    virtual ~Data() { }
};

}


#endif //DUKV8_DATA_H

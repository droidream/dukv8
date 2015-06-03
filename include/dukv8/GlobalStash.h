//
// Created by Jiang Lu on 6/2/15.
//

#ifndef DUKV8_GLOBALSTASH_H
#define DUKV8_GLOBALSTASH_H

namespace v8 {
namespace internal {

class GlobalStash {
public:
    GlobalStash(const char *name);

    int AddObject(void *ptr);

    void RemoveObject(int index);

private:
    const char *name_;
};

}
}

#endif //DUKV8_GLOBALSTASH_H

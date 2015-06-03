//
// Created by Jiang Lu on 5/31/15.
//

#ifndef DUKV8_OBJECTLIST_H
#define DUKV8_OBJECTLIST_H

namespace v8 {
namespace internal {

class ObjectList {
public:
    ObjectList();
    ~ObjectList();

    void AddObject(void *val);

protected:
    void EnsureObjectList();
    void addNewList();
    void removeList();

private:
    int list_idx_;
    void *list_ptr_;
};

}
}

#endif //DUKV8_OBJECTLIST_H

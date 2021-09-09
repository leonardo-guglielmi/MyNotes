#ifndef MYNOTES_OBSERVER_H
#define MYNOTES_OBSERVER_H

#include <string>

class Observer {
public:
    // the observer receives the name of collection where the note is added/removed and the increment of the number of
    // notes contained in that collection (1 if the note is added, -1 if its removed).
    virtual void update(const std::string& collection, int increment) = 0;

    virtual ~Observer() = default;
};

#endif //MYNOTES_OBSERVER_H

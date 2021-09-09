#ifndef MYNOTES_SUBJECT_H
#define MYNOTES_SUBJECT_H

#include <list>
#include "Observer.h"

class Subject {
protected:
    std::list<Observer*> observerList;

public:
    virtual ~Subject() = default;

    void addObserver(Observer& o) { observerList.push_back(&o); }

    void removeObserver(Observer& o) { observerList.remove(&o); }

    // receives the title and the increment of the collection from the update was called.
    void notify(const std::string& title, int increment) {
        for(auto it : observerList)
           it->update(title, increment);
    }
};

#endif //MYNOTES_SUBJECT_H

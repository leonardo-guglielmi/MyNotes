#ifndef MYNOTES_FAVOURITECOLLECTION_H
#define MYNOTES_FAVOURITECOLLECTION_H

#include "Collection.h"

class FavouriteCollection: public Collection {
public:
    void insertNote(std::shared_ptr<Note>& n) override;

    bool removeNote(const std::string& title) override;
};


#endif //MYNOTES_FAVOURITECOLLECTION_H

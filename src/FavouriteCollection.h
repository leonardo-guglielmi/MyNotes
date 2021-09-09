#ifndef MYNOTES_FAVOURITECOLLECTION_H
#define MYNOTES_FAVOURITECOLLECTION_H

#include "Collection.h"

class FavouriteCollection: public Collection {
public:
    bool removeNote(std::string& title) override;
};


#endif //MYNOTES_FAVOURITECOLLECTION_H

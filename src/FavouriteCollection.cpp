#include "FavouriteCollection.h"

bool FavouriteCollection::removeNote(const std::string &title) {
    // from Collection class method, is removed the check about if the note is locked
    if(noteList.find(title) != noteList.end()) {
        noteList.erase(title);
        return true;
    }
    else
        return false;
}


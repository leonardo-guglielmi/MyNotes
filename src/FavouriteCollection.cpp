#include "FavouriteCollection.h"

void FavouriteCollection::insertNote(std::shared_ptr<Note> &n) {
    std::string title = n->getTitle();
    if(noteList.find(title) == noteList.end()) {
        n->setFavourite(true);
        noteList[title] = n;
    }
}

bool FavouriteCollection::removeNote(const std::string &title) {
    // from Collection class method, is removed the check about if the note is locked
    if(noteList.find(title) != noteList.end()) {
        noteList[title]->setFavourite(false);
        noteList.erase(title);
        return true;
    }
    else
        return false;
}


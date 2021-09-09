#include "CollectionManager.h"

/// methods to create objects
void CollectionManager::createNewCollection(std::string& name) {
    if(collectionList.find(name) == collectionList.end()) {
        // If collection manager doesn't contain a collection with the same name, create new smart pointer to it, set the
        // number of notes associated to it at zero and add at that subject's observer list itself
        collectionList[name] = std::make_shared<Collection>(name);
        numberOfNote[name] = 0;
        collectionList[name]->addObserver(*this);
    }
}

void CollectionManager::createNewNote(std::string& collection, std::string& title) {
    if(collectionList.find(collection) != collectionList.end() && !collectionList[collection]->containsNote(title)) {
        auto ptr = std::make_shared<Note>(title);
        collectionList[collection]->insertNote(ptr);
    }
}

/// methods that manage the interaction between objects
bool CollectionManager::moveNote(std::string &start, std::string &destination, std::string &noteTitle) {
    if(collectionList.find(start) != collectionList.end() && collectionList[start]->containsNote(noteTitle)) {
        // Save the pointer to the note, insert it in the destination collection and remove it from the start collection
        auto ptr = collectionList[start]->getNote(noteTitle);
        collectionList[destination]->insertNote(ptr);
        collectionList[start]->removeNote(ptr);
        return true;
    }
    else
        return false;
}

bool CollectionManager::copyNote(std::string &start, std::string &destination, std::string &noteTitle) {
    if(collectionList.find(start) != collectionList.end() && collectionList[start]->containsNote(noteTitle)) {
        // Save the pointer to the note and add it in the destination collection
        auto ptr = collectionList[start]->getNote(noteTitle);
        collectionList[destination]->insertNote(ptr);
        return true;
    }
    else
        return false;
}

/// methods that modify objects
bool CollectionManager::renameCollection(std::string &collection, std::string &newName) {
    if(collectionList.find(collection) != collectionList.end()) {
        // Update the name of collection, create a new entry with the new name as key and copy the content of the old
        // entry and after this remove the old entry.
        collectionList[collection]->setName(newName);
        collectionList[newName] = collectionList[collection];
        collectionList.erase(collection);
        return true;
    }
    else
        return false;
}

bool CollectionManager::renameNote(std::string &collection, std::string &noteTitle, std::string &newTitle) {
    if(collectionList.find(collection) != collectionList.end() && collectionList[collection]->containsNote(noteTitle)){
       collectionList[collection]->renameNote(noteTitle, newTitle);
       return true;
    }
    else
        return false;

}

bool CollectionManager::modifyText(std::string &collectionName, std::string &noteTitle, std::string &newText) {
    if(collectionList.find(collectionName) != collectionList.end() && collectionList[collectionName]->containsNote(noteTitle)){
        collectionList[collectionName]->modifyText(noteTitle, newText);
        return true;
    }
    else
        return false;
}

void CollectionManager::switchLock(std::string &collection, std::string &note) {
    collectionList[collection]->lockNote(note);
}

void CollectionManager::addToFavourites(std::shared_ptr<Note> note) {
    favourites.insertNote(note);
}

/// methods to remove objects
void CollectionManager::deleteCollection(std::string &name) {
    if(collectionList.find(name) != collectionList.end() && !collectionList[name]->allLocked()) {
        collectionList[name]->removeObserver(*this);
        collectionList.erase(name);
    }
    else
        throw std::logic_error("one or more notes are locked");
}

void CollectionManager::deleteNote(std::string &collectionName, std::string &noteTile) {
    if(collectionList.find(collectionName) != collectionList.end() && collectionList[collectionName]->containsNote(noteTile))
        try {
            collectionList[collectionName]->removeNote(noteTile);
        }
        catch(std::logic_error& e) { throw e; }
}

void CollectionManager::removeFromFavourites(std::string &title) {
    favourites.removeNote(title);
}

/// methods to check object's properties
bool CollectionManager::containsNote(std::string &collection, std::string &note) {
    return (collectionList.find(collection) != collectionList.end() && collectionList[collection]->containsNote(note));
}

bool CollectionManager::containsCollection(std::string &collection) {
    return (collectionList.find(collection) != collectionList.end());
}

std::shared_ptr<Note> CollectionManager::getNote(std::string &collection, std::string &note) {
    return collectionList[collection]->getNote(note);
}

std::set<std::string> CollectionManager::getNoteList(std::string& collection) const {
    std::set<std::string> set;
    auto ptr = collectionList.find(collection)->second;
    return ptr->getNoteList();
}

std::set<std::string> CollectionManager::getCollectionList() {
    std::set<std::string> set;
    for(const auto& it : collectionList)
        set.insert(it.first);
    return set;
}

std::set<std::string> CollectionManager::getFavourites() const {
    return favourites.getNoteList();
}

int CollectionManager::getNumberOfNotes(std::string &collection) {
    return numberOfNote[collection];
}
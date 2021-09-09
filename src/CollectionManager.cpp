#include "CollectionManager.h"

/// observer pattern method
void CollectionManager::update() {
    for(const auto& it : collectionList) {
        numberOfNote[it.first] = it.second->countNote();
    }
}

/// methods to create objects
void CollectionManager::createNewCollection(const std::string& name) {
    if(collectionList.find(name) == collectionList.end()) {
        // If collection manager doesn't contain a collection with the same name, create new smart pointer to it, set the
        // number of notes associated to it at zero and add at that subject's observer list itself
        collectionList[name] = std::make_shared<Collection>(name);
        numberOfNote[name] = 0;
        collectionList[name]->addObserver(*this);
    }
}

void CollectionManager::createNewNote(const std::string& collection, const std::string& title) {
    if(collectionList.find(collection) != collectionList.end() && !collectionList[collection]->containsNote(title)) {
        auto ptr = std::make_shared<Note>(title);
        collectionList[collection]->insertNote(ptr);
    }
}

/// methods that manage the interaction between objects
bool CollectionManager::moveNote(const std::string &start, const std::string &destination, const std::string &noteTitle) {
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

bool CollectionManager::copyNote(const std::string &start, const std::string &destination, const std::string &noteTitle) {
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
bool CollectionManager::renameCollection(const std::string &collection, const std::string &newName) {
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

bool CollectionManager::renameNote(const std::string &collection, const std::string &noteTitle, const std::string &newTitle) {
    if(collectionList.find(collection) != collectionList.end() && collectionList[collection]->containsNote(noteTitle)){
       collectionList[collection]->renameNote(noteTitle, newTitle);
       return true;
    }
    else
        return false;

}

bool CollectionManager::modifyText(const std::string &collectionName, const std::string &noteTitle, const std::string &newText) {
    if(collectionList.find(collectionName) != collectionList.end() && collectionList[collectionName]->containsNote(noteTitle)){
        collectionList[collectionName]->modifyText(noteTitle, newText);
        return true;
    }
    else
        return false;
}

void CollectionManager::switchLock(const std::string &collection, const std::string &note) {
    collectionList[collection]->lockNote(note);
}

void CollectionManager::addToFavourites(std::shared_ptr<Note> note) {
    favourites.insertNote(note);
}

/// methods to remove objects
void CollectionManager::deleteCollection(const std::string &name) {
    if(collectionList.find(name) != collectionList.end() && !collectionList[name]->allLocked()) {
        collectionList[name]->removeObserver(*this);
        collectionList.erase(name);
    }
    else
        throw std::logic_error("one or more notes are locked");
}

void CollectionManager::deleteNote(const std::string &collectionName, const std::string &noteTile) {
    if(collectionList.find(collectionName) != collectionList.end() && collectionList[collectionName]->containsNote(noteTile))
        try {
            collectionList[collectionName]->removeNote(noteTile);
        }
        catch(std::logic_error& e) { throw e; }
}

void CollectionManager::removeFromFavourites(const std::string &title) {
    favourites.removeNote(title);
}

/// methods to check object's properties
bool CollectionManager::containsNote(const std::string &collection, const std::string &note) {
    return (collectionList.find(collection) != collectionList.end() && collectionList[collection]->containsNote(note));
}

bool CollectionManager::containsCollection(const std::string &collection) {
    return (collectionList.find(collection) != collectionList.end());
}

std::shared_ptr<Note> CollectionManager::getNote(const std::string &collection, const std::string &note) {
    return collectionList[collection]->getNote(note);
}

std::set<std::string> CollectionManager::getNoteList(const std::string& collection) const {
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

int CollectionManager::getNumberOfNotes(const std::string &collection) {
    return numberOfNote[collection];
}
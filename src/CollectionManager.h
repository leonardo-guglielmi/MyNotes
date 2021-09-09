#ifndef MYNOTES_COLLECTIONMANAGER_H
#define MYNOTES_COLLECTIONMANAGER_H

#include <map>
#include <string>
#include <set>
#include <memory>
#include <stdexcept>
#include "Collection.h"
#include "Observer.h"

/*
 * This class handle all collections, all operation users can do and the interaction with them.
*/

class CollectionManager: public Observer{
private:
    // List contains all collections, using name as key
    std::map<std::string, std::shared_ptr<Collection>> collectionList;
    Collection favourites;
    // This map associate at each collections, used it's name as key, the number of notes that collection contains
    std::map<std::string, int> numberOfNote;

public:
    ///// constructor & destructor /////
    CollectionManager(): favourites("favourites") { }
    ~CollectionManager() override = default;

    ///// observer pattern methods /////
    void update(const std::string &collection, int increment) override {
        numberOfNote[collection] += increment;
    }

    ///// other methods /////

    /// methods to create objects
    void createNewCollection(std::string& name);

    void createNewNote(std::string& collection, std::string& title);

    /// methods to manage the interaction between collections
    // Move the note from one collection to another
    bool moveNote(std::string& start, std::string& destination, std::string& noteTitle);

    // copy the selected note from start collection into destination collection
    bool copyNote(std::string& start, std::string& destination, std::string& noteTitle);

    /// methods to modify objects
    bool renameCollection(std::string& collection, std::string& newName);

    bool renameNote(std::string& collection, std::string& noteTitle, std::string& newTitle);

    bool modifyText(std::string& collectionName, std::string& noteTitle, std::string& newText);

    void switchLock(std::string& collection, std::string& note);

    void addToFavourites(std::shared_ptr<Note> note);

    /// methods to remove objects
    void deleteCollection(std::string& name);

    void deleteNote(std::string& collectionName, std::string& noteTile);

    void removeFromFavourites(std::string& title);

    /// methods to check object's properties
    bool containsNote(std::string& collection, std::string& note);

    bool containsCollection(std::string& collection);

    std::shared_ptr<Note> getNote(std::string& collection, std::string& note);

    // return a set that contain the titles of all notes in specified collectionS
    std::set<std::string> getNoteList(std::string& collection) const ;

    // return a set that contain the names of all collection
    std::set<std::string> getCollectionList();

    std::set<std::string> getFavourites() const;

    // Return the number associated to collection in map "numberOfNotes"
    int getNumberOfNotes(std::string& collection);
};

#endif //MYNOTES_COLLECTIONMANAGER_H

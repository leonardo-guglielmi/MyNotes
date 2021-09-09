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
    void update() override;

    ///// other methods /////

    /// methods to create objects
    void createNewCollection(const std::string& name);

    void createNewNote(const std::string& collection, const std::string& title);

    /// methods to manage the interaction between collections
    // Move the note from one collection to another
    bool moveNote(const std::string& start, const std::string& destination, const std::string& noteTitle);

    // copy the selected note from start collection into destination collection
    bool copyNote(const std::string& start, const std::string& destination, const std::string& noteTitle);

    /// methods to modify objects
    bool renameCollection(const std::string& collection, const std::string& newName);

    bool renameNote(const std::string& collection, const std::string& noteTitle, const std::string& newTitle);

    bool modifyText(const std::string& collectionName, const std::string& noteTitle, const std::string& newText);

    void switchLock(const std::string& collection, const std::string& note);

    void addToFavourites(std::shared_ptr<Note> note);

    /// methods to remove objects
    void deleteCollection(const std::string& name);

    void deleteNote(const std::string& collectionName, const std::string& noteTile);

    void removeFromFavourites(const std::string& title);

    /// methods to check object's properties
    bool containsNote(const std::string& collection, const std::string& note);

    bool containsCollection(const std::string& collection);

    std::shared_ptr<Note> getNote(const std::string& collection, const std::string& note);

    // return a set that contain the titles of all notes in specified collectionS
    std::set<std::string> getNoteList(const std::string& collection) const ;

    // return a set that contain the names of all collection
    std::set<std::string> getCollectionList();

    std::set<std::string> getFavourites() const;

    // Return the number associated to collection in map "numberOfNotes"
    int getNumberOfNotes(const std::string& collection);
};

#endif //MYNOTES_COLLECTIONMANAGER_H

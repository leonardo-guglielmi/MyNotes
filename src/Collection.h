#ifndef MYNOTES_COLLECTION_H
#define MYNOTES_COLLECTION_H

#include <map>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include "Note.h"
#include "Subject.h"

/*
 * This class collect notes and have methods to handle the collection (insert new note, delete another one ecc. ecc.).
 * It also extends teh Subject class to update the observers when add or remove a note.
*/
class Collection: public Subject {
protected:
    // The map use the note's title as key (use shared_ptr cause more collection can contain the same note).
    std::map<std::string, std::shared_ptr<Note>> noteList;
    std::string name;

public:
    ///// Constructors & destructor /////
    explicit Collection(const std::string& name): name(name) { }

    ~Collection() override = default;

    ///// Getter&Setter /////
    const std::string& getName() const { return name; }
    void setName(const std::string& name) { Collection::name = name; }

    ////// other methods /////
    // Insert note in the collection
    virtual void insertNote(std::shared_ptr<Note>& n);

    // remove the note from collection with its reference
    bool removeNote(std::shared_ptr<Note>& n);

    // remove note from collection with its title
    virtual bool removeNote(const std::string& title);

    // return a pointer to the note
    std::shared_ptr<Note> getNote(const std::string& title);

    // return true if the collection contain the note, false if it doesn't contain the note
    bool containsNote(const std::string& title) const;

    // rename note
    bool renameNote(const std::string& noteTitle, const std::string& newTitle);

    // modify text of note
    bool modifyText(const std::string& title, const std::string& newText);

    // lock/unlock note
    bool lockNote(const std::string& title);

    // check if all the notes in the collection are unlocked
    bool allLocked() const;

    // return a set with the titles of all notes
    std::set<std::string> getNoteList() const;
};

#endif //MYNOTES_COLLECTION_H

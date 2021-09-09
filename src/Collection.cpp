#include "Collection.h"

void Collection::insertNote(std::shared_ptr<Note>& n) {
    const std::string& title = n->getTitle();
    // checks if the collection doesn't already contains that note, in that case its add the note and notify the observers
    if(noteList.find(title) == noteList.end()) {
        noteList[title] = n;
        Subject::notify(this->name, 1);
    }
}

bool Collection::removeNote(std::shared_ptr<Note>& n) {
    std::string title = n->getTitle();
    // Check if the note is contained in the collection, if it isn't return false
    if(noteList.find(title) != noteList.end()) {
       // Check if the note is locked, in that case throw an exception.
       // If it's not locked, remove it from the list and notify the observers.
        if(!noteList[title]->isLocked()) {
           noteList.erase(title);
           Subject::notify(this->name, -1);
           return true;
        }
        else
            throw std::logic_error("note is locked");
    }
    else
        return false;
}

bool Collection::removeNote(std::string& title) {
    // Check if the note is contained in the collection, if it isn't return false
    if(noteList.find(title) != noteList.end()) {
        // Check if the note is locked, in that case throw an exception
        // If it's not locked, remove it from the list and notify the observers
        if(!noteList[title]->isLocked()) {
            noteList.erase(title);
            Subject::notify(this->name, -1);
            return true;
        }
        else
            throw std::logic_error("note is locked");
    }
    else
        return false;
}

std::shared_ptr<Note> Collection::getNote(std::string& title) {
    return noteList[title];
}

bool Collection::containsNote(std::string &title) const {
    return (noteList.find(title) != noteList.end());
}

bool Collection::renameNote(std::string &noteTitle, std::string &newTitle) {
    if(noteList.find(noteTitle) != noteList.end()) {
        // Create new tuple in list with new title as key and a copy of the note with the old title, update the new
        // entry's title and remove the tuple that use the old title as key
        noteList[newTitle] = noteList[noteTitle];
        noteList[newTitle]->setTitle(newTitle);
        noteList.erase(noteTitle);
        return true;
    }
    else
        return false;
}

bool Collection::modifyText(std::string &title, std::string &newText) {
    if(noteList.find(title) != noteList.end()) {
        noteList[title]->setText(newText);
        return true;
    } else
        return false;
}

bool Collection::lockNote(std::string& title) {
    if(noteList.find(title) != noteList.end()){
        // Switch the lock state of the note
        bool lock = !noteList[title]->isLocked();
        noteList[title]->setLocked(lock);
        return true;
    }
    else
        return false;
}

bool Collection::allLocked() const {
    bool allLocked = true;
    auto it = noteList.begin();
    while(it != noteList.end() && allLocked){
        if(!it->second->isLocked())
            allLocked = false;
        it++;
    }
    return allLocked;
}

std::set<std::string> Collection::getNoteList() const {
    std::set<std::string> set;
    for(const auto& it : noteList) {
        set.insert(it.first);
    }
    return set;
}
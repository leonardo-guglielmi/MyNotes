#ifndef MYNOTES_INTERFACE_H
#define MYNOTES_INTERFACE_H

#include <string>
#include <iostream>
#include <memory>
#include <set>
#include <stdexcept>
#include "CollectionManager.h"

/*
 * This class is the only one that interact with the user
*/

class Interface {
private:
    CollectionManager cm;
    std::string helpString = ">> methods to CREATE objects\n"
                             "- newCollection: creates new collection\n"
                             "- newNote: creates new note\n"
                             ">> methods to manager INTERACTION between object\n"
                             "- moveNote: moves specified note from actual collection to another\n"
                             ">> methods to MODIFY objects\n"
                             "- renameCollection: rename specified collection\n"
                             "- renameNote: rename specified note in specified collection\n"
                             "- modifyText: modify note's text in one collection\n"
                             "- switchLock: switch lock state of note\n"
                             "- addFavourites: add one note to favourites collection\n"
                             ">> methods to REMOVE objects\n"
                             "- deleteCollection: delete collection and all its content\n"
                             "- deleteNote: delete note\n"
                             "- removeFavourites: remove note from favourites\n"
                             ">> methods to VIEW object's properties\n"
                             "- printNote: print note\n"
                             "- printCollection: print collection and all its note\n"
                             "- countNote: count notes in one collection\n"
                             "- lisNote: list all notes in a collection\n"
                             "- listCollection: list all collections\n"
                             "- listFavourites: list all favourites notes\n"
                             ">> others\n"
                             "- exit: exit from program";

public:
    /// constructor
    Interface() {
        std::cout << "Welcome to MyNote!" << std::endl;
    }

    // Selects command from user input (main method)
    void home();

    // The follows methods works only as interface for methods of class CollectionManager
    /// methods to create objects
    void createNewCollection();

    void createNewNote();

    /// methods to manage the interaction between collections
    void moveNote();

    /// methods to modify objects
    void renameCollection();

    void renameNote();

    void modifyText();

    void switchLock();

    void addFavourites();

    /// methods to remove objects
    void deleteCollection();

    void deleteNote();

    void removeFavourites();

    /// methods to view object's properties
    void printNote();

    void printCollection();

    void countNotes();

    void listNote();

    void listCollection();

    void listFavourites();
};

#endif //MYNOTES_INTERFACE_H

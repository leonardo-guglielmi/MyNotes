#include "Interface.h"

void Interface::home() {
    bool exitFlag = false;
    std::string cmd;
    /*
     * Takes input from keyboard the command and store it in cmd var.
     * The var cmd is compared with all commands, and if the content of variable is equal to one of them, the relative
     * function it's called.
    */
    do {
        std::cout << std::endl << "Insert command, or digit \"help\" for print all the commands: ";
        std::cin >> cmd;
        if(cmd == "newCollection") {
            createNewCollection();
        }
        else if(cmd == "newNote") {
            createNewNote();
        }
        else if(cmd == "moveNote") {
            moveNote();
        }
        else if(cmd == "renameCollection") {
            //
            renameCollection();
        }
        else if(cmd == "renameNote") {
            renameNote();
        }
        else if(cmd == "modifyText") {
            modifyText();
        }
        else if(cmd == "switchLock") {
            switchLock();
        }
        else if(cmd == "addFavourites"){
            addFavourites();
        }
        else if(cmd == "deleteCollection") {
            deleteCollection();
        }
        else if(cmd == "deleteNote") {
            deleteNote();
        }
        else if(cmd == "removeFavourites") {
            removeFavourites();
        }
        else if(cmd == "printNote") {
            printNote();
        }
        else if(cmd == "printCollection") {
            printCollection();
        }
        else if(cmd == "countNote") {
            countNotes();
        }
        else if(cmd == "listNote") {
            listNote();
        }
        else if(cmd == "listCollection") {
            listCollection();
        }
        else if(cmd == "listFavourites") {
            listFavourites();
        }
        else if(cmd == "help") {
            std::cout << helpString << std::endl;
        }
        else if(cmd == "exit")
            exitFlag = true;
        else
            std::cout << "Invalid option: wrong input" << std::endl;
    } while(!exitFlag);
}

void Interface::createNewCollection() {
    std::string newCollName;
    std::cout << "Insert new collection name: ";
    std::cin >> newCollName;
    cm.createNewCollection(newCollName);
}

void Interface::createNewNote() {
    std::string collName;
    std::string noteTitle;
    std::cout << "Insert collection name: ";
    std::cin >> collName;
    std::cout << "Insert new note title: ";
    std::cin >> noteTitle;
    cm.createNewNote(collName, noteTitle);
}

void Interface::moveNote() {
    std::string startCollection;
    std::string destinationCollection;
    std::string noteTitle;
    std::cout << "Insert start collection name: ";
    std::cin >> startCollection;
    std::cout << "Insert destination collection name: ";
    std::cin >> destinationCollection;
    std::cout << "Insert note title: ";
    std::cin >> noteTitle;
    if(cm.moveNote(startCollection, destinationCollection, noteTitle))
        std::cout << "Note moved: success" << std::endl;
    else
        std::cout << "Note moved: fail" << std::endl;
}

void Interface::renameCollection() {
    std::string subject;
    std::string newName;
    std::cout << "Insert actual collection name: ";
    std::cin >> subject;
    std::cout << "Insert new collection name: ";
    std::cin >> newName;
    if(cm.renameCollection(subject, newName))
        std::cout << "Collection renamed successfully" << std::endl;
    else
        std::cout << "Collection doesn't found" << std::endl;
}

void Interface::renameNote() {
    std::string collection;
    std::string subject;
    std::string newTitle;
    std::cout << "Insert collection's name: ";
    std::cin >> collection;
    std::cout << "Insert note's name: ";
    std::cin >> subject;
    std::cout << "Insert new note name: ";
    std::cin >> newTitle;
    if(cm.renameNote(collection, subject, newTitle))
        std::cout << "Note rename successfully" << std::endl;
    else
        std::cout << "Note doesn't found" << std::endl;
}

void Interface::modifyText() {
    std::string collection;
    std::string note;
    std::string newText;
    std::cout << "Insert collection's name: ";
    std::cin >> collection;
    std::cout << "Insert note's name: ";
    std::cin >> note;
    std::cout << "Insert new note's text";
    std::cin >> newText;
    if(cm.modifyText(collection, note, newText))
        std::cout << "Note's text modified successfully" << std::endl;
    else
        std::cout << "Collection or Note doesn't found" << std::endl;
}

void Interface::switchLock() {
    std::string collection;
    std::string note;
    std::cout << "Insert collection's name: ";
    std::cin >> collection;
    std::cout << "Insert note's title: ";
    std::cin >> note;
    cm.switchLock(collection, note);
}

void Interface::addFavourites() {
    std::string collection;
    std::string note;
    std::cout << "Insert collection's name: ";
    std::cin >> collection;
    std::cout << "Insert note's title: ";
    std::cin >> note;
    auto ptr = cm.getNote(collection, note);
    cm.addToFavourites(ptr);
}

void Interface::deleteCollection() {
    std::string collection;
    std::cout << "Insert collection's name: ";
    std::cin >> collection;
    try {
        cm.deleteCollection(collection);
    }
    catch(std::logic_error& e) {
        std::cout << "error: " << e.what() << std::endl;
    }
}

void Interface::deleteNote() {
    std::string collection;
    std::string note;
    std::cout << "Insert collection's name: ";
    std::cin >> collection;
    std::cout << "Insert note's title: ";
    std::cin >> note;
    try {
        cm.deleteNote(collection, note);
    }
    catch(std::logic_error& e) {
        std::cout << "error: " << e.what() << std::endl;
    }
}

void Interface::removeFavourites() {
    std::string note;
    std::cout << "Insert note's title: ";
    std::cin >> note;
    cm.removeFromFavourites(note);
}

void Interface::printNote() {
    std::string collection;
    std::string note;
    std::string text;
    std::cout << "Insert collection's name: ";
    std::cin >> collection;
    std::cout << "insert note's title";
    std::cin >> note;
    auto ptr = cm.getNote(collection, note);
    text = ptr->getText();
    std::cout << collection + '/' + note + ':' << std::endl << text;
}

void Interface::printCollection() {
    std::string collection;
    std::cout << "Insert collection's name: ";
    std::cin >> collection;

    std::set<std::string> set = cm.getNoteList(collection);
    std::shared_ptr<Note> ptr;
    for(const auto & it : set){
        ptr = cm.getNote(collection, const_cast<std::string &>(it));
        std::cout << "Title: " << ptr->getTitle() << std::endl;
        std::cout << "Locked: " << ptr->isLocked() << std::endl;
        std::cout << "Text: " << std::endl << ptr->getText() << std::endl;
    }
}

void Interface::countNotes() {
    std::string collection;
    std::cout << "Insert collection's name: ";
    std::cin >> collection;
    std::cout << "Collection " << collection << " contains " << cm.getNumberOfNotes(collection) << " notes" << std::endl;
}

void Interface::listNote() {
    std::set<std::string> set;
    std::string collection;
    std::cout << "Insert collection's name: ";
    std::cin >> collection;
    set = cm.getNoteList(collection);
    for(const auto& it : set){
        std::cout << const_cast<std::string &>(it) << std::endl;
    }
}

void Interface::listCollection() {
    std::set<std::string> set;
    set = cm.getCollectionList();
    for(const auto& it : set){
        std::cout << const_cast<std::string &>(it) << std::endl;
    }
}

void Interface::listFavourites() {
    std::set<std::string> set = cm.getFavourites();
    for(const auto& it : set){
        std::cout << const_cast<std::string &>(it) << std::endl;
    }
}
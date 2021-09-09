#ifndef MYNOTES_NOTE_H
#define MYNOTES_NOTE_H

#include <string>
#include <stdexcept>

/*
 * This class contain information about one single note, and all the methods related
*/

class Note{

private:
    std::string title;
    std::string text;
    bool locked = false;


public:
    ///// constructors & destructor /////
    explicit Note(std::string& title): title(title) { }

    Note(std::string& title, std::string& text): title(title), text(text) { }

    ~Note() = default;

    ///// other methods //////
    // setter of text and title checks if the note is locke, in that case they avoid to modify teh note.
    const std::string& getTitle() const { return title; }

    void setTitle(const std::string& title);

    const std::string& getText() const { return text; }

    void setText(const std::string& text);

    bool isLocked() const { return locked; }

    void setLocked(bool locked) { Note::locked = locked; }
};


#endif //MYNOTES_NOTE_H

#include "Note.h"

void Note::setText(const std::string &text) {
    if(!locked)
        Note::text = text;
    else
        throw std::logic_error("note locked");
}

void Note::setTitle(const std::string &title) {
    if(!locked)
        Note::title = title;
    else
        throw std::logic_error("note locked");
}
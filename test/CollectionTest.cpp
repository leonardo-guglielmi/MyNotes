#include <gtest/gtest.h>
#include "../src/Collection.h"

TEST(CollectionTest, TestInsert) {
    Collection c ("test");
    std::string noteTitle = "testNote";
    std::shared_ptr<Note> ptr = std::make_shared<Note>(noteTitle);
    c.insertNote(ptr);
    ASSERT_EQ(ptr, c.getNote(noteTitle));
}


TEST(CollectionTest, TestRemoveNote) {
    Collection c ("test");
    std::string noteTitle = "testNote";
    c.insertEmptyNote(noteTitle);
    // testing on locked note
    c.lockNote(noteTitle); //set lock=true
    ASSERT_THROW(c.removeNote(noteTitle), std::logic_error);

    // testing on unlocked note
    c.lockNote(noteTitle); //set lock=false
    ASSERT_TRUE(c.removeNote(noteTitle));

    // testing the remove of a non-contained note
    EXPECT_FALSE(c.removeNote(noteTitle));
}

TEST(CollectionTest, TestContainsNote) {
    Collection c ("test");
    std::string noteTitle = "title";
    c.insertEmptyNote(noteTitle);

    // testing that the function returns the correct result
    ASSERT_TRUE(c.containsNote(noteTitle));

    // testing that the function return false if the note isn't contained
    std::string otherNote = "other";
    EXPECT_FALSE(c.containsNote(otherNote));
}

TEST(CollectionTest, TestRenameNote) {
    Collection c ("test");
    std::string title = "title";
    c.insertEmptyNote(title);
    std::string newTitle = "new title";

    // testing that the function ha renamed correctly the function
    ASSERT_TRUE(c.renameNote(title, newTitle));

    // testing that the old collection name doesn't appear in collection
    std::string otherTitle = "other";
    ASSERT_FALSE(c.renameNote(otherTitle, newTitle));
}

TEST(CollectionTest, TestModifyText) {
    Collection c ("test");
    std::string title = "title";
    std::string text = "text";
    c.insertEmptyNote(title);
    EXPECT_TRUE(c.modifyText(title, text));

    // checking if the text in the modified note is correct
    std::string res = c.getNote(title)->getText();
    ASSERT_EQ(text, res);

    // checking that doesn't modify the text of a not-existing note
    std::string otherTitle = "other";
    EXPECT_FALSE(c.modifyText(otherTitle, text));
}

TEST(CollectionTest, TestLockNote) {
    Collection c ("test");
    std::string title = "title";
    c.insertEmptyNote(title);
    bool firstState = c.getNote(title)->isLocked();
    EXPECT_TRUE(c.lockNote(title));

    // checking if the note is modified correctly
    bool secondState = c.getNote(title)->isLocked();
    ASSERT_NE(firstState, secondState);

    // checking that the function doesn't modify a non-existing note
    std::string otherTitle = "other";
    EXPECT_FALSE(c.lockNote(otherTitle));
}

TEST(CollectionTest, TestAllLocked) {
    Collection c ("test");
    std::string firstTitle = "title1";
    std::string secondTitle = "title2";
    c.insertEmptyNote(firstTitle);
    c.insertEmptyNote(secondTitle);
    c.lockNote(firstTitle);
    EXPECT_FALSE(c.allLocked());
    c.lockNote(secondTitle);
    ASSERT_TRUE(c.allLocked());
}

TEST(CollectionTest, TestGetNoteList) {
    Collection c ("test");
    std::string firstTitle = "title1";
    std::string secondTitle = "title2";
    c.insertEmptyNote(firstTitle);
    c.insertEmptyNote(secondTitle);
    auto set = c.getNoteList();

    // making a loop to check that the returned set contain all the notes' title
    std::string itTitle;
    bool allContained = true;
    for(auto it : set){
        itTitle = const_cast<std::string &>(it);
        if(!c.containsNote(itTitle))
            allContained = false;
    }
    ASSERT_TRUE(allContained);
}
#include <gtest/gtest.h>
#include "../src/CollectionManager.h"

/// creation methods
TEST(CollectionManagerTest, TestCreateNewCollection) {
    CollectionManager cm;
    std::string collection = "collection";
    cm.createNewCollection(collection);
    ASSERT_TRUE(cm.containsCollection(collection));
}

TEST(CollectionManagerTest, TestCreateNewNote) {
    CollectionManager cm;
    std::string collection = "collection";
    std::string note = "note";
    cm.createNewCollection(collection);
    cm.createNewNote(collection, note);
    ASSERT_TRUE(cm.containsNote(collection, note));
}

/// interaction methods
TEST(CollectionManagerTest, TestMoveNote) {
    CollectionManager cm;
    // creating new collections
    std::string firstCollection = "collection1";
    std::string secondCollection = "collection2";
    cm.createNewCollection(firstCollection);
    cm.createNewCollection(secondCollection);

    // create a new note
    std::string note = "note";
    cm.createNewNote(firstCollection, note);

    // testing the method
    cm.moveNote(firstCollection, secondCollection, note);
    ASSERT_TRUE(cm.containsNote(secondCollection, note));
    ASSERT_FALSE(cm.containsNote(firstCollection, note));
}

TEST(CollectionManagerTest, TestCopyNote) {
    CollectionManager cm;
    // creating new method
    std::string firstCollection = "collection1";
    std::string secondCollection = "collection2";
    cm.createNewCollection(firstCollection);
    cm.createNewCollection(secondCollection);

    // create a new note
    std::string note = "note";
    cm.createNewNote(firstCollection, note);

    // testing the method
    cm.copyNote( firstCollection, secondCollection, note);
    EXPECT_TRUE(cm.containsNote(firstCollection, note));
    // todo: fix function
    ASSERT_TRUE(cm.containsNote(secondCollection, note));
}

/// interaction methods
TEST(CollectionManagerTest, TestRenameCollection) {
    CollectionManager cm;
    // creating a new collection
    std::string collection = "name";
    std::string newCollection = "newName";
    cm.createNewCollection(collection);

    // testing the method
    EXPECT_TRUE(cm.renameCollection(collection, newCollection));
    ASSERT_TRUE(cm.containsCollection(newCollection));
    ASSERT_FALSE(cm.containsCollection(collection));
}

TEST(CollectionManagerTest, TestRenameNote) {
    CollectionManager cm;
    // creating a new collection and a new note
    std::string collection = "collection";
    std::string note = "title";
    std::string newNote = "newTitle";
    cm.createNewCollection(collection);
    cm.createNewNote(collection, note);

    // testing the method
    EXPECT_TRUE(cm.renameNote(collection, note, newNote));
    ASSERT_TRUE(cm.containsNote(collection,newNote));
    ASSERT_FALSE(cm.containsNote(collection, note));
}

TEST(CollectionManagerTest, TestModifyText) {
    CollectionManager cm;
    // creating new collection and new note
    std::string collection = "collection";
    std::string note = "title";
    std::string newText = "newText";
    cm.createNewCollection(collection);
    cm.createNewNote(collection, note);

    // testing method
    EXPECT_TRUE(cm.modifyText(collection, note, newText));
    ASSERT_EQ(newText, cm.getNote(collection,note)->getText());
}

TEST(CollectionManagerTest, TestSwitchLock) {
    CollectionManager cm;
    // creating new collection and new note
    std::string collection = "collection";
    std::string note = "title";
    cm.createNewCollection(collection);
    cm.createNewNote(collection, note);

    // saving old note's lock state
    bool oldLockState = cm.getNote(collection, note)->isLocked();

    // testing the method
    cm.switchLock(collection, note);
    ASSERT_NE(oldLockState, cm.getNote(collection,note)->isLocked());

}

TEST(CollectionManagerTest, TestAddToFavourites) {
    CollectionManager cm;
    // creating new collection and new note
    std::string collection = "collection";
    std::string note = "title";
    cm.createNewCollection(collection);
    cm.createNewNote(collection, note);

    // adding the note to favourites
    auto ptr = cm.getNote(collection, note);
    cm.addToFavourites(ptr);

    // checking with a loop if the result set contain the title of the new favourite note
    auto set = cm.getFavourites();
    bool isContainedInFavourites = false;
    for(auto it : set){
        if(const_cast<std::string &>(it) == ptr->getTitle())
            isContainedInFavourites = true;
    }
    ASSERT_TRUE(isContainedInFavourites);
}

/// remove methods
TEST(CollectionManagerTest, TestRemoveMethods) {
    // setup of test
    CollectionManager cm;
    std::string collection = "name";
    cm.createNewCollection(collection);
    std::string note = "title";
    cm.createNewNote(collection, note);

    // testing that the method doesn't remove a collection that contain almost a lock note
    cm.switchLock(collection, note); //set locked=true
    ASSERT_THROW(cm.deleteCollection(collection), std::logic_error);

    // testing the method remove collection
    cm.switchLock(collection, note); //set locked=false
    cm.deleteCollection(collection);
    ASSERT_FALSE(cm.containsCollection(collection));
}

TEST(CollectionManagerTest, TestDeleteNote) {
    // setting up the test
    CollectionManager cm;
    std::string collection = "name";
    cm.createNewCollection(collection);
    std::string note = "title";
    cm.createNewNote(collection, note);

    // testing that the method doesn't remove a locked note
    cm.switchLock(collection, note); //set locked=true
    ASSERT_THROW(cm.deleteNote(collection, note), std::logic_error);

    // testing that method remove the unlocked note
    cm.switchLock(collection, note); //set locked=false
    cm.deleteNote(collection, note);
    ASSERT_FALSE(cm.containsNote(collection, note));
}

TEST(CollectionManagerTest, TestRemoveFromFavourites) {
    // setting up of test
    CollectionManager cm;
    std::string collection = "name";
    cm.createNewCollection(collection);
    std::string note = "title";
    cm.createNewNote(collection, note);
    auto ptr = cm.getNote(collection, note);
    cm.addToFavourites(ptr);

    // testing tht method doesn't remove from favourites a lock method
    cm.switchLock(collection, note); //set locked=true
    ASSERT_THROW(cm.removeFromFavourites(note), std::logic_error);

    // removing the unlocked method
    cm.switchLock(collection, note); //set locked=false
    cm.removeFromFavourites(note);

    // checking with a loop if the return set contain the note's title
    auto set = cm.getFavourites();
    bool isContainedInFavourites = false;
    for(auto it : set){
        if(const_cast<std::string &>(it) == ptr->getTitle())
            isContainedInFavourites = true;
    }
    ASSERT_FALSE(isContainedInFavourites);

}

/// check properties methods
TEST(CollectionManagerTest, TestCheckPropertiesMethods) {
    CollectionManager cm;
    std::string collection = "collection";

    // testing method
    cm.createNewCollection(collection);
    ASSERT_TRUE(cm.containsCollection(collection));

    // testing false case
    std::string fakeCollection = "fakeCollection";
    ASSERT_FALSE(cm.containsCollection(fakeCollection));
}

TEST(CollectionManagerTest, TestContainsNote) {
    CollectionManager cm;
    std::string collection = "collection";
    std::string note= "note";
    cm.createNewCollection(collection);

    // testing the method
    cm.createNewNote(collection, note);
    ASSERT_TRUE(cm.containsNote(collection, note));

    // testing some false cases
    std::string fakeCollection = "fakeCollection";
    std::string fakeNote = "fakeNote";
    ASSERT_FALSE(cm.containsNote(collection, fakeNote));
    ASSERT_FALSE(cm.containsNote(fakeCollection, note));
    ASSERT_FALSE(cm.containsNote(fakeCollection, fakeNote));
}

TEST(CollectionManagerTest, TestGetNoteList) {
    // setting up the test
    CollectionManager cm;
    std::string collection = "collection";
    std::string note1 = "note1";
    std::string note2 = "note2";
    std::string note3 = "note3";
    cm.createNewCollection(collection);
    cm.createNewNote(collection, note1);
    cm.createNewNote(collection, note2);
    cm.createNewNote(collection, note3);

    // creating a compare set
    std::set<std::string> compareSet;
    compareSet.insert(note1);
    compareSet.insert(note2);
    compareSet.insert(note3);

    // making a loop to compare each entry of returnSet with the respective entry of compareSet, and check if there are
    // differences between them
    auto returnSet = cm.getNoteList(collection);
    bool isDifferent = false;

    auto compareIt = compareSet.begin();         // get begin iterators to start
    auto returnIt = returnSet.begin();
    while(returnIt != returnSet.end()) {
        if (*returnIt != *compareIt)
            isDifferent = true;
        returnIt++;
        compareIt++;
    }
    ASSERT_FALSE(isDifferent);
}

TEST(CollectionManagerTest, TestGetCollectionList) {
    // setting up test
    CollectionManager cm;
    std::string collection1 = "collection1";
    std::string collection2 = "collection2";
    std::string collection3 = "collection3";
    cm.createNewCollection(collection1);
    cm.createNewCollection(collection2);
    cm.createNewCollection(collection3);

    // creating compare set
    std::set<std::string> compareSet;
    compareSet.insert(collection1);
    compareSet.insert(collection2);
    compareSet.insert(collection3);

    // making a loop to compare each entry of returnSet with the respective entry of compareSet, and check if there are
    // differences between them
    auto returnSet = cm.getCollectionList();
    bool isDifferent = false;

    auto compareIt = compareSet.begin();         // get begin iterators to start
    auto returnIt = returnSet.begin();
    while(returnIt != returnSet.end()) {
        if (*returnIt != *compareIt)
            isDifferent = true;
        returnIt++;
        compareIt++;
    }
    ASSERT_FALSE(isDifferent);
}

TEST(CollectionManagerTest, TestGetFavourites) {
    // setting up test
    CollectionManager cm;
    std::string collection = "collection";
    cm.createNewCollection(collection);
    std::string note1 = "note1";
    std::string note2 = "note2";
    cm.createNewNote(collection, note1);
    cm.createNewNote(collection, note2);
    auto ptr1 = cm.getNote(collection, note1);
    auto ptr2 = cm.getNote(collection, note2);
    cm.addToFavourites(ptr1);
    cm.addToFavourites(ptr2);

    // creating a compare set
    std::set<std::string> compareSet;
    compareSet.insert(note1);
    compareSet.insert(note2);

    // making a loop to compare each entry of returnSet with the respective entry of compareSet, and check if there are
    // differences between them
    auto returnSet = cm.getFavourites();
    bool isDifferent = false;

    auto compareIt = compareSet.begin();
    auto returnIt = returnSet.begin();
    while(returnIt != returnSet.end()){
        if(*returnIt != *compareIt)
            isDifferent = true;
        returnIt ++;
        compareIt ++;
    }
    ASSERT_FALSE(isDifferent);
}

TEST(CollectionManagerTest, TestGetNumerOfNotes) {
    // setting up test
    CollectionManager cm;
    std::string collection = "collection";
    cm.createNewCollection(collection);
    std::string note1 = "note1";
    std::string note2 = "note2";
    cm.createNewNote(collection, note1);
    cm.createNewNote(collection, note2);

    ASSERT_EQ(cm.getNumberOfNotes(collection), 2);

    std::string note3 = "note3";
    cm.createNewNote(collection, note3);
    ASSERT_EQ(cm.getNumberOfNotes(collection), 3);
}
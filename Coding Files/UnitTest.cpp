// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
/*
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}
*/

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
    // ASSERT ends operation of this function on fail
    // EXPECT fails but continues

    add_entries(1);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1);
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    add_entries(5);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 5);
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, VectorMaxSizeScaling) {

    std::vector<int> sizes = { 0, 1, 5, 10 };
    for (int size : sizes) {
        // make size 0, 1, 5, then 10
        if (size > 0) add_entries(size - collection->size());
        // collection size is x?
        ASSERT_EQ(collection->size(), size);
        // collection max size >= x?
        ASSERT_GE(collection->max_size(), size);
    }
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, VectorCapacityScaling) {

    std::vector<int> sizes = { 0, 1, 5, 10 };
    for (int size : sizes) {
        // make size 0, 1, 5, then 10
        if (size > 0) add_entries(size - collection->size());
        // collection size is x?
        ASSERT_EQ(collection->size(), size);
        // collection capacity >= x?
        ASSERT_GE(collection->capacity(), size);
    }
}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, VectorResizeIncrease) {

    int size = 5;
    add_entries(size);
    // starting with size?
    ASSERT_EQ(collection->size(), size);
    
    // resize greater
    collection->resize(size + 2);

    // size has increased?
    ASSERT_GT(collection->size(), size);
}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, VectorResizeDecrease) {

    int size = 5;
    add_entries(size);
    // starting with size?
    ASSERT_EQ(collection->size(), size);

    // resize lesser
    collection->resize(size - 2);

    // size has decreased?
    ASSERT_LT(collection->size(), size);
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, VectorResizeToZero) {

    int size = 5;
    add_entries(size);
    // starting with size?
    ASSERT_EQ(collection->size(), size);

    // resize to zero
    collection->resize(size - size);

    // size is zero?
    ASSERT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, VectorClear) {

    int size = 5;
    add_entries(size);
    // starting with size?
    ASSERT_EQ(collection->size(), size);

    // clear
    collection->clear();

    // size is zero?
    ASSERT_EQ(collection->size(), 0);
    // also, for completeness, empty?
    ASSERT_TRUE(collection->empty());
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, VectorEraseAll) {

    int size = 5;
    add_entries(size);
    // starting with size?
    ASSERT_EQ(collection->size(), size);

    // erase all
    collection->erase(collection->begin(), collection->end());

    // size is zero?
    ASSERT_EQ(collection->size(), 0);
    // also, for completeness, empty?
    ASSERT_TRUE(collection->empty());
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, VectorReserve) {

    // get starting values
    auto collectionSize = collection->size();
    auto collectionCapacity = collection->capacity();

    // call reserve
    collection->reserve(10);

    // do test
    ASSERT_EQ(collection->size(), collectionSize);
    ASSERT_GT(collection->capacity(), collectionCapacity);
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, VectorOutOfRangeException) {
    // this is a negative test because we provide invalid data (non-existant index 1 on an empty vector)
    ASSERT_THROW(collection->at(1), std::out_of_range);
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
// TEST 1: PUSH BACK
TEST_F(CollectionTest, VectorPushBack) {

    // starting size is 0?
    ASSERT_EQ(collection->size(), 0);

    // push back element
    int element = 5;
    collection->push_back(element);

    // has the size increased to 1?
    ASSERT_EQ(collection->size(), 1);
    // is the last element correct?
    ASSERT_EQ(collection->back(), element);
}
// TEST 2: RESIZE below zero
TEST_F(CollectionTest, ResizeLessThanZero) {
    ASSERT_THROW(collection->resize(-1), std::length_error);
}

#include "DBFile.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(DBFile, CreatePositive)
{
    const char *tpch_dir = "lineItem.bin";

    const char *dbFileDirectory = "./";
    DBFile h;
    int createHeap = h.Create(tpch_dir, heap, NULL);
    ASSERT_EQ(createHeap, 1);
}

TEST(DBFile, CreateNegative)
{
    const char *tpch_dir = "lineItem.bin";
    const char *dbFileDirectory = "./";
    DBFile h;
    int createHeap = h.Create(tpch_dir, tree, NULL);
    ASSERT_EQ(createHeap, 0);
}


TEST(DBFile, OpenPositive)
{
    const char *tpch_dir = "lineItem.bin";
    DBFile h;
    int createHeap = h.Create(tpch_dir, heap, NULL);
    ASSERT_EQ(createHeap, 1);
    int openFile = h.Open(tpch_dir);
    ASSERT_EQ(openFile, 1);
}

TEST(DBFile, OpenNegative)
{
    const char *tpch_dir = "UnknownFileName";
    const char *dbFileDirectory = "./";
    DBFile h;
    int openFile = h.Open(tpch_dir);
    ASSERT_EQ(openFile, 0);
}

TEST(DBFile, ClosePositive)
{
    const char *tpch_dir = "lineItem.bin";
    DBFile h;
    int openFile = h.Open(tpch_dir);
    ASSERT_EQ(openFile, 1);
    int closeFile = h.Close();
    ASSERT_EQ(closeFile, 1);
}

TEST(DBFile, CloseNegative)
{
    DBFile h;
    int closeFile = h.Close();
    ASSERT_EQ(closeFile, 0);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
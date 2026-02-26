#include "Utils.h"
#include <gtest/gtest.h>
#include <fstream>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

// Helper function to compare two sets
bool areSetsEqual(const std::set<int>& set1, const std::set<int>& set2) {
   // Check if both sets are subsets of each other
    return std::equal(set1.begin(), set1.end(), set2.begin(), set2.end());
}

void printSet(const std::set<std::string>& s) {
    // Print the opening bracket for clarity
    std::cout << "{ ";
    
    // Iterate through the set and print each element
    for (std::string element : s) {
        std::cout << element << " ";
    }

    // Print the closing bracket for clarity
    std::cout << "}" << std::endl;
}

TEST(UtilsTest, areSetsEqual) {
    std::set<int> set1 = {1, 2, 3};
    std::set<int> set2 = {1, 2, 3};
    std::set<int> set3 = {1, 2};
    std::set<int> set4 = {1, 2, 4};

    EXPECT_TRUE(areSetsEqual(set1, set2)) << "set1 and set2 should be equal.";
    EXPECT_FALSE(areSetsEqual(set1, set3)) << "set1 and set3 should not be equal.";
    EXPECT_FALSE(areSetsEqual(set1, set4)) << "set1 and set4 should not be equal.";
}

TEST(UtilsTest, RemoveSpaces) {
    std::string input = "   Hello,   World!   ";
    Utils::removeSpaces(input);
    EXPECT_EQ(input, "Hello, World!");
}

TEST(UtilsTest, is_number) {
    EXPECT_TRUE(Utils::is_number("1"));
    EXPECT_TRUE(Utils::is_number("102"));
    EXPECT_FALSE(Utils::is_number(""));
    EXPECT_FALSE(Utils::is_number("2312f342"));
    EXPECT_FALSE(Utils::is_number("a2312"));
    EXPECT_FALSE(Utils::is_number("2312@"));
}

TEST(UtilsTest, ContainsTab) {
    EXPECT_FALSE(Utils::containsTab("This is a test string.")); // No tab
    EXPECT_TRUE(Utils::containsTab("This\tis a test string.")); // Contains a tab
    EXPECT_TRUE(Utils::containsTab("\tTab at the start."));     // Tab at the beginning
    EXPECT_TRUE(Utils::containsTab("Ends with tab\t"));         // Tab at the end
    EXPECT_FALSE(Utils::containsTab(""));                      // Empty string
}

TEST(UtilsTest, Split) {
    std::string input = "apple,banana,orange";
    auto tokens = Utils::split(input, ',');
    EXPECT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[0], "apple");
    EXPECT_EQ(tokens[1], "banana");
    EXPECT_EQ(tokens[2], "orange");
}

TEST(UtilsTest, intersectionSize) {
    // Define two sets
    std::set<int> set1 = {1, 2, 3};
    std::set<int> set2 = {1, 3, 4};

    // Call the intersectionSize method
    size_t size = Utils::intersectionSize(set1, set2);

    // Assert that the size of the intersection is correct
    ASSERT_EQ(size, 2) << "The intersection size should be 2.";
}

TEST(UtilsTest, GetViewers) {
    string path = "/mytest/data/test.txt";
    std::map<int, std::set<int>> movieToUsers = Utils::GetViewers(path);

    // Expected output for movie "105"
    std::set<int> output1 = movieToUsers[105];
    std::set<int> expectedSet1 = { 2, 3, 4, 5, 7, 8, 9, 10 };

    // Expected output for movie "104"
    std::set<int> output2 = movieToUsers[104];
    std::set<int> expectedSet2 = { 2, 3, 6, 8 };

    // Expected output for movie "3"
    std::set<int> output3 = movieToUsers[3];
    std::set<int> expectedSet3 = {};

    // Assert that there is no difference
    EXPECT_TRUE(areSetsEqual(output1, expectedSet1)) << "The difference set is not empty.";
    EXPECT_TRUE(areSetsEqual(output2, expectedSet2)) << "The difference set is not empty.";
    EXPECT_TRUE(areSetsEqual(output3, expectedSet3)) << "The difference set is not empty.";

}

TEST(UtilsTest, GetMovies) {
    // Call Utils::GetMovies to process the file
    string path = "/mytest/data/test.txt";
    std::map<int, std::set<int>> userToMovies = Utils::GetMovies(path);

    // Expected output for user "44"
    std::set<int> output1 = userToMovies[44];
    std::set<int> expectedSet1 = {};

    // Expected output for user "2"
    std::set<int> output2 = userToMovies[2];
    std::set<int> expectedSet2 = { 101, 102, 104, 105, 106};

    // Expected output for user "1"
    std::set<int> output3 = userToMovies[1];
    std::set<int> expectedSet3 = {100, 101, 102, 103};

     // Assert that there is no difference
    EXPECT_TRUE(areSetsEqual(output1, expectedSet1)) << "The difference set is not empty.";
    EXPECT_TRUE(areSetsEqual(output2, expectedSet2)) << "The difference set is not empty.";
    EXPECT_TRUE(areSetsEqual(output3, expectedSet3)) << "The difference set is not empty.";
}

TEST(UtilsTest, GetCommonMoviesSize) {
    // Define a map representing users and their watched movies
    std::map<int, std::set<int>> userToMovies = {
        {1, {101, 102, 103}},
        {2, {101, 102, 104}},
        {3, {104}}
    };

    // Call the GetCommonMoviesSize method
    size_t commonMovies1 = Utils::GetCommonMoviesSize(userToMovies, 1, 2);
    ASSERT_EQ(commonMovies1, 2) << "The common movies size should be 2.";

    size_t commonMovies2 = Utils::GetCommonMoviesSize(userToMovies, 1, 3);
    ASSERT_EQ(commonMovies2, 0) << "The common movies size should be 0.";

    size_t commonMovies3 = Utils::GetCommonMoviesSize(userToMovies, 2, 3);
    ASSERT_EQ(commonMovies3, 1) << "The common movies size should be 1.";
}


TEST(UtilsTest, GetSimiliarityGrade) {
    std::map<int, std::set<int>> userToMovies = {
        {1, {100, 101, 102, 103}},
        {2, {101, 102, 104, 105, 106}},
        {3, {100, 104, 105, 107, 108}},
        {4, {101, 105, 106, 107, 108}},
        {5, {100, 102, 103, 105, 108, 111}},
        {6, {100, 103, 104, 110, 111, 112, 113}},
        {7, {102, 105, 106, 107, 108, 109, 111, 114}},
        {8, {101, 104, 105, 106, 109, 111, 114}},
        {9, {100, 103, 105, 107, 112, 113, 115}},
        {10, {100, 102, 105, 106, 107, 109, 110, 116}}
    };

    std::map<int, size_t> similarity = Utils::GetSimiliarityGrade(1, userToMovies);

    // Since all users have the same set of movies, the similarity should be equal to the size of the set
    EXPECT_EQ(similarity[2], 2) << "Similarity with user 2 should be 2 (identical movies).";
    EXPECT_EQ(similarity[3], 1) << "Similarity with user 3 should be 3 (identical movies).";
    EXPECT_EQ(similarity[6], 2) << "Similarity with user 4 should be 0 (identical movies).";
    EXPECT_EQ(similarity[8], 1) << "Similarity with user 5 should be 0 (identical movies).";
}

TEST(UtilsTest, watchedInMovie) {
    std::map<int, std::set<int>> movieToUsers = {
        {100, {1, 3, 5, 6, 9, 10}},
        {101, {1, 2, 4, 8}},
        {102, {1, 2, 5, 7, 10}},
        {103, {1, 5, 6, 9}},
        {104, {2, 3, 6, 8}},
        {105, {2, 3, 4, 5, 6, 7, 8, 9, 10}},
        {106, {2, 4, 7, 8, 10}},
        {107, {3, 4, 7, 9, 10}},
        {108, {3, 4, 5, 7}},
        {109, {7, 8, 10}},
        {110, {6, 10}},
        {111, {5 ,6, 7, 8}},
        {112, {6 ,9}},
        {113, {6, 9}},
        {114, {7 ,8}},
        {115, {9}},
        {116, {10}}
    };

    // Call the watchedInMovie method
    std::set<int> users1 = Utils::watchedInMovie(101, movieToUsers);
    std::set<int> expected1 = {1, 2, 4, 8};

    std::set<int> users2 = Utils::watchedInMovie(102, movieToUsers);
    std::set<int> expected2 = {1, 2, 5, 7, 10};

    std::set<int> users3 = Utils::watchedInMovie(104, movieToUsers);
    std::set<int> expected3 = {2, 3, 6, 8};

    // Assertions
    EXPECT_EQ(users1, expected1) << "The users who watched movie 101 are incorrect.";
    EXPECT_EQ(users2, expected2) << "The users who watched movie 102 are incorrect.";
    EXPECT_EQ(users3, expected3) << "The users who watched movie 104 should be empty.";
}

TEST(UtilsTest, GetRelevanceGrades) {
    // Mock movieToUsers and userToMovies maps
    // std::map<int, std::set<int>> movieToUsers = {
    //     {100, {1, 3, 5, 6, 9, 10}},
    //     {101, {1, 2, 4, 8}},
    //     {102, {1, 2, 5, 7, 10}},
    //     {103, {1, 5, 6, 9}},
    //     {104, {2, 3, 6, 8}},
    //     {105, {2, 3, 4, 5, 7, 8, 9, 10}},
    //     {106, {2, 4, 7, 8, 10}},
    //     {107, {3, 4, 7, 9, 10}},
    //     {108, {3, 4, 5, 7}},
    //     {109, {7, 8, 10}},
    //     {110, {6, 10}},
    //     {111, {5 ,6, 7, 8}},
    //     {112, {6 ,9}},
    //     {113, {6, 9}},
    //     {114, {7 ,8}},
    //     {115, {9}},
    //     {116, {10}}
    // };

    std::map<int, std::set<int>> movieToUsers = {
        {101, {1, 2}},
        {102, {1, 2}},
        {103, {1, 3}},
        {104, {3}},
        {105, {2}}
    };

    // std::map<int, std::set<int>> userToMovies = {
    //     {1, {100, 101, 102, 103}},
    //     {2, {101, 102, 104, 105, 106}},
    //     {3, {100, 104, 105, 107, 108}},
    //     {4, {101, 105, 106, 107, 108}},
    //     {5, {100, 102, 103, 105, 108, 111}},
    //     {6, {100, 103, 104, 110, 111, 112, 113}},
    //     {7, {102, 105, 106, 107, 108, 109, 111, 114}},
    //     {8, {101, 104, 105, 106, 109, 111, 114}},
    //     {9, {100, 103, 105, 107, 112, 113, 115}},
    //     {10, {100, 102, 105, 106, 107, 109, 110, 116}}
    // };

     std::map<int, std::set<int>> userToMovies = {
        {1, {101, 102, 103}},
        {2, {101, 102, 105}},
        {3, {103, 104}}
    };

    // Call GetRelevanceGrades
    std::map<int, size_t> relevanceGrades = Utils::GetRelevanceGrades(3, 105, movieToUsers, userToMovies);

    // Expected results
    EXPECT_EQ(relevanceGrades[101], 0) << "Relevance grade for movie 101 is incorrect.";
    EXPECT_EQ(relevanceGrades[102], 0) << "Relevance grade for movie 102 is incorrect.";
    EXPECT_EQ(relevanceGrades[103], 0) << "Relevance grade for movie 103 is incorrect.";
    EXPECT_EQ(relevanceGrades[104], 0) << "Relevance grade for movie 104 is incorrect.";
    EXPECT_EQ(relevanceGrades[105], 0) << "Relevance grade for movie 105 is incorrect.";
}

// TEST(UtilsTest, cmpPairByFirstValueForAcsendingSort) {
//     pair<int, size_t> p1(1, 2);
//     pair<int, size_t> p2(2, 3);
//     pair<int, size_t> p3(4, 1);
//     pair<int, size_t> p4(1, 1);

//     EXPECT_TRUE(Utils::cmpPairByFirstValueForAcsendingSort(p1, p2));
//     EXPECT_FALSE(Utils::cmpPairByFirstValueForAcsendingSort(p2, p1));
//     EXPECT_TRUE(Utils::cmpPairByFirstValueForAcsendingSort(p1, p3));
//     EXPECT_FALSE(Utils::cmpPairByFirstValueForAcsendingSort(p4, p1));
// }

// TEST(UtilsTest, cmpPairBySecondValueForDescendingSort) {
//     pair<int, size_t> p1(1, 2);
//     pair<int, size_t> p2(2, 3);
//     pair<int, size_t> p3(4, 1);
//     pair<int, size_t> p4(1, 1);

//     EXPECT_FALSE(Utils::cmpPairBySecondValueForDescendingSort(p1, p2));
//     EXPECT_TRUE(Utils::cmpPairBySecondValueForDescendingSort(p2, p1));
//     EXPECT_TRUE(Utils::cmpPairBySecondValueForDescendingSort(p1, p3));
//     EXPECT_FALSE(Utils::cmpPairBySecondValueForDescendingSort(p1, p4));
// }

TEST(UtilsTest, sortMapByValue) {
    std::map<int, size_t> myMap = {
        {101, 0},
        {102, 0},
        {103, 0},
        {104, 0},
        {105, 0}
    };

    // Sort
    std::vector<std::pair<int, size_t>> sortedVec = Utils::sortMapByValue(myMap);

    EXPECT_EQ(sortedVec[0].first, 102);
    EXPECT_EQ(sortedVec[1].first, 104);
    EXPECT_EQ(sortedVec[2].first, 101);
    EXPECT_EQ(sortedVec[3].first, 103);
    EXPECT_EQ(sortedVec[4].first, 106);
}
TEST(UtilsTest, ClearFile) {
    const std::string testFile = "test_clear.txt";

    // Create a test file with some content
    std::ofstream outFile(testFile);
    outFile << "Temporary content";
    outFile.close();

    // Clear the file
    Utils::clearFile(testFile);

    // Verify the file is empty
    std::ifstream inFile(testFile);
    ASSERT_TRUE(inFile.is_open());
    std::string content;
    ASSERT_FALSE(std::getline(inFile, content)); // No content should be read
    inFile.close();

    // Clean up the test file
    std::remove(testFile.c_str());
}

TEST(UtilsTest, GetFirstWord) {
    std::string command1 = "POST 101 102 103";
    std::string command2 = "PATCH 105 106";
    std::string command3 = "DELETE";

    EXPECT_EQ(Utils::getFirstWord(command1), "POST");
    EXPECT_EQ(Utils::getFirstWord(command2), "PATCH");
    EXPECT_EQ(Utils::getFirstWord(command3), "DELETE");
}

TEST(UtilsTest, convertVectorToString) {
    std::vector<std::pair<int, size_t>> sortedVec = {
        {101, 5}, {102, 3}, {103, 2}, {104, 1}
    };

    size_t N = 3; // Number of elements to include in the string
    std::string result = Utils::convertVectorToString(sortedVec, N);

    EXPECT_EQ(result, "101 102 103");
}

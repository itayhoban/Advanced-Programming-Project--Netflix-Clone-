#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include <fstream>

// Declare the main function for testing
int main();

// Helper function to run the main function with redirected input/output
void runMainWithStreams(std::istream& simulatedInput, std::ostream& capturedOutput) {
    // Backup original streams
    std::streambuf* cinBackup = std::cin.rdbuf();
    std::streambuf* coutBackup = std::cout.rdbuf();

    // Redirect streams
    std::cin.rdbuf(simulatedInput.rdbuf());
    std::cout.rdbuf(capturedOutput.rdbuf());

    // Call the global main function
    main();

    // Restore the original streams
    std::cin.rdbuf(cinBackup);
    std::cout.rdbuf(coutBackup);
}

// Test case for the main function
TEST(MainTest, ValidInputSequence) {
    // Simulate user input
    std::stringstream simulatedInput("add 1 101\nrecommend 1 101\n");
    std::stringstream capturedOutput;

    // Run the main function with simulated input/output
    runMainWithStreams(simulatedInput, capturedOutput);

    // Capture and validate the output
    std::string output = capturedOutput.str();
    EXPECT_NE(output.find("What would you like to do next?"), std::string::npos);
}

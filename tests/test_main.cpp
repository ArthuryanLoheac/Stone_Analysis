#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "cypher.hpp"
#include "const.hpp"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// Test cryptMessage
Test(cryptMessage, basic_message)
{
    const char *message = "HelloWorld";
    std::string encrypted = cryptMessage(message);
    cr_assert_neq(encrypted, message, "The encrypted message should not match the original message.");
    std::string decrypted = decryptMessage(encrypted);
    cr_assert_eq(decrypted, message, "The decrypted message should match the original message.");
}

Test(cryptMessage, empty_message)
{
    const char *message = "";
    std::string encrypted = cryptMessage(message);
    cr_assert_eq(encrypted, "", "The encrypted message of an empty string should also be empty.");
    std::string decrypted = decryptMessage(encrypted);
    cr_assert_eq(decrypted, "", "The decrypted message of an empty string should also be empty.");
}

Test(cryptMessage, long_message)
{
    const char *message = "ThisIsALongMessageWithMoreThanTenCharacters";
    std::string encrypted = cryptMessage(message);
    cr_assert_neq(encrypted, message, "The encrypted message should not match the original message.");
    std::string decrypted = decryptMessage(encrypted);
    cr_assert_eq(decrypted, message, "The decrypted message should match the original message.");
}

// Test cypher and decypher
Test(cypher, basic_usage, .init=redirect_all_std)
{
    const char *inputFile = "tests/input.wav";
    const char *outputFile = "tests/output.wav";
    const char *message = "HelloWorld";

    // Create a dummy input file
    std::ofstream input(inputFile, std::ios::binary);
    char header[WAV_HEADER_SIZE] = {0};
    input.write(header, WAV_HEADER_SIZE);
    std::vector<char> audioData(1000, 0);
    input.write(audioData.data(), audioData.size());
    input.close();

    // Test cypher
    cypher(inputFile, outputFile, message);

    // Test decypher
    decypher(outputFile);
    cr_assert_stdout_eq_str("HelloWorld\n", "The hidden message should be correctly retrieved.");
}

Test(cypher, long_message, .init=redirect_all_std)
{
    const char *inputFile = "tests/input_long.wav";
    const char *outputFile = "tests/output_long.wav";
    const char *message = "ThisIsALongMessageWithMoreThanTenCharacters";

    // Create a dummy input file
    std::ofstream input(inputFile, std::ios::binary);
    char header[WAV_HEADER_SIZE] = {0};
    input.write(header, WAV_HEADER_SIZE);
    std::vector<char> audioData(2000, 0);
    input.write(audioData.data(), audioData.size());
    input.close();

    // Test cypher
    cypher(inputFile, outputFile, message);

    // Test decypher
    decypher(outputFile);
    cr_assert_stdout_eq_str("ThisIsALongMessageWithMoreThanTenCharacters\n", "The hidden message should be correctly retrieved.");
}

Test(cypher, message_too_long)
{
    const char *inputFile = "tests/input_too_long.wav";
    const char *outputFile = "tests/output_too_long.wav";
    const char *message = "ThisMessageIsWayTooLongToFitInTheAudioFile";

    // Create a dummy input file
    std::ofstream input(inputFile, std::ios::binary);
    char header[WAV_HEADER_SIZE] = {0};
    input.write(header, WAV_HEADER_SIZE);
    std::vector<char> audioData(60, 0); // Small audio data
    input.write(audioData.data(), audioData.size());
    input.close();

    // Test cypher
    cr_assert_throw(cypher(inputFile, outputFile, message), std::runtime_error, "The message is too long for the audio file.");
}

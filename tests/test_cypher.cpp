#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "cypher.hpp"

Test(cypher, invalid_input_file)
{
    const char *inputFile = "tests/invalid.wav";
    const char *outputFile = "tests/output.wav";
    const char *message = "Hello";

    cr_assert_throw(cypher(inputFile, outputFile, message), std::runtime_error, "Un fichier d'entrée invalide doit lever une exception.");
}

Test(decypher, invalid_input_file)
{
    const char *inputFile = "tests/invalid.wav";

    cr_assert_throw(decypher(inputFile), std::runtime_error, "Un fichier d'entrée invalide doit lever une exception.");
}

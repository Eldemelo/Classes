#include "mbstrings.h"
#include <stdio.h>

/* mbslen - multi-byte string length
 * - Description: returns the number of UTF-8 code points ("characters")
 * in a multibyte string. If the argument is NULL or an invalid UTF-8
 * string is passed, returns -1.
 *
 * - Arguments: A pointer to a character array (`bytes`), consisting of UTF-8
 * variable-length encoded multibyte code points.
 *
 * - Return: returns the actual number of UTF-8 code points in `src`. If an
 * invalid sequence of bytes is encountered, return -1.
 *
 * - Hints:
 * UTF-8 characters are encoded in 1 to 4 bytes. The number of leading 1s in the
 * highest order byte indicates the length (in bytes) of the character. For
 * example, a character with the encoding 1111.... is 4 bytes long, a character
 * with the encoding 1110.... is 3 bytes long, and a character with the encoding
 * 1100.... is 2 bytes long. Single-byte UTF-8 characters were designed to be
 * compatible with ASCII. As such, the first bit of a 1-byte UTF-8 character is
 * 0.......
 *
 * You will need bitwise operations for this part of the assignment!
 */
size_t mbslen(const char* bytes) {
    if (bytes == NULL) {
        return (size_t)-1; // Return -1 for NULL input
    }

    size_t len = 0;

    // While there are still bytes to read
    while (*bytes) {
        unsigned char byte = (unsigned char)*bytes;
        int char_len = 0;

        // Determine the length of the character based on the leading byte
        if ((byte & 0x80) == 0) {
            char_len = 1;  // ASCII character (0xxxxxxx)
        } else if ((byte & 0xE0) == 0xC0) {
            char_len = 2;  // 2-byte character (110xxxxx)
        } else if ((byte & 0xF0) == 0xE0) {
            char_len = 3;  // 3-byte character (1110xxxx)
        } else if ((byte & 0xF8) == 0xF0) {
            char_len = 4;  // 4-byte character (11110xxx)
        } else {
            return (size_t)-1;  // Invalid UTF-8 leading byte
        }

        // Validate the continuation bytes (should start with 10xxxxxx)
        for (int i = 1; i < char_len; i++) {
            if ((bytes[i] & 0xC0) != 0x80) {
                return (size_t)-1;  // Invalid UTF-8 sequence
            }
        }

        bytes += char_len; // Move to the next character
        len++;             // Increment the character count
    }

    return len; // Return the total character count
}
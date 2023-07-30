#ifndef _PRINTF_H_
#define _PRINTF_H_

#include <stdarg.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef printf
#define printf    usdk_printf
#endif
#ifndef sprintf
#define sprintf   usdk_sprintf
#endif
#ifndef snprintf
#define snprintf  usdk_snprintf
#endif
#ifndef vsnprintf
#define vsnprintf usdk_vsnprintf
#endif
#ifndef vprintf
#define vprintf   usdk_vprintf
#endif

/**
 * Output a character to a custom device like UART, used by the printf() function
 * This function is declared here only. You have to write your custom implementation somewhere
 * \param character Character to output
 */
void usdk_putchar(char character);

/**
 * Tiny printf implementation
 * You have to implement _putchar if you use printf()
 * To avoid conflicts with the regular printf() API it is overridden by macro defines
 * and internal underscore-appended functions like printf_() are used
 * \param format A string that specifies the format of the output
 * \return The number of characters that are written into the array, not counting the terminating null character
 */
int usdk_printf(const char* format, ...);
#define usdk_println(fmt, ...) usdk_printf(fmt "\n", ##__VA_ARGS__)

/**
 * Tiny sprintf implementation
 * Due to security reasons (buffer overflow) YOU SHOULD CONSIDER USING (V)SNPRINTF INSTEAD!
 * \param buffer A pointer to the buffer where to store the formatted string. MUST be big enough to store the output!
 * \param format A string that specifies the format of the output
 * \return The number of characters that are WRITTEN into the buffer, not counting the terminating null character
 */
int usdk_sprintf(char* buffer, const char* format, ...);

/**
 * Tiny snprintf/vsnprintf implementation
 * \param buffer A pointer to the buffer where to store the formatted string
 * \param count The maximum number of characters to store in the buffer, including a terminating null character
 * \param format A string that specifies the format of the output
 * \param va A value identifying a variable arguments list
 * \return The number of characters that COULD have been written into the buffer, not counting the terminating
 *         null character. A value equal or larger than count indicates truncation. Only when the returned value
 *         is non-negative and less than count, the string has been completely written.
 */
int usdk_snprintf(char* buffer, size_t count, const char* format, ...);
int usdk_vsnprintf(char* buffer, size_t count, const char* format, va_list va);

/**
 * Tiny vprintf implementation
 * \param format A string that specifies the format of the output
 * \param va A value identifying a variable arguments list
 * \return The number of characters that are WRITTEN into the buffer, not counting the terminating null character
 */
int usdk_vprintf(const char* format, va_list va);

/**
 * printf with output function
 * You may use this as dynamic alternative to printf() with its fixed _putchar() output
 * \param out An output function which takes one character and an argument pointer
 * \param arg An argument pointer for user data passed to output function
 * \param format A string that specifies the format of the output
 * \return The number of characters that are sent to the output function, not counting the terminating null character
 */
int usdk_fctprintf(void (*out)(char character, void* arg), void* arg, const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif  // _PRINTF_H_

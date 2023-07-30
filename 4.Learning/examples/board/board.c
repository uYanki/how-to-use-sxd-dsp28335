#include "board.h"

#ifdef CONFIG_STDIO_PRINTF_TXCHAR

int fputc(int ch, register FILE *fp)
{
    CONFIG_STDIO_PRINTF_TXCHAR(ch);
    return ch;
}

// 不重定向 fputs 将会导致 printf 输出格式不完整
int fputs(const char *ptr, register FILE *fp)
{
    u8 *src = (u8 *) ptr;
    while (*src) { CONFIG_STDIO_PRINTF_TXCHAR(*src++); }
    return (int) (src - (u8 *) ptr);
}

int putc(int ch, register FILE *fp)
{
    CONFIG_STDIO_PRINTF_TXCHAR(ch);
    return ch;
}

int putchar(int ch)
{
    CONFIG_STDIO_PRINTF_TXCHAR(ch);
    return ch;
}

#endif  // CONFIG_STDIO_PRINTF_TXCHAR

#ifdef CONFIG_USDK_PRINTF_TXCHAR

void usdk_putchar(char ch)
{
    CONFIG_USDK_PRINTF_TXCHAR(ch);
}

#endif  // CONFIG_USDK_PRINTF_TXCHAR

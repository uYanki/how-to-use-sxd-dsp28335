#ifndef __USDK_CONF_H__
#define __USDK_CONF_H__

#define CONFIG_USING_STDIO_PRINTF 1
#if CONFIG_USING_STDIO_PRINTF
#define CONFIG_STDIO_PRINTF_TXCHAR(ch) SCIB_TxChar(ch)
#define println(fmt, ...)              printf(fmt "\n", ##__VA_ARGS__)
#endif

#define CONFIG_USING_USDK_PRINTF 0
#if CONFIG_USING_USDK_PRINTF
#define CONFIG_USDK_PRINTF_TXCHAR(ch) SCIB_TxChar(ch)
#endif

#define CONFIG_DEBUG_PRINTF printf

#endif

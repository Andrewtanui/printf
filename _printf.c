#include <stdio.h>
#include <stdarg.h>

int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    char buffer[1024];
    char *pbuf = buffer;

    va_start(args, format);

    for (; *format != '\0'; format++) {
        if (*format != '%') {
            // copy regular characters to buffer
            *pbuf++ = *format;
            count++;
            continue;
        }

        format++; // skip '%'

        switch (*format) {
            case 'c':
                // print a character
                *pbuf++ = va_arg(args, int);
                count++;
                break;
            case 's': {
                // print a string
                const char *str = va_arg(args, const char *);
                while (*str != '\0') {
                    *pbuf++ = *str++;
                    count++;
                }
                break;
            }
            case '%':
                // print a '%' character
                *pbuf++ = '%';
                count++;
                break;
            default:
                // unsupported conversion specifier
                *pbuf++ = '%';
                *pbuf++ = *format;
                count += 2;
                break;
        }
    }

    va_end(args);

    // null-terminate the buffer and print to stdout
    *pbuf = '\0';
    printf("%s", buffer);

    return count;
}


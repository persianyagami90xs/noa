/*-
 * Copyright (c) 2010 The Noa Project, http://noaproject.org/
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <assert.h>
#include <kernel.h>
#include <stdarg.h>

unsigned int
log2ceil(unsigned long i)
{
	unsigned int l;

	l = log2floor(i);
	if (i > (1UL << l))
		l++;
	return (l);
}

unsigned int
log2floor(unsigned long i)
{
	unsigned int l = 0, s;

	for (s = sizeof i * 4; ; s /= 2) {
		if (i >= 1UL << s) {
			i >>= s;
			l += s;
		}
		if (s == 0)
			break;
	}
	return (l);
}

static void
puts(const char *str)
{

	while (*str != '\0')
		putchar(*str++);
}

void
printf(const char *restrict format, ...)
{
	va_list args;
	const char *str;
	int state = 0;
	char c;

	va_start(args, format);
	for (; *format != '\0'; format++) {
		if (state == 0) {
			if (*format == '%')
				state = 1;
			else
				putchar(*format);
		} else {
			switch (*format) {
			case '%':
				putchar('%');
				state = 0;
				break;
			case 'c':
				c = va_arg(args, char);
				putchar(c);
				state = 0;
				break;
			case 's':
				str = va_arg(args, const char *);
				puts(str);
				state = 0;
				break;
			default:
				assert(0);
			}
		}
	}
	va_end(args);
}

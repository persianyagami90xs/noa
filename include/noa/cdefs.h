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

#ifndef _NOA_CDEFS_H_
#define	_NOA_CDEFS_H_

#ifndef _KERNEL
#ifdef __cplusplus
#define	__BEGIN_DECLS	extern "C" {
#define	__END_DECLS	}
#else
#define	__BEGIN_DECLS
#define	__END_DECLS
#endif
#endif

#define	__unused		__attribute__((unused))
#define	__aligned_max		__attribute__((aligned))

#define	__containerof(p, type, member) \
	(struct type *)((char *)(p) - (char *)((const struct type *)0)->member)

#define	__symbol_alias(from, to) \
	extern __typeof(from) to __attribute__((alias(#from)))

#define	__howmany(a, b)		(((a) + (b) - 1) / (b))
#define	__roundup(a, b)		(__howmany((a), (b)) * (b))

#define	__CTASSERT(expr)	___CTASSERT(expr, __LINE__)
#define	___CTASSERT(expr, line)	____CTASSERT(expr, line)
#define	____CTASSERT(expr, line) \
	typedef char __ctassert_## line[(expr) ? 1 : -1]

#define	__ABI_STRUCT(name, size, contents) \
	struct name {					\
		union {					\
			char __pad[(size)];		\
			struct contents;		\
		};					\
	} __aligned_max;				\
	__CTASSERT(sizeof(struct name) == (size));

#endif /* !_NOA_CDEFS_H_ */

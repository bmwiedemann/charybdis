/*
 * Copyright (c) 2012 William Pitcock <nenolod@dereferenced.org>.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice is present in all copies.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __CAPABILITY_H__
#define __CAPABILITY_H__

#include "stdinc.h"
#include "rb_dictionary.h"

struct CapabilityIndex {
	const char *name;
	rb_dictionary *cap_dict;
	unsigned int highest_bit;
	rb_dlink_node node;
};

#define CAP_ORPHANED	0x1
#define CAP_REQUIRED	0x2

struct CapabilityEntry {
	const char *cap;
	unsigned int value;
	unsigned int flags;
	void *ownerdata;
};

extern struct CapabilityEntry *capability_find(struct CapabilityIndex *idx, const char *cap);
extern unsigned int capability_get(struct CapabilityIndex *idx, const char *cap, void **ownerdata);
extern unsigned int capability_put(struct CapabilityIndex *idx, const char *cap, void *ownerdata);
extern unsigned int capability_put_anonymous(struct CapabilityIndex *idx);
extern void capability_orphan(struct CapabilityIndex *idx, const char *cap);
extern void capability_require(struct CapabilityIndex *idx, const char *cap);

extern struct CapabilityIndex *capability_index_create(const char *name);
extern void capability_index_destroy(struct CapabilityIndex *);
extern const char *capability_index_list(struct CapabilityIndex *, unsigned int capability_mask);
extern unsigned int capability_index_mask(struct CapabilityIndex *);
extern unsigned int capability_index_get_required(struct CapabilityIndex *);
extern void capability_index_stats(void (*cb)(const char *line, void *privdata), void *privdata);

#endif

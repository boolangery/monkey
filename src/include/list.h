/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/* Monkey HTTP Daemon
 * ------------------
 * Copyright (C) 2010, Jonathan Gonzalez V. <zeus@gnu.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef   	MK_LIST_H_
#define   	MK_LIST_H_

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#define container_of(ptr, type, member) ({                      \
      const typeof( ((type *)0)->member ) *__mptr = (ptr);      \
      (type *)( (char *)__mptr - offsetof(type,member) );})


struct mk_list
{
    struct mk_list *prev, *next;
};

static inline void mk_list_init(struct mk_list *list)
{
    list->next = list;
    list->prev = list;
}

static inline void __mk_list_add(struct mk_list *new, struct mk_list *prev,
                                 struct mk_list *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

static inline void mk_list_add(struct mk_list *new, struct mk_list *head)
{
    __mk_list_add(new, head->prev, head);
}

static inline void __mk_list_del(struct mk_list *prev, struct mk_list *next)
{
    prev->next = next;
    next->prev = prev;
}

static inline void mk_list_del(struct mk_list *entry)
{
    __mk_list_del(entry->prev, entry->next);
}

#define mk_list_foreach(curr, head) for( curr = (head)->next; curr != (head); curr = curr->next )

#define mk_list_entry( ptr, type, member ) container_of( ptr, type, member )


#endif /* !MK_LIST_H_ */

/*
 * Very simple prng to allow for randomized tests with reproducable
 * results.
 *
 * Copyright (C) 2012 by Open Source Routing.
 * Copyright (C) 2012 by Internet Systems Consortium, Inc. ("ISC")
 *
 * This file is part of Quagga
 *
 * Quagga is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * Quagga is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Quagga; see the file COPYING.  If not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "prng.h"

struct prng
{
  uint32_t state;
};

struct prng*
prng_new(uint32_t seed)
{
  struct prng *rv = calloc(sizeof(*rv), 1);
  assert(rv);

  rv->state = seed;

  return rv;
}

unsigned int
prng_rand(struct prng *prng)
{
  prng->state *= 1664525;
  prng->state += 1013904223;

  return prng->state;
}

const char *
prng_fuzz(struct prng *prng,
          const char *string,
          const char *charset,
          unsigned int operations)
{
  static char buf[256];
  unsigned int charset_len;
  unsigned int i;
  unsigned int offset;
  unsigned int op;
  unsigned int character;

  assert(strlen(string) < sizeof(buf));

  strncpy(buf, string, sizeof(buf));
  charset_len = strlen(charset);

  for (i = 0; i < operations; i++)
    {
      offset = prng_rand(prng) % strlen(buf);
      op = prng_rand(prng) % 3;

      switch (op)
        {
        case 0:
          /* replace */
          character = prng_rand(prng) % charset_len;
          buf[offset] = charset[character];
          break;
        case 1:
          /* remove */
          memmove(buf + offset, buf + offset + 1, strlen(buf) - offset);
          break;
        case 2:
          /* insert */
          assert(strlen(buf) + 1 < sizeof(buf));

          memmove(buf + offset + 1, buf + offset, strlen(buf) + 1 - offset);
          character = prng_rand(prng) % charset_len;
          buf[offset] = charset[character];
          break;
        }
    }
  return buf;
}

void
prng_free(struct prng *prng)
{
  free(prng);
}

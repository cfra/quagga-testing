/*
 * Very simple prng for tests which yields reproducable results.
 *
 * Copyright (C) 2013 Christian Franke <nobody@nowhere.ws>
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

#include "prng.h"

struct prng
{
  unsigned long long state1;
  unsigned long long state2;
};

static char
prng_bit(struct prng *prng)
{
  prng->state1 *= 2416;
  prng->state1 += 374441;
  prng->state1 %= 1771875;

  if (prng->state1 % 2)
    {
      prng->state2 *= 84589;
      prng->state2 += 45989;
      prng->state2 %= 217728;
    }

  return prng->state2 % 2;
}

struct prng*
prng_new(unsigned long long seed)
{
  struct prng *rv = calloc(sizeof(*rv), 1);
  assert(rv);

  rv->state1 = rv->state2 = seed;

  return rv;
}

unsigned int
prng_rand(struct prng *prng)
{
  unsigned int i, rv = 0;

  for (i = 0; i < 32; i++)
    {
      rv |= prng_bit(prng);
      rv <<= 1;
    }
  return rv;
}

void 
prng_free(struct prng *prng)
{
  free(prng);
}

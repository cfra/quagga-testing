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
#ifndef _PRNG_H
#define _PRNG_H

struct prng;

struct prng* prng_new(unsigned long long seed);
unsigned int prng_rand(struct prng*);
void prng_free(struct prng *);

#endif

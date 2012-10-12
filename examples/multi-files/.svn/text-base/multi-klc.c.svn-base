/*
 * ---------- header ----------------------------------------------------------
 *
 * project       bpt
 *
 * license       BSD
 *
 * file          /home/mycure/bpt/examples/multi-files/multi-klc.c
 *
 * created       julien quintard   [thu jul 12 17:00:15 2007]
 * updated       julien quintard   [sat jul 14 05:20:24 2007]
 */

#include "multi.h"

/*
 * functions in relation with bpt: load/unload/interval
 */

void			klc_load(t_bpt(klc)			*bpt,
				 t_bpt_imm(klc)			*node,
				 t_bpt_node(klc)		addr)
{
  node->addr = addr;
  node->buf = (void *)addr;

  /*
   * do nothing because we are in main memory
   */
}

void			klc_unload(t_bpt(klc)			*bpt,
				   t_bpt_imm(klc)		*node)
{
  /*
   * do nothing, again...
   */
}

int			klc_addrcmp(t_bpt(klc)			*bpt,
				    t_bpt_addr(klc)		addr1,
				    t_bpt_addr(klc)		addr2)
{
  if (addr1 < addr2)
    return (-1);
  else
    return (addr1 > addr2);
}

int			klc_keycmp(t_bpt(klc)			*bpt,
				   t_bpt_key(klc)		key1,
				   t_bpt_key(klc)		key2)
{
  if (key1 < key2)
    return (-1);
  else
    return (key1 > key2);
}

int			klc_valcmp(t_bpt(klc)			*bpt,
				   t_bpt_value(klc)		val1,
				   t_bpt_value(klc)		val2)
{
  if (val1 < val2)
    return (-1);
  else
    return (val1 > val2);
}

/*
 * functions
 */

void			klc_make_unused(t_bpt_unused(klc)	*unused,
					t_bpt_addr(klc)		*array,
					t_bpt_uni(klc)		size,
					t_bpt_uni(klc)		alloc)
{
  t_bpt_uni(klc)	i;

  unused->array = array;
  unused->index = alloc - 1;

  for (i = 0; i < size; i++)
    unused->array[i] = (t_bpt_addr(klc))KLC_UNUSED_ADDR;

  for (i = 0; i < alloc; i++)
    unused->array[i] = (t_bpt_addr(klc))malloc(KLC_NODESZ);
}

void			klc_clean_unused(t_bpt_unused(klc)	*unused,
					 t_bpt_uni(klc)		size)
{
  t_bpt_uni(klc)	i;

  for (i = 0; i < size; i++)
    if (unused->array[i] != KLC_UNUSED_ADDR)
      free((void *)unused->array[i]);
}

void			klc_init(t_bpt(klc)			*bpt)
{
  t_bpt_uni(klc)	alloc = BPT_INIT_ALLOC();
  t_bpt_uni(klc)	size = BPT_INIT_SIZE();
  t_bpt_addr(klc)	array[size];
  t_bpt_unused(klc)	unused;

  klc_make_unused(&unused, array, size, alloc);

  if (bpt_init(klc, bpt, KLC_NODESZ, KLC_UNUSED_ADDR, KLC_UNUSED_KEY,
	       KLC_UNUSED_VALUE, KLC_FLAGS, BPT_BALANCING_PLUS,
	       klc_load, klc_unload, klc_addrcmp, klc_keycmp, klc_valcmp,
	       NULL, NULL, &unused) != 0)
    {
      klc_clean_unused(&unused, size);
      fprintf(stderr, "example: cannot initialize the tree\n");
      exit(EXIT_FAILURE);
    }

  klc_clean_unused(&unused, size);
}

void			klc_add(t_bpt(klc)			*bpt,
				t_bpt_key(klc)			address,
				t_bpt_value(klc)		nblocks)
{
  t_bpt_uni(klc)	alloc = BPT_ADD_ALLOC(bpt);
  t_bpt_uni(klc)	size = BPT_ADD_SIZE(bpt);
  t_bpt_addr(klc)	array[size];
  t_bpt_lfentry(klc)	lfentry;
  t_bpt_unused(klc)	unused;

  klc_make_unused(&unused, array, size, alloc);

  lfentry.u.addr.address = address;
  lfentry.nblocks = nblocks;

  if (bpt_add(klc, bpt, &lfentry, &unused) != 0)
    {
      klc_clean_unused(&unused, size);
      fprintf(stderr, "example: cannot add an entry in the tree\n");
      exit(EXIT_FAILURE);
    }

  klc_clean_unused(&unused, size);
}

void			klc_mod(t_bpt(klc)			*bpt,
				t_bpt_key(klc)			idk,
				t_bpt_key(klc)			address,
				t_bpt_value(klc)		nblocks)
{
  t_bpt_uni(klc)	alloc = BPT_MODIFY_ALLOC(bpt);
  t_bpt_uni(klc)	size = BPT_MODIFY_SIZE(bpt);
  t_bpt_addr(klc)	array[size];
  t_bpt_lfentry(klc)	lfentry;
  t_bpt_unused(klc)	unused;

  klc_make_unused(&unused, array, size, alloc);

  lfentry.u.addr.address = address;
  lfentry.nblocks = nblocks;

  if (bpt_modify(klc, bpt, idk, &lfentry, &unused) != 0)
    {
      klc_clean_unused(&unused, size);
      fprintf(stderr, "example: cannot modify an entry in the tree\n");
      exit(EXIT_FAILURE);
    }

  klc_clean_unused(&unused, size);
}

void			klc_cmod(t_bpt(klc)			*bpt,
				 t_bpt_key(klc)			idk,
				 t_bpt_value(klc)		idv,
				 t_bpt_key(klc)			address,
				 t_bpt_value(klc)		nblocks)
{
  t_bpt_uni(klc)	alloc = BPT_MODIFY_ALLOC(bpt);
  t_bpt_uni(klc)	size = BPT_MODIFY_SIZE(bpt);
  t_bpt_addr(klc)	array[size];
  t_bpt_lfentry(klc)	lfentry;
  t_bpt_unused(klc)	unused;
  t_bpt_entry(klc)	entry;

  if (bpt_collide_search(klc, bpt, idk, idv, &entry) != 0)
    {
      fprintf(stderr, "example: cannot find the entry in collision\n");
      exit(EXIT_FAILURE);
    }

  klc_make_unused(&unused, array, size, alloc);

  lfentry.u.addr.address = address;
  lfentry.nblocks = nblocks;

  if (bpt_collide_modify(klc, bpt, entry, &lfentry, &unused) != 0)
    {
      klc_clean_unused(&unused, size);
      fprintf(stderr, "example: cannot modify an entry in collision\n");
      exit(EXIT_FAILURE);
    }

  klc_clean_unused(&unused, size);
}

void			klc_rem(t_bpt(klc)			*bpt,
				t_bpt_key(klc)			idk)
{
  t_bpt_uni(klc)	alloc = BPT_REMOVE_ALLOC(bpt);
  t_bpt_uni(klc)	size = BPT_REMOVE_SIZE(bpt);
  t_bpt_addr(klc)	array[size];
  t_bpt_unused(klc)	unused;

  klc_make_unused(&unused, array, size, alloc);

  if (bpt_remove(klc, bpt, idk, &unused) != 0)
    {
      klc_clean_unused(&unused, size);
      fprintf(stderr, "example: cannot remove an entry in the tree\n");
      exit(EXIT_FAILURE);
    }

  klc_clean_unused(&unused, size);
}

void			klc_crem(t_bpt(klc)			*bpt,
				 t_bpt_key(klc)			idk,
				 t_bpt_value(klc)		idv)
{
  t_bpt_uni(klc)	alloc = BPT_REMOVE_ALLOC(bpt);
  t_bpt_uni(klc)	size = BPT_REMOVE_SIZE(bpt);
  t_bpt_addr(klc)	array[size];
  t_bpt_unused(klc)	unused;
  t_bpt_entry(klc)	entry;

  if (bpt_collide_search(klc, bpt, idk, idv, &entry) != 0)
    {
      fprintf(stderr, "example: cannot find the entry in collision\n");
      exit(EXIT_FAILURE);
    }

  klc_make_unused(&unused, array, size, alloc);

  if (bpt_collide_remove(klc, bpt, entry, &unused) != 0)
    {
      klc_clean_unused(&unused, size);
      fprintf(stderr, "example: cannot remove an entry in collision\n");
      exit(EXIT_FAILURE);
    }

  klc_clean_unused(&unused, size);
}

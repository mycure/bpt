/*
 * ---------- header ----------------------------------------------------------
 *
 * project       bpt
 *
 * license       BSD
 *
 * file          /home/mycure/bpt/examples/strings/strings.c
 *
 * created       julien quintard   [thu jul 12 17:01:40 2007]
 * updated       julien quintard   [sun jul 15 12:11:11 2007]
 */

#include "strings.h"

#define BPT_DEBUG

#define STRINGS_ADDR_T		u_int32_t
#define STRINGS_KEY_T		char*
#define STRINGS_VALUE_T		char /* limited to an age of 127 */

#define STRINGS_NODESZ		59
#define STRINGS_UNUSED_ADDR	0
#define STRINGS_UNUSED_KEY	NULL
#define STRINGS_UNUSED_VALUE	-1
#define STRINGS_FLAGS		BPT_FLAG_ZERO

typedef struct		s_inentry
{
  STRINGS_KEY_T		name;
  STRINGS_ADDR_T	age;
}			t_inentry;

typedef struct		s_lfentry
{
  STRINGS_KEY_T		name;
  STRINGS_VALUE_T	age;
}			t_lfentry;

bpt_make(strings, BPT_NDI_T, BPT_UNI_T, BPT_NODES_T,
	 BPT_HEIGHT_T, STRINGS_ADDR_T, STRINGS_KEY_T, STRINGS_VALUE_T,
	 t_inentry, t_lfentry, name, age);

/*
 * functions
 */

void			strings_load(t_bpt(strings)		*bpt,
				     t_bpt_imm(strings)		*node,
				     t_bpt_node(strings)	addr)
{
  node->addr = addr;
  node->buf = (void *)addr;

  /*
   * do nothing because we are in main memory
   */
}

void			strings_unload(t_bpt(strings)		*bpt,
				       t_bpt_imm(strings)	*node)
{
  /*
   * do nothing, again...
   */
}

int			strings_addrcmp(t_bpt(strings)		*bpt,
					t_bpt_addr(strings)	addr1,
					t_bpt_addr(strings)	addr2)
{
  if (addr1 < addr2)
    return (-1);
  else
    return (addr1 > addr2);
}

int			strings_keycmp(t_bpt(strings)		*bpt,
				       t_bpt_key(strings)	key1,
				       t_bpt_key(strings)	key2)
{
  if (key1 == key2)
    return (0);

  if ((key1 == bpt->ukey) || (key2 == bpt->ukey))
    return (-1);

  /*
   * sort alphabetical reverse
   */
  return (strcmp(key2, key1));
}

int			strings_valcmp(t_bpt(strings)		*bpt,
				       t_bpt_value(strings)	val1,
				       t_bpt_value(strings)	val2)
{
  if (val1 < val2)
    return (-1);
  else
    return (val1 > val2);
}

/*
 * functions
 */

void			strings_make_unused(t_bpt_unused(strings) *unused,
					    t_bpt_addr(strings)	*array,
					    t_bpt_uni(strings)	size,
					    t_bpt_uni(strings)	alloc)
{
  t_bpt_uni(strings)	i;

  unused->array = array;
  unused->index = alloc - 1;

  for (i = 0; i < size; i++)
    unused->array[i] = (t_bpt_addr(strings))STRINGS_UNUSED_ADDR;

  for (i = 0; i < alloc; i++)
    unused->array[i] = (t_bpt_addr(strings))malloc(STRINGS_NODESZ);
}

void			strings_clean_unused(t_bpt_unused(strings) *unused,
					     t_bpt_uni(strings)	size)
{
  t_bpt_uni(strings)	i;

  for (i = 0; i < size; i++)
    if (unused->array[i] != STRINGS_UNUSED_ADDR)
      free((void *)unused->array[i]);
}

void			strings_init(t_bpt(strings)		*bpt)
{
  t_bpt_uni(strings)	alloc = BPT_INIT_ALLOC();
  t_bpt_uni(strings)	size = BPT_INIT_SIZE();
  t_bpt_addr(strings)	array[size];
  t_bpt_unused(strings)	unused;

  strings_make_unused(&unused, array, size, alloc);

  if (bpt_init(strings, bpt, STRINGS_NODESZ, STRINGS_UNUSED_ADDR,
	       STRINGS_UNUSED_KEY, STRINGS_UNUSED_VALUE, STRINGS_FLAGS,
	       BPT_BALANCING_PLUS,
	       strings_load, strings_unload, strings_addrcmp,
	       strings_keycmp, strings_valcmp, NULL, NULL, &unused) != 0)
    {
      strings_clean_unused(&unused, size);
      fprintf(stderr, "example: cannot initialize the tree\n");
      exit(EXIT_FAILURE);
    }

  strings_clean_unused(&unused, size);
}

void			strings_add(t_bpt(strings)		*bpt,
				    t_bpt_key(strings)		name,
				    t_bpt_value(strings)	age)
{
  t_bpt_uni(strings)	alloc = BPT_ADD_ALLOC(bpt);
  t_bpt_uni(strings)	size = BPT_ADD_SIZE(bpt);
  t_bpt_addr(strings)	array[size];
  t_bpt_lfentry(strings) lfentry;
  t_bpt_unused(strings)	unused;

  strings_make_unused(&unused, array, size, alloc);

  lfentry.name = strdup(name);
  lfentry.age = age;

  if (bpt_add(strings, bpt, &lfentry, &unused) != 0)
    {
      strings_clean_unused(&unused, size);
      fprintf(stderr, "example: cannot add an entry in the tree\n");
      exit(EXIT_FAILURE);
    }

  strings_clean_unused(&unused, size);
}

void			strings_rem(t_bpt(strings)		*bpt,
				    t_bpt_key(strings)		name)
{
  t_bpt_uni(strings)	alloc = BPT_REMOVE_ALLOC(bpt);
  t_bpt_uni(strings)	size = BPT_REMOVE_SIZE(bpt);
  t_bpt_addr(strings)	array[size];
  t_bpt_unused(strings)	unused;

  strings_make_unused(&unused, array, size, alloc);

  if (bpt_remove(strings, bpt, name, &unused) != 0)
    {
      strings_clean_unused(&unused, size);
      fprintf(stderr, "example: cannot remove an entry in the tree\n");
      exit(EXIT_FAILURE);
    }

  strings_clean_unused(&unused, size);
}

void			strings_dump_entry(t_bpt(strings)	*bpt,
					   t_bpt_imm(strings)	*node,
					   t_bpt_ndi(strings)	i)
{
  printf("[%u] %s : %d\n",
	 i,
         BPT_KEYCMP(bpt, BPT_GET_ENTRY(strings, node, i, name),
		    bpt->ukey) == 0 ?
	 "nil" : BPT_GET_ENTRY(strings, node, i, name),
         BPT_KEYCMP(bpt, BPT_GET_ENTRY(strings, node, i, name),
		    bpt->ukey) == 0 ?
         -1 : BPT_GET_ENTRY(strings, node, i, age));
}

#define		STRINGS_INDENT(_level_)					\
  {									\
    int		_i_;							\
									\
    for (_i_ = 0; _i_ < (_level_ * 3); _i_++)				\
      printf(" ");							\
  }

void			strings_dump_node(t_bpt(strings)	*bpt,
					  t_bpt_imm(strings)	*node,
					  t_bpt_height(strings)	level)
{
  t_bpt_ndi(strings)	nkeys = BPT_NKEYS(strings, bpt, node);
  t_bpt_imm(strings)	child;
  t_bpt_ndi(strings)	i;

  STRINGS_INDENT(level);

  printf("[head] ");
  if (BPT_GET_HEAD(strings, node, type) == BPT_TYPE_INTERNAL)
    printf("internal");
  else
    printf("leaf");
  printf("\n");

  for (i = 0; i < nkeys; i++)
    {
      STRINGS_INDENT(level);

      if (BPT_GET_HEAD(strings, node, type) == BPT_TYPE_LEAF)
	strings_dump_entry(bpt, node, i);

      if ((BPT_GET_HEAD(strings, node, type) == BPT_TYPE_INTERNAL) &&
	  (BPT_KEYCMP(bpt, BPT_GET_ENTRY(strings, node, i, name),
		      bpt->ukey) != 0))
	{
	  BPT_LOAD(bpt, &child, BPT_GET_ENTRY(strings, node, i, age));

	  printf("\n");

	  strings_dump_node(bpt, &child, level + 1);

	  BPT_UNLOAD(bpt, &child);
	}
    }
}

void			strings_dump(t_bpt(strings)			*bpt)
{
  t_bpt_imm(strings)	root;

  BPT_LOAD(bpt, &root, bpt->root);
  strings_dump_node(bpt, &root, 0);
  BPT_UNLOAD(bpt, &root);
}

/*
 * main function
 */

int			main(void)
{
  t_bpt(strings)	bpt;

  strings_init(&bpt);

  strings_add(&bpt, "chiche", -3);
  strings_add(&bpt, "chodaboy", 9);
  strings_add(&bpt, "dave", 49);
  strings_add(&bpt, "orbison", 2);
  strings_add(&bpt, "hamster", 120);
  strings_add(&bpt, "enculees jumelles", 2);
  strings_add(&bpt, "chodachien", 89);
  strings_add(&bpt, "l'homme neutre", 1);
  strings_add(&bpt, "spermix zero", -8);

  strings_dump(&bpt);

  return (0);
}

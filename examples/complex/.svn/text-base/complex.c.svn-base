/*
 * ---------- header ----------------------------------------------------------
 *
 * project       bpt
 *
 * license       BSD
 *
 * file          /home/mycure/bpt/examples/complex/complex.c
 *
 * created       julien quintard   [thu jul 12 17:01:40 2007]
 * updated       julien quintard   [mon sep 12 06:00:42 2011]
 */

#include "complex.h"

#define BPT_DEBUG

typedef struct		s_address
{
  int			block;
  int			offset;
}			t_address;

typedef struct		s_key
{
  int			real;
  int			imaginary;
}			t_key;

typedef struct		s_value
{
  int			length;
  char*			string;
}			t_value;

#define COMPLEX_ADDR_T		t_address
#define COMPLEX_KEY_T		t_key
#define COMPLEX_VALUE_T		t_value

t_address		uaddress =
  {
    .block = 0,
    .offset = 0
  };

t_key			ukey =
  {
    .real = 0,
    .imaginary = 0
  };

t_value			uvalue =
  {
    .length = 0,
    .string = NULL
  };

#define COMPLEX_NODESZ		59
#define COMPLEX_UNUSED_ADDR	uaddress
#define COMPLEX_UNUSED_KEY	ukey
#define COMPLEX_UNUSED_VALUE	uvalue
#define COMPLEX_FLAGS		BPT_FLAG_ZERO

typedef struct		s_inentry
{
  COMPLEX_KEY_T		K;
  COMPLEX_ADDR_T	V;
}			t_inentry;

typedef struct		s_lfentry
{
  COMPLEX_KEY_T		K;
  COMPLEX_VALUE_T	V;
}			t_lfentry;

bpt_make(complex, BPT_NDI_T, BPT_UNI_T, BPT_NODES_T,
	 BPT_HEIGHT_T, COMPLEX_ADDR_T, COMPLEX_KEY_T, COMPLEX_VALUE_T,
	 t_inentry, t_lfentry, K, V);

/*
 * functions
 */

void			complex_load(t_bpt(complex)		*bpt,
				     t_bpt_imm(complex)		*node,
				     t_bpt_node(complex)	addr)
{
  node->addr = addr;
  node->buf = (void *)addr.block;

  /*
   * do nothing because we are in main memory
   */
}

void			complex_unload(t_bpt(complex)		*bpt,
				       t_bpt_imm(complex)	*node)
{
  /*
   * do nothing, again...
   */
}

int			complex_addrcmp(t_bpt(complex)		*bpt,
					t_bpt_addr(complex)	addr1,
					t_bpt_addr(complex)	addr2)
{
  if (addr1.block < addr2.block)
    return (-1);
  else
    return (addr1.block > addr2.block);
}

int			complex_keycmp(t_bpt(complex)		*bpt,
				       t_bpt_key(complex)	key1,
				       t_bpt_key(complex)	key2)
{
  int			k1 = key1.real + key1.imaginary;
  int			k2 = key2.real + key2.imaginary;
  int			uk = bpt->ukey.real + bpt->ukey.imaginary;

  if (k1 == k2)
    return (0);

  if ((k1 == uk) || (k2 == uk))
    return (-1);

  if (k1 < k2)
    return (-1);
  else
    return (k1 > k2);
}

int			complex_valcmp(t_bpt(complex)		*bpt,
				       t_bpt_value(complex)	val1,
				       t_bpt_value(complex)	val2)
{
  if (val1.length < val2.length)
    return (-1);
  else
    return (val1.length > val2.length);
}

/*
 * functions
 */

void			complex_make_unused(t_bpt_unused(complex) *unused,
					    t_bpt_addr(complex)	*array,
					    t_bpt_uni(complex)	size,
					    t_bpt_uni(complex)	alloc)
{
  t_bpt_uni(complex)	i;

  unused->array = array;
  unused->index = alloc - 1;

  for (i = 0; i < size; i++)
    unused->array[i] = (t_bpt_addr(complex))COMPLEX_UNUSED_ADDR;

  for (i = 0; i < alloc; i++)
    {
      unused->array[i].block = (int)malloc(COMPLEX_NODESZ);
      unused->array[i].offset = 0;
    }
}

void			complex_clean_unused(t_bpt(complex)	*bpt,
					     t_bpt_unused(complex) *unused,
					     t_bpt_uni(complex)	size)
{
  t_bpt_uni(complex)	i;

  for (i = 0; i < size; i++)
    if (BPT_ADDRCMP(bpt, unused->array[i], COMPLEX_UNUSED_ADDR) == 0)
      free((void *)unused->array[i].block);
}

void			complex_init(t_bpt(complex)		*bpt)
{
  t_bpt_uni(complex)	alloc = BPT_INIT_ALLOC();
  t_bpt_uni(complex)	size = BPT_INIT_SIZE();
  t_bpt_addr(complex)	array[size];
  t_bpt_unused(complex)	unused;

  complex_make_unused(&unused, array, size, alloc);

  if (bpt_init(complex, bpt, COMPLEX_NODESZ, COMPLEX_UNUSED_ADDR,
	       COMPLEX_UNUSED_KEY, COMPLEX_UNUSED_VALUE, COMPLEX_FLAGS,
	       BPT_BALANCING_PLUS,
	       complex_load, complex_unload, complex_addrcmp,
	       complex_keycmp, complex_valcmp, NULL, NULL, &unused) != 0)
    {
      complex_clean_unused(bpt, &unused, size);
      fprintf(stderr, "example: cannot initialize the tree\n");
      exit(EXIT_FAILURE);
    }

  complex_clean_unused(bpt, &unused, size);
}

void			complex_add(t_bpt(complex)		*bpt,
				    t_bpt_key(complex)		K,
				    t_bpt_value(complex)	V)
{
  t_bpt_uni(complex)	alloc = BPT_ADD_ALLOC(bpt);
  t_bpt_uni(complex)	size = BPT_ADD_SIZE(bpt);
  t_bpt_addr(complex)	array[size];
  t_bpt_lfentry(complex) lfentry;
  t_bpt_unused(complex)	unused;

  complex_make_unused(&unused, array, size, alloc);

  lfentry.K = K;
  lfentry.V = V;

  if (bpt_add(complex, bpt, &lfentry, &unused) != 0)
    {
      complex_clean_unused(bpt, &unused, size);
      fprintf(stderr, "example: cannot add an entry in the tree\n");
      exit(EXIT_FAILURE);
    }

  complex_clean_unused(bpt, &unused, size);
}

void			complex_rem(t_bpt(complex)		*bpt,
				    t_bpt_key(complex)		K)
{
  t_bpt_uni(complex)	alloc = BPT_REMOVE_ALLOC(bpt);
  t_bpt_uni(complex)	size = BPT_REMOVE_SIZE(bpt);
  t_bpt_addr(complex)	array[size];
  t_bpt_unused(complex)	unused;

  complex_make_unused(&unused, array, size, alloc);

  if (bpt_remove(complex, bpt, K, &unused) != 0)
    {
      complex_clean_unused(bpt, &unused, size);
      fprintf(stderr, "example: cannot remove an entry in the tree\n");
      exit(EXIT_FAILURE);
    }

  complex_clean_unused(bpt, &unused, size);
}

void			complex_dump_entry(t_bpt(complex)	*bpt,
					   t_bpt_imm(complex)	*node,
					   t_bpt_ndi(complex)	i)
{
  printf("  [%u] ", i);

  if (BPT_KEYCMP(bpt, BPT_GET_ENTRY(complex, node, i, K), bpt->ukey) == 0)
    printf("nil");
  else
    {
      t_key	k = BPT_GET_ENTRY(complex, node, i, K);

      printf("%d %d", k.real, k.imaginary);
    }

  printf(" : ");

  if (BPT_KEYCMP(bpt, BPT_GET_ENTRY(complex, node, i, K), bpt->ukey) == 0)
    printf("nil");
  else
    {
      if (BPT_GET_HEAD(complex, node, type) == BPT_TYPE_INTERNAL)
	{
	  t_address a = BPT_GET_INENTRY(complex, node, i, V);

	  printf("%u %u\n", a.block, a.offset);
	}
      else
	{
	  t_value v = BPT_GET_LFENTRY(complex, node, i, V);

	  printf("%u %s\n", v.length, v.string);
	}
    }

  printf("\n");
}

#define		COMPLEX_INDENT(_level_)					\
  {									\
    int		_i_;							\
									\
    for (_i_ = 0; _i_ < (_level_ * 3); _i_++)				\
      printf(" ");							\
  }

void			complex_dump_node(t_bpt(complex)	*bpt,
					  t_bpt_imm(complex)	*node,
					  t_bpt_height(complex)	level)
{
  t_bpt_ndi(complex)	nkeys = BPT_NKEYS(complex, bpt, node);
  t_bpt_imm(complex)	child;
  t_bpt_ndi(complex)	i;

  COMPLEX_INDENT(level);

  printf("[head] ");
  if (BPT_GET_HEAD(complex, node, type) == BPT_TYPE_INTERNAL)
    printf("internal");
  else
    printf("leaf");
  printf("\n");

  for (i = 0; i < nkeys; i++)
    {
      COMPLEX_INDENT(level);

      if (BPT_GET_HEAD(complex, node, type) == BPT_TYPE_LEAF)
	complex_dump_entry(bpt, node, i);

      if ((BPT_GET_HEAD(complex, node, type) == BPT_TYPE_INTERNAL) &&
	  (BPT_KEYCMP(bpt, BPT_GET_ENTRY(complex, node, i, K),
		      bpt->ukey) != 0))
	{
	  BPT_LOAD(bpt, &child, BPT_GET_INENTRY(complex, node, i, V));

	  printf("\n");

	  complex_dump_node(bpt, &child, level + 1);

	  BPT_UNLOAD(bpt, &child);
	}
    }
}

void			complex_dump(t_bpt(complex)			*bpt)
{
  t_bpt_imm(complex)	root;

  BPT_LOAD(bpt, &root, bpt->root);
  complex_dump_node(bpt, &root, 0);
  BPT_UNLOAD(bpt, &root);
}

/*
 * main function
 */

int			main(void)
{
  t_bpt(complex)	bpt;

  complex_init(&bpt);

  complex_add(&bpt,
	      (t_key){ .real = 4, .imaginary = 2 },
	      (t_value){ .length = 3, .string = "XXX"});

  complex_add(&bpt,
	      (t_key){ .real = 8, .imaginary = 4 },
	      (t_value){ .length = 4, .string = "dave"});

  complex_add(&bpt,
	      (t_key){ .real = 2, .imaginary = 1 },
	      (t_value){ .length = 7, .string = "licorne"});

  complex_dump(&bpt);

  return (0);
}

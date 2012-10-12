/*
 * ---------- header ----------------------------------------------------------
 *
 * project       bpt
 *
 * license       BSD
 *
 * file          /home/mycure/bpt/test/tree.c
 *
 * created       julien quintard   [thu jul 12 17:29:39 2007]
 * updated       julien quintard   [sat jul 14 05:17:55 2007]
 */

/*
 * includes
 */

#include <sys/types.h>
#include "link.in"

/*
 * debug, used to print the error that occurs
 */

#undef TREE_DEBUG

/*
 * make the tree
 */

#include "../bpt.h"

bpt_make(tree, BPT_NDI_T, BPT_UNI_T, BPT_NODES_T,
	 BPT_HEIGHT_T, IN_ADDR_T, IN_KEY_T, IN_VALUE_T,
	 t_in_inentry, t_in_lfentry, key, value);

/*
 * error defines
 */

#define TREE_EZERO		0x0
#define TREE_EINIT		0x1
#define TREE_EOP		0x2
#define TREE_EVERIFY		0x3
#define TREE_ECLEAN		0x4
#define TREE_ELOAD		0x5
#define TREE_EALLOC		0x6

/*
 * global variables
 */

unsigned int    ___loaded = 0;
unsigned int    ___allocated = 0;

/*
 * prototypes
 */

#if 1

void			tree_dump_entry(t_bpt(tree)		*bpt,
					t_bpt_imm(tree)		*node,
					t_bpt_ndi(tree)		i);

void			tree_dump_node(t_bpt(tree)		*bpt,
				       t_bpt_imm(tree)		*node,
				       t_bpt_height(tree)	level);

void			tree_dump(t_bpt(tree)			*bpt);

#endif

void			tree_load(t_bpt(tree)			*bpt,
				  t_bpt_imm(tree)		*node,
				  t_bpt_node(tree)		addr);

void			tree_unload(t_bpt(tree)			*bpt,
				    t_bpt_imm(tree)		*node);

int			tree_addrcmp(t_bpt(tree)		*bpt,
				     t_bpt_addr(tree)		addr2,
				     t_bpt_addr(tree)		addr1);

int			tree_keycmp(t_bpt(tree)			*bpt,
				    t_bpt_key(tree)		key2,
				    t_bpt_key(tree)		key1);

int			tree_valcmp(t_bpt(tree)			*bpt,
				    t_bpt_value(tree)		val2,
				    t_bpt_value(tree)		val1);

#if (IN_FLAGS & BPT_FLAG_CALLBACK) && defined(IN_INTERVAL_T)

IN_INTERVAL_T		tree_get_interval(t_bpt(tree)		*bpt,
					  t_bpt_imm(tree)	*node);

void			tree_callback_update_node(t_bpt(tree)      *bpt,
						  t_bpt_imm(tree)  *node,
						  t_bpt_node(tree) addr,
						  IN_INTERVAL_T    interval);

void			tree_callback_update(t_bpt(tree)	*bpt,
					     t_bpt_imm(tree)	*node);

void			tree_callback_interval(t_bpt(tree)	*bpt,
					       t_bpt_imm(tree)	*node1,
					       t_bpt_ndi(tree)	ndi);

void			tree_callback_insert(t_bpt(tree)	*bpt,
					     t_bpt_cbctx(tree)	*cbctx);

void			tree_callback_split(t_bpt(tree)		*bpt,
					    t_bpt_cbctx(tree)	*cbctx);

void			tree_callback_modify(t_bpt(tree)	*bpt,
					     t_bpt_cbctx(tree)	*cbctx);

void			tree_callback_delete(t_bpt(tree)	*bpt,
					     t_bpt_cbctx(tree)	*cbctx);

void			tree_callback_migrate(t_bpt(tree)	*bpt,
					      t_bpt_cbctx(tree)	*cbctx);

void			tree_callback_balance(t_bpt(tree)	*bpt,
					      t_bpt_cbctx(tree)	*cbctx);

#endif

void			tree_callback(t_bpt(tree)		*bpt,
				      t_bpt_cbctx(tree)		*cbctx);

void			tree_make_unused(t_bpt_unused(tree)	*unused,
					 t_bpt_addr(tree)	*array,
					 t_bpt_uni(tree)	size,
					 t_bpt_uni(tree)	alloc);

void			tree_clean_unused(t_bpt_unused(tree)	*unused,
					  t_bpt_uni(tree)	size);

int			tree_init(t_bpt(tree)			*bpt);

int			tree_add(t_bpt(tree)			*bpt,
				 t_bpt_key(tree)		key,
				 t_bpt_value(tree)		value);

int			tree_mod(t_bpt(tree)			*bpt,
				 t_bpt_key(tree)		idk,
				 t_bpt_key(tree)		key,
				 t_bpt_value(tree)		value);

int			tree_rem(t_bpt(tree)			*bpt,
				 t_bpt_key(tree)		idk);

int			tree_clean(t_bpt(tree)			*bpt);

void			tree_exit(int				code,
				  char				*msg,
				  int				error);

int			tree_op(t_bpt(tree)			*bpt,
				t_in_input			input);

#if (IN_FLAGS & BPT_FLAG_CALLBACK) && defined(IN_INTERVAL_T)

IN_INTERVAL_T		tree_compute_interval(t_bpt(tree)	*bpt,
					      t_bpt_imm(tree)	*node1,
					      t_bpt_ndi(tree)	ndi);

#endif

int			tree_verify(t_bpt(tree)			*bpt,
				    t_in_output			*output,
				    u_int64_t			i);

void			tree_main(void);

/*
 * functions in relation with bpt library
 */

void			tree_load(t_bpt(tree)			*bpt,
				  t_bpt_imm(tree)		*node,
				  t_bpt_node(tree)		addr)
{
  node->addr = addr;
  node->buf = (void *)((unsigned int)addr);
}

void			tree_unload(t_bpt(tree)			*bpt,
				    t_bpt_imm(tree)		*node)
{
  /*
   * nothing to do
   */
}

int			tree_addrcmp(t_bpt(tree)		*bpt,
				     t_bpt_addr(tree)		addr1,
				     t_bpt_addr(tree)		addr2)
{
  if (addr1 < addr2)
    return (-1);
  else
    return (addr1 > addr2);
}

int			tree_keycmp(t_bpt(tree)			*bpt,
				    t_bpt_key(tree)		key1,
				    t_bpt_key(tree)		key2)
{
  if (key1 < key2)
    return (-1);
  else
    return (key1 > key2);
}

int			tree_valcmp(t_bpt(tree)			*bpt,
				    t_bpt_value(tree)		val1,
				    t_bpt_value(tree)		val2)
{
  if (val1 < val2)
    return (-1);
  else
    return (val1 > val2);
}

#if (IN_FLAGS & BPT_FLAG_CALLBACK) && defined(IN_INTERVAL_T)

IN_INTERVAL_T		tree_get_interval(t_bpt(tree)		*bpt,
					  t_bpt_imm(tree)	*node)
{

  /*
   * we decide to keep the higher interval in each internal node
   */

  t_bpt_ndi(tree)	nkeys = BPT_NKEYS(tree, bpt, node);
  IN_INTERVAL_T		interval = -1;
  t_bpt_ndi(tree)	i;

  for (i = 0; (i < nkeys) &&
	 (BPT_KEYCMP(bpt, BPT_GET_ENTRY(tree, node, i, key),
		     bpt->ukey) != 0);
       i++)
    {
      if (i == 0)
	interval = BPT_GET_ENTRY(tree, node, i, interval);

      if (interval < BPT_GET_ENTRY(tree, node, i, interval))
	interval = BPT_GET_ENTRY(tree, node, i, interval);
    }

  return (interval);
}

void			tree_callback_update_node(t_bpt(tree) *bpt,
						  t_bpt_imm(tree) *node,
						  t_bpt_node(tree) addr,
						  IN_INTERVAL_T interval)
{
  t_bpt_imm(tree)	parent;
  t_bpt_ndi(tree)	ndi;

  /*
   * we use the node's address to retrieve the parent node entry that points
   * to the node to update.
   */

  if (bpt_ndi(tree, bpt, node, addr, &ndi) != 0)
    return ;

  if (interval == BPT_GET_ENTRY(tree, node, ndi, interval))
    return;

  BPT_SET_ENTRY(tree, node, ndi, interval, interval);

  if (BPT_GET_HEAD(tree, node, parent) == bpt->uaddr)
    return ;

  if ((interval = tree_get_interval(bpt, node)) == -1)
    return;

  BPT_LOAD(bpt, &parent, BPT_GET_HEAD(tree, node, parent));
  tree_callback_update_node(bpt, &parent, node->addr, interval);
  BPT_UNLOAD(bpt, &parent);  
}

void			tree_callback_update(t_bpt(tree)	*bpt,
					     t_bpt_imm(tree)	*node)
{
  IN_INTERVAL_T		interval;
  t_bpt_imm(tree)	parent;

  if (BPT_GET_HEAD(tree, node, parent) == bpt->uaddr)
    return;

  if ((interval = tree_get_interval(bpt, node)) == -1)
    return;

  BPT_LOAD(bpt, &parent, BPT_GET_HEAD(tree, node, parent));
  tree_callback_update_node(bpt, &parent, node->addr, interval);
  BPT_UNLOAD(bpt, &parent);  
}

void			tree_callback_interval(t_bpt(tree)	*bpt,
					       t_bpt_imm(tree)	*node1,
					       t_bpt_ndi(tree)	ndi)
{
  t_bpt_entry(tree)	current = { node1->addr, ndi };
  IN_INTERVAL_T		interval;
  t_bpt_imm(tree)	node2;
  t_bpt_entry(tree)	next;

  if (bpt_next_entry(tree, bpt, current, &next, BPT_OPT_TREE) == 0)
    {
      BPT_LOAD(bpt, &node2, next.node);

      interval = BPT_GET_ENTRY(tree, &node2, next.ndi, key) -
	(BPT_GET_ENTRY(tree, node1, current.ndi, key) +
	 BPT_GET_ENTRY(tree, node1, current.ndi, value));

      BPT_SET_ENTRY(tree, node1, current.ndi, interval, interval);

      BPT_UNLOAD(bpt, &node2);
    }
  else
    BPT_SET_ENTRY(tree, node1, current.ndi, interval, 0);
}

void			tree_callback_insert(t_bpt(tree)	*bpt,
					     t_bpt_cbctx(tree)	*cbctx)
{
  t_bpt_imm(tree)	update;
  t_bpt_imm(tree)	node1;
  t_bpt_entry(tree)	prev;

  BPT_LOAD(bpt, &node1, cbctx->current.node);
  tree_callback_interval(bpt, &node1, cbctx->current.ndi);
  BPT_UNLOAD(bpt, &node1);

  if (bpt_prev_entry(tree, bpt, cbctx->current, &prev, BPT_OPT_TREE) == 0)
    {
      t_bpt_imm(tree)	node2;

      BPT_LOAD(bpt, &node2, prev.node);
      tree_callback_interval(bpt, &node2, prev.ndi);
      tree_callback_update(bpt, &node2);
      BPT_UNLOAD(bpt, &node2);
    }

  BPT_LOAD(bpt, &update, cbctx->node);
  tree_callback_update(bpt, &update);
  BPT_UNLOAD(bpt, &update);
}

void			tree_callback_split(t_bpt(tree)		*bpt,
					    t_bpt_cbctx(tree)	*cbctx)
{
  t_bpt_imm(tree)	update;
  t_bpt_imm(tree)	node1;
  t_bpt_entry(tree)	prev;

  BPT_LOAD(bpt, &node1, cbctx->current.node);
  tree_callback_interval(bpt, &node1, cbctx->current.ndi);
  BPT_UNLOAD(bpt, &node1);

  if (bpt_prev_entry(tree, bpt, cbctx->current, &prev, BPT_OPT_TREE) == 0)
    {
      t_bpt_imm(tree)	node2;

      BPT_LOAD(bpt, &node2, prev.node);
      tree_callback_interval(bpt, &node2, prev.ndi);
      tree_callback_update(bpt, &node2);
      BPT_UNLOAD(bpt, &node2);
    }

  BPT_LOAD(bpt, &update, cbctx->node1);
  tree_callback_update(bpt, &update);
  BPT_UNLOAD(bpt, &update);

  BPT_LOAD(bpt, &update, cbctx->node2);
  tree_callback_update(bpt, &update);
  BPT_UNLOAD(bpt, &update);
}

void			tree_callback_modify(t_bpt(tree)	*bpt,
					     t_bpt_cbctx(tree)	*cbctx)
{
  t_bpt_imm(tree)	update;
  t_bpt_imm(tree)	node;

  BPT_LOAD(bpt, &node, cbctx->current.node);
  tree_callback_interval(bpt, &node, cbctx->current.ndi);
  BPT_UNLOAD(bpt, &node);

  BPT_LOAD(bpt, &update, cbctx->node);
  tree_callback_update(bpt, &update);
  BPT_UNLOAD(bpt, &update);
}

void			tree_callback_delete(t_bpt(tree)	*bpt,
					     t_bpt_cbctx(tree)	*cbctx)
{
  t_bpt_imm(tree)	update;
  t_bpt_imm(tree)	node;

  if (cbctx->previous.node != bpt->uaddr)
    {
      BPT_LOAD(bpt, &node, cbctx->previous.node);
      tree_callback_interval(bpt, &node, cbctx->previous.ndi);
      BPT_UNLOAD(bpt, &node);
    }

  BPT_LOAD(bpt, &update, cbctx->node);
  tree_callback_update(bpt, &update);
  BPT_UNLOAD(bpt, &update);
}

void			tree_callback_migrate(t_bpt(tree)	*bpt,
					      t_bpt_cbctx(tree)	*cbctx)
{
  t_bpt_imm(tree)	update;
  t_bpt_imm(tree)	node;

  if (cbctx->previous.node != bpt->uaddr)
    {
      BPT_LOAD(bpt, &node, cbctx->previous.node);
      tree_callback_interval(bpt, &node, cbctx->previous.ndi);
      BPT_UNLOAD(bpt, &node);
    }

  BPT_LOAD(bpt, &update, cbctx->node);
  tree_callback_update(bpt, &update);
  BPT_UNLOAD(bpt, &update);
}

void			tree_callback_balance(t_bpt(tree)	*bpt,
					      t_bpt_cbctx(tree)	*cbctx)
{
  t_bpt_imm(tree)	update;
  t_bpt_imm(tree)	node;

  if (cbctx->previous.node != bpt->uaddr)
    {
      BPT_LOAD(bpt, &node, cbctx->previous.node);
      tree_callback_interval(bpt, &node, cbctx->previous.ndi);
      BPT_UNLOAD(bpt, &node);
    }

  BPT_LOAD(bpt, &update, cbctx->node1);
  tree_callback_update(bpt, &update);
  BPT_UNLOAD(bpt, &update);

  BPT_LOAD(bpt, &update, cbctx->node2);
  tree_callback_update(bpt, &update);
  BPT_UNLOAD(bpt, &update);
}

void			tree_callback(t_bpt(tree)		*bpt,
				      t_bpt_cbctx(tree)		*cbctx)
{

#if 0
  printf("---[callback][0x%x] [prev] %qd:%qd [current] %qd:%qd [node] %qd "
	 "[node1] %qd [node2] %qd\n",
	 cbctx->cb,
	 (int64_t)cbctx->previous.node,
	 (int64_t)cbctx->previous.ndi,
	 (int64_t)cbctx->current.node,
	 (int64_t)cbctx->current.ndi,
	 (int64_t)cbctx->node,
	 (int64_t)cbctx->node1,
	 (int64_t)cbctx->node2);
#endif

  switch (cbctx->cb)
    {
    case BPT_CB_INSERT:
      tree_callback_insert(bpt, cbctx);
      break;
    case BPT_CB_SPLIT:
      tree_callback_split(bpt, cbctx);
      break;
    case BPT_CB_MODIFY:
      tree_callback_modify(bpt, cbctx);
      break;
    case BPT_CB_DELETE:
      tree_callback_delete(bpt, cbctx);
      break;
    case BPT_CB_MIGRATE:
      tree_callback_migrate(bpt, cbctx);
      break;
    case BPT_CB_BALANCE:
      tree_callback_balance(bpt, cbctx);
      break;
    }
}

#else

void			tree_callback(t_bpt(tree)		*bpt,
				      t_bpt_cbctx(tree)		*cbctx)
{

}

#endif

/*
 * functions
 */

void			tree_make_unused(t_bpt_unused(tree)	*unused,
					 t_bpt_addr(tree)	*array,
					 t_bpt_uni(tree)	size,
					 t_bpt_uni(tree)	alloc)
{
  t_bpt_uni(tree)	i;

  unused->array = array;
  unused->index = alloc - 1;

  for (i = 0; i < size; i++)
    unused->array[i] = (t_bpt_addr(tree))IN_UNUSED_ADDR;

  for (i = 0; i < alloc; i++)
    {
      unused->array[i] = (t_bpt_addr(tree))((unsigned int)malloc(IN_NODESZ));
      ___allocated++;
    }
}

void			tree_clean_unused(t_bpt_unused(tree)	*unused,
					  t_bpt_uni(tree)	size)
{
  t_bpt_uni(tree)	i;

  for (i = 0; i < size; i++)
    if (unused->array[i] != IN_UNUSED_ADDR)
      {
	free((void *)((unsigned int)unused->array[i]));
	___allocated--;
      }
}

int			tree_init(t_bpt(tree)			*bpt)
{
  t_bpt_uni(tree)	alloc = BPT_INIT_ALLOC();
  t_bpt_uni(tree)	size = BPT_INIT_SIZE();
  t_bpt_addr(tree)	array[size];
  t_bpt_unused(tree)	unused;

  tree_make_unused(&unused, array, size, alloc);

  if (bpt_init(tree, bpt, IN_NODESZ, IN_UNUSED_ADDR, IN_UNUSED_KEY,
	       IN_UNUSED_VALUE, IN_FLAGS, 50, tree_load, tree_unload,
	       tree_addrcmp, tree_keycmp, tree_valcmp,
	       tree_callback, NULL, &unused) != 0)
    {
      tree_clean_unused(&unused, size);
      return (-1);
    }

  tree_clean_unused(&unused, size);

  return (0);
}

int			tree_add(t_bpt(tree)			*bpt,
				 t_bpt_key(tree)		key,
				 t_bpt_value(tree)		value)
{
  t_bpt_uni(tree)	alloc = BPT_ADD_ALLOC(bpt);
  t_bpt_uni(tree)	size = BPT_ADD_SIZE(bpt);
  t_bpt_addr(tree)	array[size];
  t_bpt_lfentry(tree)	lfentry;
  t_bpt_unused(tree)	unused;

  memset(&lfentry, 0x0, sizeof(t_bpt_lfentry(tree)));

  tree_make_unused(&unused, array, size, alloc);

  lfentry.key = key;
  lfentry.value = value;

  if (bpt_add(tree, bpt, &lfentry, &unused) != 0)
    {
      tree_clean_unused(&unused, size);
      return (-1);
    }

  tree_clean_unused(&unused, size);

  return (0);
}

int			tree_mod(t_bpt(tree)			*bpt,
				 t_bpt_key(tree)		idk,
				 t_bpt_key(tree)		key,
				 t_bpt_value(tree)		value)
{
  t_bpt_uni(tree)	alloc = BPT_MODIFY_ALLOC(bpt);
  t_bpt_uni(tree)	size = BPT_MODIFY_SIZE(bpt);
  t_bpt_addr(tree)	array[size];
  t_bpt_lfentry(tree)	lfentry;
  t_bpt_unused(tree)	unused;

  memset(&lfentry, 0x0, sizeof(t_bpt_lfentry(tree)));

  tree_make_unused(&unused, array, size, alloc);

  lfentry.key = key;
  lfentry.value = value;

  if (bpt_modify(tree, bpt, idk, &lfentry, &unused) != 0)
    {
      tree_clean_unused(&unused, size);
      return (-1);
    }

  tree_clean_unused(&unused, size);

  return (0);
}

int			tree_rem(t_bpt(tree)			*bpt,
				 t_bpt_key(tree)		idk)
{
  t_bpt_uni(tree)	alloc = BPT_REMOVE_ALLOC(bpt);
  t_bpt_uni(tree)	size = BPT_REMOVE_SIZE(bpt);
  t_bpt_addr(tree)	array[size];
  t_bpt_unused(tree)	unused;

  tree_make_unused(&unused, array, size, alloc);

  if (bpt_remove(tree, bpt, idk, &unused) != 0)
    {
      tree_clean_unused(&unused, size);
      return (-1);
    }

  tree_clean_unused(&unused, size);

  return (0);
}

int			tree_clean(t_bpt(tree)			*bpt)
{
  t_bpt_uni(tree)	alloc = BPT_CLEAN_ALLOC(bpt);
  t_bpt_uni(tree)	size = BPT_CLEAN_SIZE(bpt);
  t_bpt_addr(tree)	array[size];
  t_bpt_unused(tree)	unused;

  tree_make_unused(&unused, array, size, alloc);

  if (bpt_clean(tree, bpt, &unused) != 0)
    {
      tree_clean_unused(&unused, size);
      return (-1);
    }

  tree_clean_unused(&unused, size);

  return (0);
}

void			tree_exit(int				code,
				  char				*msg,
				  int				error)
{
  printf("%s", msg);

#ifdef TREE_DEBUG
  printf("-[%u]\n", error);
#else
  printf("\n");
#endif

  exit(code);
}

int			tree_op(t_bpt(tree)			*bpt,
				t_in_input			input)
{
  switch(input.op)
    {
      case IN_ADD:

#ifdef TREE_DEBUG
	printf("add %qd %qd\n", (int64_t)input.key, (int64_t)input.value);
#endif

	return (tree_add(bpt, input.key, input.value));
	break;
      case IN_MOD:

#ifdef TREE_DEBUG
	printf("mod %qd %qd %qd\n", (int64_t)input.id,
	       (int64_t)input.key, (int64_t)input.value);
#endif

	return (tree_mod(bpt, input.id, input.key, input.value));
	break;
      case IN_REM:

#ifdef TREE_DEBUG
	printf("rem %qd\n", (int64_t)input.id);
#endif

	return (tree_rem(bpt, input.id));
	break;
    }

  return (-1);
}

#if (IN_FLAGS & BPT_FLAG_CALLBACK) && defined(IN_INTERVAL_T)

IN_INTERVAL_T		tree_compute_interval(t_bpt(tree)	*bpt,
					      t_bpt_imm(tree)	*node1,
					      t_bpt_ndi(tree)	ndi)
{
  t_bpt_entry(tree)	current = { node1->addr, ndi };
  IN_INTERVAL_T		interval;
  t_bpt_imm(tree)	node2;
  t_bpt_entry(tree)	next;

  if (bpt_next_entry(tree, bpt, current, &next, BPT_OPT_TREE) != 0)
    return (0);

  BPT_LOAD(bpt, &node2, next.node);

  interval = BPT_GET_ENTRY(tree, &node2, next.ndi, key) -
    (BPT_GET_ENTRY(tree, node1, ndi, key) +
     BPT_GET_ENTRY(tree, node1, ndi, value));

  BPT_UNLOAD(bpt, &node2);

  return (interval);
}

#endif

int			tree_verify(t_bpt(tree)			*bpt,
				    t_in_output			*output,
				    u_int64_t			i)
{
  int64_t		nxt = (i + 1) >= IN_OUTPUT_NOPS ? -1 : i + 1;
  int64_t		prv = i == 0 ? -1 : i - 1;
  t_bpt_entry(tree)	previous;
  t_bpt_entry(tree)	current;
  t_bpt_imm(tree)	node1;
  t_bpt_imm(tree)	node2;
  t_bpt_entry(tree)	next;

  if (bpt_search(tree, bpt, output[i].key, &current) != 0)
    return (-1);

  BPT_LOAD(bpt, &node1, current.node);

#if (IN_FLAGS & BPT_FLAG_CALLBACK) && defined(IN_INTERVAL_T)
  if (BPT_GET_ENTRY(tree, &node1, current.ndi, interval) !=
      tree_compute_interval(bpt, &node1, current.ndi))
    {
      BPT_UNLOAD(bpt, &node1);
      return (-1);
    }
#endif

  if (prv != -1)
    {
      if (bpt_prev_entry(tree, bpt, current, &previous, BPT_OPT_TREE) != 0)
	{
	  BPT_UNLOAD(bpt, &node1);
	  return (-1);
	}

      BPT_LOAD(bpt, &node2, previous.node);

      if ((BPT_GET_ENTRY(tree, &node2, previous.ndi, key) !=
	   output[prv].key) ||
	  (BPT_GET_ENTRY(tree, &node2, previous.ndi, value) !=
	   output[prv].value))
	{
	  BPT_UNLOAD(bpt, &node2);
	  BPT_UNLOAD(bpt, &node1);
	  return (-1);
	}

      BPT_UNLOAD(bpt, &node2);
    }

  if (nxt != -1)
    {
      if (bpt_next_entry(tree, bpt, current, &next, BPT_OPT_TREE) != 0)
	{
	  BPT_UNLOAD(bpt, &node1);
	  return (-1);
	}

      BPT_LOAD(bpt, &node2, next.node);

      if ((BPT_GET_ENTRY(tree, &node2, next.ndi, key) !=
	   output[nxt].key) ||
	  (BPT_GET_ENTRY(tree, &node2, next.ndi, value) !=
	   output[nxt].value))
	{
	  BPT_UNLOAD(bpt, &node2);
	  BPT_UNLOAD(bpt, &node1);
	  return (-1);
	}

      BPT_UNLOAD(bpt, &node2);
    }

  return (0);
}

#if 1

void			tree_dump_entry(t_bpt(tree)		*bpt,
					t_bpt_imm(tree)		*node,
					t_bpt_ndi(tree)		i)
{
  printf("[entry %3u] k: %10qd\t\tv: %10qd\n",
	 i,
         BPT_GET_ENTRY(tree, node, i, key) == bpt->ukey ?
	 -1 : (int64_t)BPT_GET_ENTRY(tree, node, i, key),
         BPT_GET_ENTRY(tree, node, i, key) == bpt->ukey ?
         -1 : (int64_t)BPT_GET_ENTRY(tree, node, i, value));
}

#define		TREE_INDENT(_level_)					\
  {									\
    int		_i_;							\
									\
    for (_i_ = 0; _i_ < (_level_ * 3); _i_++)				\
      printf(" ");							\
  }

void			tree_dump_node(t_bpt(tree)		*bpt,
				       t_bpt_imm(tree)		*node,
				       t_bpt_height(tree)	level)
{
  t_bpt_ndi(tree)	nkeys = BPT_NKEYS(tree, bpt, node);
  t_bpt_imm(tree)	child;
  t_bpt_ndi(tree)	i;

  TREE_INDENT(level);

  printf("[head] t: ");
  if (BPT_GET_HEAD(tree, node, type) == BPT_TYPE_INTERNAL)
    printf("internal");
  else
    printf("leaf");

  printf(" (%qu)   parent: %qd   prv: %qd   nxt: %qd\n",
	 (int64_t)node->addr,
         BPT_GET_HEAD(tree, node, parent) == bpt->uaddr ?
	 -1 : (int64_t)BPT_GET_HEAD(tree, node, parent),
         BPT_GET_HEAD(tree, node, prv) == bpt->uaddr ?
	 -1 : (int64_t)BPT_GET_HEAD(tree, node, prv),
         BPT_GET_HEAD(tree, node, nxt) == bpt->uaddr ?
	 -1 : (int64_t)BPT_GET_HEAD(tree, node, nxt)); 

  for (i = 0; i < nkeys; i++)
    {
      TREE_INDENT(level);

      tree_dump_entry(bpt, node, i);

      if ((BPT_GET_HEAD(tree, node, type) == BPT_TYPE_INTERNAL) &&
	  (BPT_GET_ENTRY(tree, node, i, key) != bpt->ukey))
	{
	  BPT_LOAD(bpt, &child, BPT_GET_ENTRY(tree, node, i, value));

	  tree_dump_node(bpt, &child, level + 1);

	  BPT_UNLOAD(bpt, &child);
	}
    }
}

void			tree_dump(t_bpt(tree)			*bpt)
{
  t_bpt_imm(tree)	root;

  BPT_LOAD(bpt, &root, bpt->root);
  tree_dump_node(bpt, &root, 0);
  BPT_UNLOAD(bpt, &root);
}

#endif

void			tree_main(void)
{
  t_bpt(tree)		bpt;
  u_int64_t		i;

  if (tree_init(&bpt) != 0)
    tree_exit(EXIT_FAILURE, "[KO]", TREE_EINIT);

  for (i = 0; i < IN_INPUT_NOPS; i++)
    {
      if (tree_op(&bpt, input[i]) != 0)
	tree_exit(EXIT_FAILURE, "[KO]", TREE_EOP);

#if 0
      tree_dump(&bpt);
#endif

    }

  for (i = 0; i < IN_OUTPUT_NOPS; i++)
    if (tree_verify(&bpt, output, i) != 0)
      tree_exit(EXIT_FAILURE, "[KO]", TREE_EVERIFY);

  if (tree_clean(&bpt) != 0)
    tree_exit(EXIT_FAILURE, "[KO]", TREE_ECLEAN);

  if (___loaded != 0)
    tree_exit(EXIT_FAILURE, "[KO]", TREE_ELOAD);

  if (___allocated != 0)
    tree_exit(EXIT_FAILURE, "[KO]", TREE_EALLOC);
}

int			main(void)
{
  struct timeval	reftime;
  struct timeval	curtime;
  struct timeval	diff;
  struct timezone	tzp;

  printf("[%-5s] running %-15s		", "bpt", IN_NAME);
  fflush(stdout);

  gettimeofday(&reftime, &tzp);
  tree_main();
  gettimeofday(&curtime, &tzp);

  timersub(&curtime, &reftime, &diff);

  printf("%u.%u ", (unsigned int)diff.tv_sec,
	 (unsigned int)diff.tv_usec);

  tree_exit(EXIT_SUCCESS, "[OK]", TREE_EZERO);

  return (0);
}

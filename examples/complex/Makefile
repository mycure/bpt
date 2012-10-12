#
# ---------- header -----------------------------------------------------------
#
# project       bpt
#
# license       BSD
#
# file          /home/mycure/bpt/examples/complex/Makefile
#
# created       julien quintard   [thu jul 12 16:50:32 2007]
# updated       julien quintard   [thu jul 12 17:05:54 2007]
#

#
# ---------- variables --------------------------------------------------------
#

COMPLEX			=			complex

COMPLEX_SRCS		=			complex.c

COMPLEX_OBJS		=			$(COMPLEX_SRCS:.c=.o)

CC			=			gcc
CFLAGS			=			-Wall			\
						-Werror			\
						-Wuninitialized		\
						-Wunused		\
						-O3

RM			=			rm -f

#
# ---------- rules ------------------------------------------------------------
#

main:		$(COMPLEX_OBJS)
	$(CC) $(CFLAGS) $(COMPLEX_OBJS) -o $(COMPLEX)

clear:
	@$(RM) $(COMPLEX_OBJS) *~

clean:			clear
	@$(RM) $(COMPLEX)

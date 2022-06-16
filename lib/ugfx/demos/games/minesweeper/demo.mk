DEMODIR = $(GFXLIB)/demos/games/minesweeper

GFXINC +=   $(DEMODIR) \
			$(DEMODIR)/resources/romfs
			
GFXSRC +=	$(DEMODIR)/main.c \
			$(DEMODIR)/mines.c
			
DEFS += -DMINES_SHOW_SPLASH=GFXON

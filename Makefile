all: hello.gb

obj/start.obj: src/start.asm
	gb-lcc -c -o obj/start.obj src/start.asm

obj/main.obj: src/main.c 
	gb-lcc -c -o obj/main.obj -Igen -Iinclude src/main.c

obj/entity.obj: src/entity/entity.c
	gb-lcc -c -o obj/main.obj -Iinclude src/entity/entity.c

obj/e_player.obj: src/entity/e_player.c
	gb-lcc -c -o obj/e_player.o -Iinclude src/entity/e_player.c

obj/e_projectile.obj: src/entity/e_projectile.c
	gb-lcc -c -o obj/e_projectile.o -Iinclude src/entity/e_projectile.c

obj/world.obj: src/world.c
	gb-lcc -c -o obj/world.obj -Igen -Iinclude src/world.c

obj/oam.obj: src/oam.c
	gb-lcc -c -o obj/oam.obj -Iinclude src/oam.c

obj/tiles.obj: gen/tiles.c
	gb-lcc -c -o obj/tiles.obj -Iinclude gen/tiles.c

obj/maps.obj: gen/maps.c
	gb-lcc -c -o obj/maps.obj gen/maps.c

hello.gb: obj/start.obj obj/main.obj obj/tiles.obj obj/maps.obj obj/entity.obj \
	obj/oam.obj obj/e_player.obj obj/e_projectile.obj obj/world.obj
	link-gbz80 -- -z -m -j -x hello.gb obj/start.obj obj/main.obj obj/maps.obj \
		obj/entity.obj obj/oam.obj obj/e_player.obj obj/e_projectile.obj \
		obj/world.obj
	mv hello.map obj

@echo off
set PATH=%PATH%;..\tools\gbdk\bin

echo deleting old files
del obj\*.obj
del hello.gb
del hello.sym

if not exist obj md obj

echo lcc start.asm
lcc -c -o obj\start.obj src\start.asm

echo lcc main.c
lcc -c -o obj\main.obj -Igen -Iinclude src\main.c
rem lcc -S -o main.s -Igen main.c

echo lcc entity.c
lcc -c -o obj\entity.obj -Iinclude src\entity\entity.c
rem lcc -S -o entity.asm -Iinclude src\entity\entity.c

echo lcc e_player.c
lcc -c -o obj\e_player.obj -Iinclude src\entity\e_player.c

echo lcc e_projectile.c
lcc -c -o obj\e_projectile.obj -Iinclude src\entity\e_projectile.c

echo lcc world.c
lcc -c -o obj\world.obj -Igen -Iinclude src\world.c
lcc -S -o obj\world.asm -Igen -Iinclude src\world.c

echo lcc oam.c
lcc -c -o obj\oam.obj -Iinclude src\oam.c

echo lcc data
lcc -c -o obj\tiles.obj gen\tiles.c
lcc -c -o obj\maps.obj gen\maps.c

echo link
link-gbz80 -- -z -m -j -x hello.gb obj\start.obj obj\main.obj obj\tiles.obj obj\maps.obj obj\entity.obj ^
	obj\oam.obj obj\e_player.obj obj\e_projectile.obj obj\world.obj
move hello.map obj

pause
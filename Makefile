# Compile source files
gcc -ffreestanding -m32 -g -c "PurgedGL/src/purgedgl.c" -o "PurgedGL/binaries/purgedgl.o"
gcc -ffreestanding -m32 -g -c "PurgedGL/src/pgl_math.c" -o "PurgedGL/binaries/pgl_math.o"
gcc -ffreestanding -m32 -g -c "PurgedGL/src/3d.c" -o "PurgedGL/binaries/3d.o"
gcc -ffreestanding -m32 -g -c "PurgedGL/src/draw.c" -o "PurgedGL/binaries/draw.o"
gcc -ffreestanding -m32 -g -c "PurgedGL/src/light.c" -o "PurgedGL/binaries/light.o"
gcc -ffreestanding -m32 -g -c "PurgedGL/src/texture.c" -o "PurgedGL/binaries/texture.o"
gcc -ffreestanding -m32 -g -c "PurgedGL/src/video.c" -o "PurgedGL/binaries/video.o"

# Compile demos
gcc -ffreestanding -m32 -g -c "PurgedGL/demo/pyramid.c" -o "PurgedGL/binaries/demo/pyramid.o"
gcc -ffreestanding -m32 -g -c "PurgedGL/demo/texture_test.c" -o "PurgedGL/binaries/demo/texture_test.o"
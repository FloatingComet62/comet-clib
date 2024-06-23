# -O (Same as -O1)
# -O0 (do no optimization, the default if no optimization level is specified)
# -O1 (optimize minimally)
# -O2 (optimize more)
# -O3 (optimize even more)
# -Ofast (optimize very aggressively to the point of breaking standard compliance)
# -Og (Optimize debugging experience. -Og enables optimizations that do not interfere with debugging. It should be the optimization level of choice for the standard edit-compile-debug cycle, offering a reasonable level of optimization while maintaining fast compilation and a good debugging experience.)
# -Os (Optimize for size. -Os enables all -O2 optimizations that do not typically increase code size. It also performs further optimizations designed to reduce code size. -Os disables the following optimization flags: -falign-functions -falign-jumps -falign-loops -falign-labels -freorder-blocks -freorder-blocks-and-partition -fprefetch-loop-arrays -ftree-vect-loop-version)

if [[ $1 = "run" ]]; then
	echo "Running Code"
	# https://stackoverflow.com/questions/793858/how-to-mkdir-only-if-a-directory-does-not-already-exist
	mkdir -p build
	if [[ $2 = "release" ]]; then
		echo "Building Release build"
		echo "Building..."
		gcc lib/*.c main.c -Os -o build/release.exe
		echo "Running..."
		echo
		./build/release.exe
	else
		echo "Building Debug build"
		echo "Building..."
		gcc lib/*.c main.c -DCOMET_LIB_DEBUG=1 -o build/debug.exe
		echo "Running..."
		echo
		./build/debug.exe
	fi
elif [[ $1 = "build" ]]; then
	# https://stackoverflow.com/questions/793858/how-to-mkdir-only-if-a-directory-does-not-already-exist
	mkdir -p build
	if [[ $2 = "release" ]]; then
		echo "Building Release build"
		gcc lib/*.c main.c -w -Os -o build/release.exe
	else
		echo "Building Debug build"
		gcc lib/*.c main.c -DCOMET_LIB_DEBUG=1 -o build/debug.exe
	fi
elif [[ $1 = "clean" ]]; then
	echo "Cleaning Builds"
	# https://stackoverflow.com/questions/4846007/check-if-directory-exists-and-delete-in-one-command
	if [[ -d "build" ]]; then
		rm build --recursive
	fi
fi


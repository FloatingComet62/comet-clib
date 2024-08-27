# -O (Same as -O1)
# -O0 (do no optimization, the default if no optimization level is specified)
# -O1 (optimize minimally)
# -O2 (optimize more)
# -O3 (optimize even more)
# -Ofast (optimize very aggressively to the point of breaking standard compliance)
# -Og (Optimize debugging experience. -Og enables optimizations that do not interfere with debugging. It should be the optimization level of choice for the standard edit-compile-debug cycle, offering a reasonable level of optimization while maintaining fast compilation and a good debugging experience.)
# -Os (Optimize for size. -Os enables all -O2 optimizations that do not typically increase code size. It also performs further optimizations designed to reduce code size. -Os disables the following optimization flags: -falign-functions -falign-jumps -falign-loops -falign-labels -freorder-blocks -freorder-blocks-and-partition -fprefetch-loop-arrays -ftree-vect-loop-version)

help() {
	echo "run - run code in debug mode"
	echo "run release - run code in release mode"
	echo "build - build code in debug mode"
	echo "build release - build code in release mode"
	echo "test - test code in debug mode"
	echo "test release - test code in release mode"
	echo "clean - clean all the builds"
}

DEBUG_OUT=build/debug.exe
RELEASE_OUT=build/release.exe
TEST_DEBUG_OUT=build/test_debug.exe
TEST_RELEASE_OUT=build/test_release.exe

build() {
	if [[ $1 = "release" ]]; then
		if [[ $2 = "test" ]]; then
			echo "Building Release build"
			gcc tests/*.c lib/*.c main.c -DCOMET_LIB_TEST=1 -Wextra -Os -o $TEST_RELEASE_OUT
		else
			echo "Building Release build"
			gcc lib/*.c main.c -Wextra -Os -o $RELEASE_OUT 
		fi
	else
		if [[ $2 = "test" ]]; then
			echo "Building Debug build"
			gcc tests/*.c lib/*.c main.c -DCOMET_LIB_TEST=1 -DCOMET_LIB_DEBUG=1 -o $TEST_DEBUG_OUT
		else
			echo "Building Debug build"
			gcc lib/*.c main.c -DCOMET_LIB_DEBUG=1 -o $DEBUG_OUT
		fi
	fi
}

if [[ $1 = "run" ]]; then
	# https://stackoverflow.com/questions/793858/how-to-mkdir-only-if-a-directory-does-not-already-exist
	mkdir -p build
	if [[ $2 = "release" ]]; then
		build "release"
		echo "Running..."
		echo
		./$RELEASE_OUT
	else
		build "debug"
		echo "Running..."
		echo
		./$DEBUG_OUT
	fi
elif [[ $1 = "build" ]]; then
	# https://stackoverflow.com/questions/793858/how-to-mkdir-only-if-a-directory-does-not-already-exist
	mkdir -p build
	if [[ $2 = "release" ]]; then
		build "release"
	else
		build "debug"
	fi
elif [[ $1 = "test" ]]; then
	echo "Testing Code"
	if [[ $2 = "release" ]]; then
		build "release" "test"
		echo "Testing..."
		echo
		./$TEST_RELEASE_OUT
	else
		build "debug" "test"
		echo "Testing..."
		echo
		./$TEST_DEBUG_OUT
	fi
elif [[ $1 = "clean" ]]; then
	echo "Cleaning Builds"
	# https://stackoverflow.com/questions/4846007/check-if-directory-exists-and-delete-in-one-command
	if [[ -d "build" ]]; then
		rm build --recursive
	fi
elif [[ $1 = "help" ]]; then
	help
else
	help
fi

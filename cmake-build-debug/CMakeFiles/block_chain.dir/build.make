# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/default/Documents/clion-2018.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/default/Documents/clion-2018.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/default/CLionProjects/block_chain

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/default/CLionProjects/block_chain/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/block_chain.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/block_chain.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/block_chain.dir/flags.make

CMakeFiles/block_chain.dir/main.cpp.o: CMakeFiles/block_chain.dir/flags.make
CMakeFiles/block_chain.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/default/CLionProjects/block_chain/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/block_chain.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/block_chain.dir/main.cpp.o -c /home/default/CLionProjects/block_chain/main.cpp

CMakeFiles/block_chain.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/block_chain.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/default/CLionProjects/block_chain/main.cpp > CMakeFiles/block_chain.dir/main.cpp.i

CMakeFiles/block_chain.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/block_chain.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/default/CLionProjects/block_chain/main.cpp -o CMakeFiles/block_chain.dir/main.cpp.s

CMakeFiles/block_chain.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/block_chain.dir/main.cpp.o.requires

CMakeFiles/block_chain.dir/main.cpp.o.provides: CMakeFiles/block_chain.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/block_chain.dir/build.make CMakeFiles/block_chain.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/block_chain.dir/main.cpp.o.provides

CMakeFiles/block_chain.dir/main.cpp.o.provides.build: CMakeFiles/block_chain.dir/main.cpp.o


CMakeFiles/block_chain.dir/block_chain/chain/Chain.cpp.o: CMakeFiles/block_chain.dir/flags.make
CMakeFiles/block_chain.dir/block_chain/chain/Chain.cpp.o: ../block_chain/chain/Chain.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/default/CLionProjects/block_chain/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/block_chain.dir/block_chain/chain/Chain.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/block_chain.dir/block_chain/chain/Chain.cpp.o -c /home/default/CLionProjects/block_chain/block_chain/chain/Chain.cpp

CMakeFiles/block_chain.dir/block_chain/chain/Chain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/block_chain.dir/block_chain/chain/Chain.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/default/CLionProjects/block_chain/block_chain/chain/Chain.cpp > CMakeFiles/block_chain.dir/block_chain/chain/Chain.cpp.i

CMakeFiles/block_chain.dir/block_chain/chain/Chain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/block_chain.dir/block_chain/chain/Chain.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/default/CLionProjects/block_chain/block_chain/chain/Chain.cpp -o CMakeFiles/block_chain.dir/block_chain/chain/Chain.cpp.s

CMakeFiles/block_chain.dir/block_chain/chain/Chain.cpp.o.requires:

.PHONY : CMakeFiles/block_chain.dir/block_chain/chain/Chain.cpp.o.requires

CMakeFiles/block_chain.dir/block_chain/chain/Chain.cpp.o.provides: CMakeFiles/block_chain.dir/block_chain/chain/Chain.cpp.o.requires
	$(MAKE) -f CMakeFiles/block_chain.dir/build.make CMakeFiles/block_chain.dir/block_chain/chain/Chain.cpp.o.provides.build
.PHONY : CMakeFiles/block_chain.dir/block_chain/chain/Chain.cpp.o.provides

CMakeFiles/block_chain.dir/block_chain/chain/Chain.cpp.o.provides.build: CMakeFiles/block_chain.dir/block_chain/chain/Chain.cpp.o


CMakeFiles/block_chain.dir/block_chain/chain/block/transaction/Transaction.cpp.o: CMakeFiles/block_chain.dir/flags.make
CMakeFiles/block_chain.dir/block_chain/chain/block/transaction/Transaction.cpp.o: ../block_chain/chain/block/transaction/Transaction.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/default/CLionProjects/block_chain/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/block_chain.dir/block_chain/chain/block/transaction/Transaction.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/block_chain.dir/block_chain/chain/block/transaction/Transaction.cpp.o -c /home/default/CLionProjects/block_chain/block_chain/chain/block/transaction/Transaction.cpp

CMakeFiles/block_chain.dir/block_chain/chain/block/transaction/Transaction.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/block_chain.dir/block_chain/chain/block/transaction/Transaction.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/default/CLionProjects/block_chain/block_chain/chain/block/transaction/Transaction.cpp > CMakeFiles/block_chain.dir/block_chain/chain/block/transaction/Transaction.cpp.i

CMakeFiles/block_chain.dir/block_chain/chain/block/transaction/Transaction.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/block_chain.dir/block_chain/chain/block/transaction/Transaction.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/default/CLionProjects/block_chain/block_chain/chain/block/transaction/Transaction.cpp -o CMakeFiles/block_chain.dir/block_chain/chain/block/transaction/Transaction.cpp.s

CMakeFiles/block_chain.dir/block_chain/chain/block/transaction/Transaction.cpp.o.requires:

.PHONY : CMakeFiles/block_chain.dir/block_chain/chain/block/transaction/Transaction.cpp.o.requires

CMakeFiles/block_chain.dir/block_chain/chain/block/transaction/Transaction.cpp.o.provides: CMakeFiles/block_chain.dir/block_chain/chain/block/transaction/Transaction.cpp.o.requires
	$(MAKE) -f CMakeFiles/block_chain.dir/build.make CMakeFiles/block_chain.dir/block_chain/chain/block/transaction/Transaction.cpp.o.provides.build
.PHONY : CMakeFiles/block_chain.dir/block_chain/chain/block/transaction/Transaction.cpp.o.provides

CMakeFiles/block_chain.dir/block_chain/chain/block/transaction/Transaction.cpp.o.provides.build: CMakeFiles/block_chain.dir/block_chain/chain/block/transaction/Transaction.cpp.o


CMakeFiles/block_chain.dir/block_chain/Validator.cpp.o: CMakeFiles/block_chain.dir/flags.make
CMakeFiles/block_chain.dir/block_chain/Validator.cpp.o: ../block_chain/Validator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/default/CLionProjects/block_chain/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/block_chain.dir/block_chain/Validator.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/block_chain.dir/block_chain/Validator.cpp.o -c /home/default/CLionProjects/block_chain/block_chain/Validator.cpp

CMakeFiles/block_chain.dir/block_chain/Validator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/block_chain.dir/block_chain/Validator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/default/CLionProjects/block_chain/block_chain/Validator.cpp > CMakeFiles/block_chain.dir/block_chain/Validator.cpp.i

CMakeFiles/block_chain.dir/block_chain/Validator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/block_chain.dir/block_chain/Validator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/default/CLionProjects/block_chain/block_chain/Validator.cpp -o CMakeFiles/block_chain.dir/block_chain/Validator.cpp.s

CMakeFiles/block_chain.dir/block_chain/Validator.cpp.o.requires:

.PHONY : CMakeFiles/block_chain.dir/block_chain/Validator.cpp.o.requires

CMakeFiles/block_chain.dir/block_chain/Validator.cpp.o.provides: CMakeFiles/block_chain.dir/block_chain/Validator.cpp.o.requires
	$(MAKE) -f CMakeFiles/block_chain.dir/build.make CMakeFiles/block_chain.dir/block_chain/Validator.cpp.o.provides.build
.PHONY : CMakeFiles/block_chain.dir/block_chain/Validator.cpp.o.provides

CMakeFiles/block_chain.dir/block_chain/Validator.cpp.o.provides.build: CMakeFiles/block_chain.dir/block_chain/Validator.cpp.o


CMakeFiles/block_chain.dir/block_chain/Client.cpp.o: CMakeFiles/block_chain.dir/flags.make
CMakeFiles/block_chain.dir/block_chain/Client.cpp.o: ../block_chain/Client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/default/CLionProjects/block_chain/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/block_chain.dir/block_chain/Client.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/block_chain.dir/block_chain/Client.cpp.o -c /home/default/CLionProjects/block_chain/block_chain/Client.cpp

CMakeFiles/block_chain.dir/block_chain/Client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/block_chain.dir/block_chain/Client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/default/CLionProjects/block_chain/block_chain/Client.cpp > CMakeFiles/block_chain.dir/block_chain/Client.cpp.i

CMakeFiles/block_chain.dir/block_chain/Client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/block_chain.dir/block_chain/Client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/default/CLionProjects/block_chain/block_chain/Client.cpp -o CMakeFiles/block_chain.dir/block_chain/Client.cpp.s

CMakeFiles/block_chain.dir/block_chain/Client.cpp.o.requires:

.PHONY : CMakeFiles/block_chain.dir/block_chain/Client.cpp.o.requires

CMakeFiles/block_chain.dir/block_chain/Client.cpp.o.provides: CMakeFiles/block_chain.dir/block_chain/Client.cpp.o.requires
	$(MAKE) -f CMakeFiles/block_chain.dir/build.make CMakeFiles/block_chain.dir/block_chain/Client.cpp.o.provides.build
.PHONY : CMakeFiles/block_chain.dir/block_chain/Client.cpp.o.provides

CMakeFiles/block_chain.dir/block_chain/Client.cpp.o.provides.build: CMakeFiles/block_chain.dir/block_chain/Client.cpp.o


CMakeFiles/block_chain.dir/block_chain/chain/block/Block.cpp.o: CMakeFiles/block_chain.dir/flags.make
CMakeFiles/block_chain.dir/block_chain/chain/block/Block.cpp.o: ../block_chain/chain/block/Block.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/default/CLionProjects/block_chain/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/block_chain.dir/block_chain/chain/block/Block.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/block_chain.dir/block_chain/chain/block/Block.cpp.o -c /home/default/CLionProjects/block_chain/block_chain/chain/block/Block.cpp

CMakeFiles/block_chain.dir/block_chain/chain/block/Block.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/block_chain.dir/block_chain/chain/block/Block.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/default/CLionProjects/block_chain/block_chain/chain/block/Block.cpp > CMakeFiles/block_chain.dir/block_chain/chain/block/Block.cpp.i

CMakeFiles/block_chain.dir/block_chain/chain/block/Block.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/block_chain.dir/block_chain/chain/block/Block.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/default/CLionProjects/block_chain/block_chain/chain/block/Block.cpp -o CMakeFiles/block_chain.dir/block_chain/chain/block/Block.cpp.s

CMakeFiles/block_chain.dir/block_chain/chain/block/Block.cpp.o.requires:

.PHONY : CMakeFiles/block_chain.dir/block_chain/chain/block/Block.cpp.o.requires

CMakeFiles/block_chain.dir/block_chain/chain/block/Block.cpp.o.provides: CMakeFiles/block_chain.dir/block_chain/chain/block/Block.cpp.o.requires
	$(MAKE) -f CMakeFiles/block_chain.dir/build.make CMakeFiles/block_chain.dir/block_chain/chain/block/Block.cpp.o.provides.build
.PHONY : CMakeFiles/block_chain.dir/block_chain/chain/block/Block.cpp.o.provides

CMakeFiles/block_chain.dir/block_chain/chain/block/Block.cpp.o.provides.build: CMakeFiles/block_chain.dir/block_chain/chain/block/Block.cpp.o


CMakeFiles/block_chain.dir/block_chain/chain/block/Hash.cpp.o: CMakeFiles/block_chain.dir/flags.make
CMakeFiles/block_chain.dir/block_chain/chain/block/Hash.cpp.o: ../block_chain/chain/block/Hash.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/default/CLionProjects/block_chain/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/block_chain.dir/block_chain/chain/block/Hash.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/block_chain.dir/block_chain/chain/block/Hash.cpp.o -c /home/default/CLionProjects/block_chain/block_chain/chain/block/Hash.cpp

CMakeFiles/block_chain.dir/block_chain/chain/block/Hash.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/block_chain.dir/block_chain/chain/block/Hash.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/default/CLionProjects/block_chain/block_chain/chain/block/Hash.cpp > CMakeFiles/block_chain.dir/block_chain/chain/block/Hash.cpp.i

CMakeFiles/block_chain.dir/block_chain/chain/block/Hash.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/block_chain.dir/block_chain/chain/block/Hash.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/default/CLionProjects/block_chain/block_chain/chain/block/Hash.cpp -o CMakeFiles/block_chain.dir/block_chain/chain/block/Hash.cpp.s

CMakeFiles/block_chain.dir/block_chain/chain/block/Hash.cpp.o.requires:

.PHONY : CMakeFiles/block_chain.dir/block_chain/chain/block/Hash.cpp.o.requires

CMakeFiles/block_chain.dir/block_chain/chain/block/Hash.cpp.o.provides: CMakeFiles/block_chain.dir/block_chain/chain/block/Hash.cpp.o.requires
	$(MAKE) -f CMakeFiles/block_chain.dir/build.make CMakeFiles/block_chain.dir/block_chain/chain/block/Hash.cpp.o.provides.build
.PHONY : CMakeFiles/block_chain.dir/block_chain/chain/block/Hash.cpp.o.provides

CMakeFiles/block_chain.dir/block_chain/chain/block/Hash.cpp.o.provides.build: CMakeFiles/block_chain.dir/block_chain/chain/block/Hash.cpp.o


CMakeFiles/block_chain.dir/block_chain/Listener.cpp.o: CMakeFiles/block_chain.dir/flags.make
CMakeFiles/block_chain.dir/block_chain/Listener.cpp.o: ../block_chain/Listener.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/default/CLionProjects/block_chain/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/block_chain.dir/block_chain/Listener.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/block_chain.dir/block_chain/Listener.cpp.o -c /home/default/CLionProjects/block_chain/block_chain/Listener.cpp

CMakeFiles/block_chain.dir/block_chain/Listener.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/block_chain.dir/block_chain/Listener.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/default/CLionProjects/block_chain/block_chain/Listener.cpp > CMakeFiles/block_chain.dir/block_chain/Listener.cpp.i

CMakeFiles/block_chain.dir/block_chain/Listener.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/block_chain.dir/block_chain/Listener.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/default/CLionProjects/block_chain/block_chain/Listener.cpp -o CMakeFiles/block_chain.dir/block_chain/Listener.cpp.s

CMakeFiles/block_chain.dir/block_chain/Listener.cpp.o.requires:

.PHONY : CMakeFiles/block_chain.dir/block_chain/Listener.cpp.o.requires

CMakeFiles/block_chain.dir/block_chain/Listener.cpp.o.provides: CMakeFiles/block_chain.dir/block_chain/Listener.cpp.o.requires
	$(MAKE) -f CMakeFiles/block_chain.dir/build.make CMakeFiles/block_chain.dir/block_chain/Listener.cpp.o.provides.build
.PHONY : CMakeFiles/block_chain.dir/block_chain/Listener.cpp.o.provides

CMakeFiles/block_chain.dir/block_chain/Listener.cpp.o.provides.build: CMakeFiles/block_chain.dir/block_chain/Listener.cpp.o


CMakeFiles/block_chain.dir/block_chain/socket/SocketServer.cpp.o: CMakeFiles/block_chain.dir/flags.make
CMakeFiles/block_chain.dir/block_chain/socket/SocketServer.cpp.o: ../block_chain/socket/SocketServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/default/CLionProjects/block_chain/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/block_chain.dir/block_chain/socket/SocketServer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/block_chain.dir/block_chain/socket/SocketServer.cpp.o -c /home/default/CLionProjects/block_chain/block_chain/socket/SocketServer.cpp

CMakeFiles/block_chain.dir/block_chain/socket/SocketServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/block_chain.dir/block_chain/socket/SocketServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/default/CLionProjects/block_chain/block_chain/socket/SocketServer.cpp > CMakeFiles/block_chain.dir/block_chain/socket/SocketServer.cpp.i

CMakeFiles/block_chain.dir/block_chain/socket/SocketServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/block_chain.dir/block_chain/socket/SocketServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/default/CLionProjects/block_chain/block_chain/socket/SocketServer.cpp -o CMakeFiles/block_chain.dir/block_chain/socket/SocketServer.cpp.s

CMakeFiles/block_chain.dir/block_chain/socket/SocketServer.cpp.o.requires:

.PHONY : CMakeFiles/block_chain.dir/block_chain/socket/SocketServer.cpp.o.requires

CMakeFiles/block_chain.dir/block_chain/socket/SocketServer.cpp.o.provides: CMakeFiles/block_chain.dir/block_chain/socket/SocketServer.cpp.o.requires
	$(MAKE) -f CMakeFiles/block_chain.dir/build.make CMakeFiles/block_chain.dir/block_chain/socket/SocketServer.cpp.o.provides.build
.PHONY : CMakeFiles/block_chain.dir/block_chain/socket/SocketServer.cpp.o.provides

CMakeFiles/block_chain.dir/block_chain/socket/SocketServer.cpp.o.provides.build: CMakeFiles/block_chain.dir/block_chain/socket/SocketServer.cpp.o


CMakeFiles/block_chain.dir/block_chain/socket/Socket.cpp.o: CMakeFiles/block_chain.dir/flags.make
CMakeFiles/block_chain.dir/block_chain/socket/Socket.cpp.o: ../block_chain/socket/Socket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/default/CLionProjects/block_chain/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/block_chain.dir/block_chain/socket/Socket.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/block_chain.dir/block_chain/socket/Socket.cpp.o -c /home/default/CLionProjects/block_chain/block_chain/socket/Socket.cpp

CMakeFiles/block_chain.dir/block_chain/socket/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/block_chain.dir/block_chain/socket/Socket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/default/CLionProjects/block_chain/block_chain/socket/Socket.cpp > CMakeFiles/block_chain.dir/block_chain/socket/Socket.cpp.i

CMakeFiles/block_chain.dir/block_chain/socket/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/block_chain.dir/block_chain/socket/Socket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/default/CLionProjects/block_chain/block_chain/socket/Socket.cpp -o CMakeFiles/block_chain.dir/block_chain/socket/Socket.cpp.s

CMakeFiles/block_chain.dir/block_chain/socket/Socket.cpp.o.requires:

.PHONY : CMakeFiles/block_chain.dir/block_chain/socket/Socket.cpp.o.requires

CMakeFiles/block_chain.dir/block_chain/socket/Socket.cpp.o.provides: CMakeFiles/block_chain.dir/block_chain/socket/Socket.cpp.o.requires
	$(MAKE) -f CMakeFiles/block_chain.dir/build.make CMakeFiles/block_chain.dir/block_chain/socket/Socket.cpp.o.provides.build
.PHONY : CMakeFiles/block_chain.dir/block_chain/socket/Socket.cpp.o.provides

CMakeFiles/block_chain.dir/block_chain/socket/Socket.cpp.o.provides.build: CMakeFiles/block_chain.dir/block_chain/socket/Socket.cpp.o


CMakeFiles/block_chain.dir/block_chain/socket/Peer.cpp.o: CMakeFiles/block_chain.dir/flags.make
CMakeFiles/block_chain.dir/block_chain/socket/Peer.cpp.o: ../block_chain/socket/Peer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/default/CLionProjects/block_chain/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/block_chain.dir/block_chain/socket/Peer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/block_chain.dir/block_chain/socket/Peer.cpp.o -c /home/default/CLionProjects/block_chain/block_chain/socket/Peer.cpp

CMakeFiles/block_chain.dir/block_chain/socket/Peer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/block_chain.dir/block_chain/socket/Peer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/default/CLionProjects/block_chain/block_chain/socket/Peer.cpp > CMakeFiles/block_chain.dir/block_chain/socket/Peer.cpp.i

CMakeFiles/block_chain.dir/block_chain/socket/Peer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/block_chain.dir/block_chain/socket/Peer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/default/CLionProjects/block_chain/block_chain/socket/Peer.cpp -o CMakeFiles/block_chain.dir/block_chain/socket/Peer.cpp.s

CMakeFiles/block_chain.dir/block_chain/socket/Peer.cpp.o.requires:

.PHONY : CMakeFiles/block_chain.dir/block_chain/socket/Peer.cpp.o.requires

CMakeFiles/block_chain.dir/block_chain/socket/Peer.cpp.o.provides: CMakeFiles/block_chain.dir/block_chain/socket/Peer.cpp.o.requires
	$(MAKE) -f CMakeFiles/block_chain.dir/build.make CMakeFiles/block_chain.dir/block_chain/socket/Peer.cpp.o.provides.build
.PHONY : CMakeFiles/block_chain.dir/block_chain/socket/Peer.cpp.o.provides

CMakeFiles/block_chain.dir/block_chain/socket/Peer.cpp.o.provides.build: CMakeFiles/block_chain.dir/block_chain/socket/Peer.cpp.o


# Object files for target block_chain
block_chain_OBJECTS = \
"CMakeFiles/block_chain.dir/main.cpp.o" \
"CMakeFiles/block_chain.dir/block_chain/chain/Chain.cpp.o" \
"CMakeFiles/block_chain.dir/block_chain/chain/block/transaction/Transaction.cpp.o" \
"CMakeFiles/block_chain.dir/block_chain/Validator.cpp.o" \
"CMakeFiles/block_chain.dir/block_chain/Client.cpp.o" \
"CMakeFiles/block_chain.dir/block_chain/chain/block/Block.cpp.o" \
"CMakeFiles/block_chain.dir/block_chain/chain/block/Hash.cpp.o" \
"CMakeFiles/block_chain.dir/block_chain/Listener.cpp.o" \
"CMakeFiles/block_chain.dir/block_chain/socket/SocketServer.cpp.o" \
"CMakeFiles/block_chain.dir/block_chain/socket/Socket.cpp.o" \
"CMakeFiles/block_chain.dir/block_chain/socket/Peer.cpp.o"

# External object files for target block_chain
block_chain_EXTERNAL_OBJECTS =

block_chain: CMakeFiles/block_chain.dir/main.cpp.o
block_chain: CMakeFiles/block_chain.dir/block_chain/chain/Chain.cpp.o
block_chain: CMakeFiles/block_chain.dir/block_chain/chain/block/transaction/Transaction.cpp.o
block_chain: CMakeFiles/block_chain.dir/block_chain/Validator.cpp.o
block_chain: CMakeFiles/block_chain.dir/block_chain/Client.cpp.o
block_chain: CMakeFiles/block_chain.dir/block_chain/chain/block/Block.cpp.o
block_chain: CMakeFiles/block_chain.dir/block_chain/chain/block/Hash.cpp.o
block_chain: CMakeFiles/block_chain.dir/block_chain/Listener.cpp.o
block_chain: CMakeFiles/block_chain.dir/block_chain/socket/SocketServer.cpp.o
block_chain: CMakeFiles/block_chain.dir/block_chain/socket/Socket.cpp.o
block_chain: CMakeFiles/block_chain.dir/block_chain/socket/Peer.cpp.o
block_chain: CMakeFiles/block_chain.dir/build.make
block_chain: CMakeFiles/block_chain.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/default/CLionProjects/block_chain/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable block_chain"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/block_chain.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/block_chain.dir/build: block_chain

.PHONY : CMakeFiles/block_chain.dir/build

CMakeFiles/block_chain.dir/requires: CMakeFiles/block_chain.dir/main.cpp.o.requires
CMakeFiles/block_chain.dir/requires: CMakeFiles/block_chain.dir/block_chain/chain/Chain.cpp.o.requires
CMakeFiles/block_chain.dir/requires: CMakeFiles/block_chain.dir/block_chain/chain/block/transaction/Transaction.cpp.o.requires
CMakeFiles/block_chain.dir/requires: CMakeFiles/block_chain.dir/block_chain/Validator.cpp.o.requires
CMakeFiles/block_chain.dir/requires: CMakeFiles/block_chain.dir/block_chain/Client.cpp.o.requires
CMakeFiles/block_chain.dir/requires: CMakeFiles/block_chain.dir/block_chain/chain/block/Block.cpp.o.requires
CMakeFiles/block_chain.dir/requires: CMakeFiles/block_chain.dir/block_chain/chain/block/Hash.cpp.o.requires
CMakeFiles/block_chain.dir/requires: CMakeFiles/block_chain.dir/block_chain/Listener.cpp.o.requires
CMakeFiles/block_chain.dir/requires: CMakeFiles/block_chain.dir/block_chain/socket/SocketServer.cpp.o.requires
CMakeFiles/block_chain.dir/requires: CMakeFiles/block_chain.dir/block_chain/socket/Socket.cpp.o.requires
CMakeFiles/block_chain.dir/requires: CMakeFiles/block_chain.dir/block_chain/socket/Peer.cpp.o.requires

.PHONY : CMakeFiles/block_chain.dir/requires

CMakeFiles/block_chain.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/block_chain.dir/cmake_clean.cmake
.PHONY : CMakeFiles/block_chain.dir/clean

CMakeFiles/block_chain.dir/depend:
	cd /home/default/CLionProjects/block_chain/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/default/CLionProjects/block_chain /home/default/CLionProjects/block_chain /home/default/CLionProjects/block_chain/cmake-build-debug /home/default/CLionProjects/block_chain/cmake-build-debug /home/default/CLionProjects/block_chain/cmake-build-debug/CMakeFiles/block_chain.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/block_chain.dir/depend


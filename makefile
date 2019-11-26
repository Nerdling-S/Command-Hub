CXX = g++-8
CXXFLAGS = -Wall -g -std=c++17
LDLIBS = -lncurses -lstdc++fs
SRCOBJ := $(patsubst ./src/%.cpp,./obj/%.o,$(wildcard ./src/*.cpp))
LIBOBJ := $(patsubst ./src/libs/%.cpp,./obj/libs/%.o,$(wildcard ./src/libs/*.cpp))

command-hub: $(SRCOBJ) $(LIBOBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

./obj/hub.o: ./src/hub.cpp ./src/commands.hpp ./src/libs/lang.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

./obj/%.o: ./src/%.cpp ./src/%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	${RM} /obj/*.o && $(RM) obj/libs/*.o
CXXFLAGS = -Wall -g
LDLIBS = -lncurses
OBJ := $(patsubst %.cpp,obj/%.o,$(wildcard src/*.cpp))
LIB := $(patsubst %.cpp,obj/libs/%.o,$(wildcard src/libs/*.cpp))

command-hub: $(OBJ) $(LIB)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

/obj/%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	${RM} /obj/*.o && $(RM) obj/libs/*.o
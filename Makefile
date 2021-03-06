CXXFLAGS = -std=c++17 -O2

src = \
	util/string.cpp \
	io.cpp \
	main.cpp
objs = $(addprefix build/,$(src:.cpp=.o))
 
dice: $(objs)
	$(CXX) $(CXXFLAGS) $(objs) -o dice

$(objs): build/%.o: source/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $(CXXFLAGS) $< -o $@

build/io.o: source/info.hpp

clean:
	rm -f dice
	rm -fr build/

.PHONY: clean

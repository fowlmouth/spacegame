SRC := $(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
OBJ := $(SRC:.cpp=.o)

IMGUI_SRC := $(wildcard deps/imgui/*.cpp) $(wildcard deps/imgui-sfml/*.cpp)
IMGUI_OBJ := $(IMGUI_SRC:.cpp=.o)
LIBIMGUI  := libimgui.a

EDYN_SRC := $(wildcard deps/edyn/src/*.cpp) $(wildcard deps/edyn/src/**/*.cpp)
EDYN_OBJ := $(EDYN_SRC:.cpp=.o)
LIBEDYN  := libedyn.a
EDYN_HEADER := deps/edyn/include/edyn/build_settings.h

BIN := spacegame

CXXFLAGS := -std=c++20 -Iinclude/ -Ideps/entt/src -Ideps/imgui/ -Ideps/imgui-sfml/ -Ideps/imgui_entt_entity_editor/ -Ideps/edyn/include $(shell pkg-config --cflags sfml-graphics)
LDLIBS := $(shell pkg-config --libs sfml-graphics) -L. -limgui -ledyn

ASSETS_TAR := spacegame-assets.tgz
ASSETS_URL := "https://www.dropbox.com/s/6bjba6qzwlgs38b/spacegame-assets.tgz?dl=1"

ifeq ($(OS),Windows_NT)

else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		LDLIBS += -lGL
	else ifeq ($(UNAME_S),Darwin)
		CXXFLAGS += -DGL_SILENCE_DEPRECATION
		LDLIBS += -framework OpenGL
	endif
endif

ALL: $(BIN)
.PHONY: debug clean cleanall run bundle-assets init

debug: CXXFLAGS += -g
debug: $(BIN)

$(BIN): $(OBJ) $(LIBIMGUI) $(LIBEDYN)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)

run: $(BIN) assets
	./$(BIN)

clean:
	rm -f $(OBJ) $(IMGUI_OBJ) $(LIBIMGUI) $(EDYN_OBJ) $(LIBEDYN) deps/edyn/include/edyn/build_settings.h

cleanall: clean
	rm -f $(BIN) assets/ "$(ASSETS_TAR)"

bundle-assets:
	tar czvf $(ASSETS_TAR) assets/

$(ASSETS_TAR):
	curl -sL "$(ASSETS_URL)" -o "$(ASSETS_TAR)"

assets: $(ASSETS_TAR)
	tar xzvf $(ASSETS_TAR)

init: assets
	git submodule update --init

$(LIBIMGUI): $(IMGUI_OBJ)
	ar rvs $@ $^

$(EDYN_HEADER):
	sed 's/#cmakedefine /#define /' deps/edyn/cmake/in/build_settings.h.in > $@

$(LIBEDYN): $(EDYN_HEADER) $(EDYN_OBJ)
	ar rvs $@ $(EDYN_OBJ)

%.o: %.cpp $(EDYN_HEADER)
	$(CXX) $(CXXFLAGS) -c $< -o $@
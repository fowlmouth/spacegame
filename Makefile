SRC := $(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
OBJ := $(SRC:.cpp=.o)

IMGUI_SRC := $(wildcard deps/imgui/*.cpp) $(wildcard deps/imgui-sfml/*.cpp)
IMGUI_OBJ := $(IMGUI_SRC:.cpp=.o)
LIBIMGUI := libimgui.a

BIN := spacegame

CXXFLAGS := -std=c++20 -Iinclude/ -Ideps/entt/single_include -Ideps/imgui/ -Ideps/imgui-sfml/ -Ideps/imgui_entt_entity_editor/ $(shell pkg-config --cflags sfml-graphics)
LDLIBS := $(shell pkg-config --libs sfml-graphics) -L. -limgui

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

$(BIN): $(OBJ) $(LIBIMGUI)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)

run: $(BIN) assets
	./$(BIN)

clean:
	rm -f $(OBJ)

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

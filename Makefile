SRC := $(wildcard src/*.cpp) $(wildcard src/**/*.cpp) $(wildcard imgui/*.cpp) $(wildcard imgui-sfml/*.cpp)
OBJ := $(SRC:.cpp=.o)

BIN := spacegame

CXXFLAGS := -std=c++20 -Iinclude/ -Ientt/single_include -Iimgui/ -Iimgui-sfml/ $(shell pkg-config --cflags sfml-graphics)
LDLIBS := $(shell pkg-config --libs sfml-graphics) -framework OpenGL

ASSETS_TAR := spacegame-assets.tgz
ASSETS_URL := "https://www.dropbox.com/s/6bjba6qzwlgs38b/spacegame-assets.tgz?dl=1"

ALL: $(BIN)
.PHONY: debug clean cleanall run

debug: CXXFLAGS += -g
debug: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

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

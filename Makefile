SRC := $(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
OBJ := $(SRC:.cpp=.o)

BIN := spacegame

CXXFLAGS := -std=c++20 -Iinclude/ -Ientt/single_include $(shell pkg-config --cflags sfml-graphics)
LDLIBS := $(shell pkg-config --libs sfml-graphics)

ASSETS_TAR := spacegame-assets.tgz
ASSETS_URL := "https://www.dropbox.com/s/kc992wfsj3xqdd7/spacegame-assets.tgz?dl=1"

ALL: $(BIN)
.PHONY: clean cleanall run xx

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

entt:
	git submodule update --init

bundle-assets:
	tar czvf $(ASSETS_TAR) assets/

$(ASSETS_TAR):
	curl -sL "$(ASSETS_URL)" -o "$(ASSETS_TAR)"

assets: $(ASSETS_TAR)
	tar xzvf $(ASSETS_TAR)

TGUI-0.9.5:
	curl -sL https://github.com/texus/TGUI/archive/v0.9.5.zip | bsdtar -xf-
	mkdir TGUI-0.9.5/build
	cd TGUI-0.9.5/build
	cmake -DCMAKE_OSX_ARCHITECTURES=arm64 ..
	$(MAKE)

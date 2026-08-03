EE_BIN = amongus.elf

CXX = mips64r5900el-ps2-elf-g++
PS2SDK ?= /usr/local/ps2dev/ps2sdk

EE_OBJS = \
	src/main.o \
	src/game.o

EE_INCS = \
	-I./tyra/inc \
	-I/usr/include \
	-I/usr/include/libpng16 \
	-I$(PS2SDK)/ee/include \
	-I$(PS2SDK)/common/include

EE_CXXFLAGS = \
	-D_EE \
	-G0 \
	-O2 \
	-Wall \
	$(EE_INCS)

EE_LDFLAGS = \
	-ltyra \
	-lpng \
	-lz \
	-lpatches \
	-lgskit \
	-ldma \
	-lgraph \
	-ldraw \
	-lpacket

all: $(EE_BIN)

$(EE_BIN): $(EE_OBJS)
	$(CXX) $(EE_CXXFLAGS) -o $@ $^ $(EE_LDFLAGS)

src/main.o: src/main.cpp
	$(CXX) $(EE_CXXFLAGS) -c $< -o $@

src/game.o: src/game.cpp
	$(CXX) $(EE_CXXFLAGS) -c $< -o $@

clean:
	rm -f $(EE_OBJS) $(EE_BIN)

.PHONY: all clean

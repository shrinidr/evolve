CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g -I.
LDFLAGS  :=

BUILD_DIR := build
TARGET    := argan

SRCS := main.cpp \
        loader/loader.cpp \
        analyzer/analyzer.cpp \
        executor/executor.cpp

OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

run: $(TARGET)
	./$(TARGET) run $(ARGS)

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TARGET).exe

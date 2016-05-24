BIN_NAMES = poolgame

poolgame_SOURCES = main.cpp BilliardBall.cpp Table.cpp \
				   mathUtility.cpp


CXX = g++
CXX_FLAGS = -std=c++11 -Wall -g -O2
LINK_FLAGS = -g -O2

BUILD_PATH = build

.PHONY: all
all: $(BIN_NAMES)

$(BUILD_PATH):
	@echo "Creating directory: $@"
	@mkdir -p $@

$(BUILD_PATH)/%.o: %.cpp | $(BUILD_PATH)
	@echo "Compiling: $< -> $@"
	@$(CXX) $(CXX_FLAGS) -MP -MMD -c -o $@ $<

$(BIN_NAMES):
	@echo "Linking: $@"
	@$(CXX) $(LINK_FLAGS) $($@_OBJS) -o $@

define BIN_T
 $(1)_OBJS = $$($(1)_SOURCES:%.cpp=$$(BUILD_PATH)/%.o)
 $(1): $$($(1)_OBJS)
 SOURCES += $$($(1)_SOURCES)
 OBJECTS += $$($(1)_OBJS)
endef

$(foreach BIN,$(BIN_NAMES),$(eval $(call BIN_T,$(BIN))))

DEP_FILES = $(OBJECTS:.o=.d)
-include $(DEP_FILES)

.PHONY: clean
clean:
	@$(RM) -r $(BIN_NAMES) $(BUILD_PATH)

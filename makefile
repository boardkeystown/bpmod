# cpp settings
CXX        :=g++
CXXFLAGS   :=--std=c++17 -pipe -fPIC -MMD -MP 
CXXFLAGS   +=-Wall -Werror 
CXXFLAGS   +=-Werror=return-type
CXXFLAGS   +=-Wextra
#CXXFLAGS   +=-fsanitize=leak
#CXXFLAGS   +=-fsanitize=address 
#CXXFLAGS   +=-fno-omit-frame-pointer
CXXFLAGS   +=-Wuninitialized 
CXXFLAGS   +=-Wmaybe-uninitialized

CXXFLAGS   +=-Og -g
CXXLDFLAGS := #

# targets
MAIN_TARGET_BASENAME :=main
MAIN_TARGET          :=$(MAIN_TARGET_BASENAME).e

BPMOD_BASENAME    :=bpmod
BPMOD_TARGET      :=$(BPMOD_BASENAME).so
BPMOD_STUB_TARGET :=$(BPMOD_BASENAME).pyi

# structure and sources
PROJECT_DIR       :=$(CURDIR)
MAIN_DIR          :=$(PROJECT_DIR)/src
OBJECTS_DIR       :=$(PROJECT_DIR)/.objects
BPMOD_DIR         :=$(PROJECT_DIR)/bpmod_src
TEST_SCRIPTS      :=pyscripts

_MK_DIRS :=$(shell mkdir -pv $(OBJECTS_DIR))

SPACE := #this is the
SPACE += # space trick
define FIND_DIRS
$(subst $(SPACE),:,$(shell find $(1) -type d))
endef

VPATH :=$(PROJECT_DIR):\
        $(OBJECTS_DIR):\
        $(call FIND_DIRS, $(MAIN_DIR)): \
        $(call FIND_DIRS, $(BPMOD_DIR))

# libraries

BOOST_INC :=/home/blackbox/b_1_82_0_install/include
BOOST_LIB :=/home/blackbox/b_1_82_0_install/lib
BOOST_FLAGS   :=-I$(BOOST_INC)
BOOST_LDFLAGS :=-Wl,-rpath,$(BOOST_LIB) -L$(BOOST_LIB)
BOOST_LDLIBS  :=-lboost_system \
                -lboost_filesystem \
                -lboost_python38

PYTHON_INC     :=/usr/include/python3.8
PYTHON_LIB     :=/usr/lib/python3.8
PYTHON_FLAGS   :=-I$(PYTHON_INC)
PYTHON_GNU     :=/usr/lib/python3.8/config-3.8-x86_64-linux-gnu
PYTHON_LDFLAGS :=-Wl,-rpath,$(PYTHON_LIB) -L$(PYTHON_LIB) \
                 -Wl,-rpath,$(PYTHON_GNU) -L$(PYTHON_GNU)
PYTHON_LDLIBS  :=-lpython3.8

CXXFLAGS +=-I$(MAIN_DIR) \
           -I$(PROJECT_DIR) \
           -I$(BPMOD_DIR) \
             $(BOOST_FLAGS) \
             $(PYTHON_FLAGS)

CXXLDFLAGS +=$(BOOST_LDFLAGS) $(BOOST_LDLIBS) \
             $(PYTHON_LDFLAGS) $(PYTHON_LDLIBS)
CXXLDFLAGS +=-ldl -lstdc++
# cpp src
define RWILDCARD
$(foreach d,$(wildcard $(1:=/*)),$(call RWILDCARD,$(d),$(2))$(filter $(subst *,%,$(2)),$(d)))
endef

# cpp src

MAIN_CPP_SRC   :=$(call RWILDCARD,$(MAIN_DIR),*.cpp)

BPMOD_CPP_SRC :=$(call RWILDCARD,$(BPMOD_DIR),*.cpp)

# cpp objects
MAIN_CPP_OBJ   :=$(addprefix $(OBJECTS_DIR)/,$(notdir $(MAIN_CPP_SRC:.cpp=.o)))

BPMOD_CPP_OBJ :=$(addprefix $(OBJECTS_DIR)/,$(notdir $(BPMOD_CPP_SRC:.cpp=.o)))

.PHONEY: default bpmodso stub all clean info 

default: $(MAIN_TARGET)

all: $(MAIN_TARGET) $(BPMOD_TARGET) stub
# mk main test program
$(MAIN_TARGET): $(MAIN_CPP_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(CXXLDFLAGS)

$(OBJECTS_DIR)/%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
# mk the boost python shared lib 
bpmodso: $(BPMOD_TARGET)
$(BPMOD_TARGET): $(BPMOD_CPP_OBJ)
	$(CXX)  $(CXXFLAGS) -shared -export-dynamic $^ -o $@ $(CXXLDFLAGS)
	cp $(BPMOD_TARGET) $(PROJECT_DIR)/$(TEST_SCRIPTS)/$(BPMOD_TARGET)
# mk module stub file
stub: $(BPMOD_TARGET) | $(BPMOD_TARGET)
	$(RM) -v $(BPMOD_STUB_TARGET) $(PROJECT_DIR)/$(BPMOD_STUB_TARGET)
	stubgen -v -m $(BPMOD_BASENAME) -o .
	cp $(BPMOD_STUB_TARGET) $(PROJECT_DIR)/$(TEST_SCRIPTS)/$(BPMOD_STUB_TARGET)

clean:
	$(RM) -v $(MAIN_TARGET)
	$(RM) -v $(BPMOD_TARGET)
	$(RM) -v $(OBJECTS_DIR)/*
	$(RM) -v $(BPMOD_STUB_TARGET) $(PROJECT_DIR)/$(BPMOD_STUB_TARGET)
	$(RM) -v $(PROJECT_DIR)/$(TEST_SCRIPTS)/$(BPMOD_STUB_TARGET)
	$(RM) -v $(PROJECT_DIR)/$(TEST_SCRIPTS)/$(BPMOD_TARGET)

info:
	@echo $(BPMOD_CPP_OBJ)
	@echo $(BPMOD_CPP_SRC)

DEPENDENCIES :=$(wildcard $(OBJECTS_DIR)/*.d)
-include $(DEPENDENCIES)

##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Servitor3D
ConfigurationName      :=Debug
WorkspacePath          :=C:/Users/James/code/Servitor/build/codelite/servitor
ProjectPath            :=C:/Users/James/code/Servitor/threedee
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=James
Date                   :=22/07/2019
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/msys64/mingw64/bin/g++.exe
SharedObjectLinkerName :=C:/msys64/mingw64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=../bin/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="Servitor3D.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/msys64/mingw64/bin/windres.exe
LinkOptions            :=  -static -m64 -static-libstdc++ -static-libgcc
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)C:\Users\James\code\raven-set $(IncludeSwitch)C:\Users\James\code\boost\boost_1_70_0 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)boost_system-mgw82-mt-x64-1_70 $(LibrarySwitch)boost_thread-mgw82-mt-x64-1_70 
ArLibs                 :=  "libboost_system-mgw82-mt-x64-1_70.a" "libboost_thread-mgw82-mt-x64-1_70.a" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)C:\Users\James\code\boost\boost_1_70_0\stage\lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/msys64/mingw64/bin/ar.exe rcu
CXX      := C:/msys64/mingw64/bin/g++.exe
CC       := C:/msys64/mingw64/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/msys64/mingw64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/cServitor.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_raven-set_cRunWatch.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/cServitor.cpp$(ObjectSuffix): cServitor.cpp $(IntermediateDirectory)/cServitor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/James/code/Servitor/threedee/cServitor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cServitor.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cServitor.cpp$(DependSuffix): cServitor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cServitor.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/cServitor.cpp$(DependSuffix) -MM cServitor.cpp

$(IntermediateDirectory)/cServitor.cpp$(PreprocessSuffix): cServitor.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cServitor.cpp$(PreprocessSuffix) cServitor.cpp

$(IntermediateDirectory)/up_up_raven-set_cRunWatch.cpp$(ObjectSuffix): ../../raven-set/cRunWatch.cpp $(IntermediateDirectory)/up_up_raven-set_cRunWatch.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/James/code/raven-set/cRunWatch.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_raven-set_cRunWatch.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_raven-set_cRunWatch.cpp$(DependSuffix): ../../raven-set/cRunWatch.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_raven-set_cRunWatch.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_raven-set_cRunWatch.cpp$(DependSuffix) -MM ../../raven-set/cRunWatch.cpp

$(IntermediateDirectory)/up_up_raven-set_cRunWatch.cpp$(PreprocessSuffix): ../../raven-set/cRunWatch.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_raven-set_cRunWatch.cpp$(PreprocessSuffix) ../../raven-set/cRunWatch.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/James/code/Servitor/threedee/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/



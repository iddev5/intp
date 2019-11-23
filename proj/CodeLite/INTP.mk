##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=INTP
ConfigurationName      :=Release
WorkspacePath          :=/home/ayush/Documents/Projects/INTP/INTP/proj/CodeLite
ProjectPath            :=/home/ayush/Documents/Projects/INTP/INTP/proj/CodeLite
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Ayush
Date                   :=23/11/19
CodeLitePath           :=/home/ayush/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="INTP.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -O2 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/up_up_src_lexer.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_main.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_intp.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_parser.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_sds_sds.c$(ObjectSuffix) 



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
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/up_up_src_lexer.c$(ObjectSuffix): ../../src/lexer.c $(IntermediateDirectory)/up_up_src_lexer.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/ayush/Documents/Projects/INTP/INTP/src/lexer.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_lexer.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_lexer.c$(DependSuffix): ../../src/lexer.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_lexer.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_lexer.c$(DependSuffix) -MM ../../src/lexer.c

$(IntermediateDirectory)/up_up_src_lexer.c$(PreprocessSuffix): ../../src/lexer.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_lexer.c$(PreprocessSuffix) ../../src/lexer.c

$(IntermediateDirectory)/up_up_src_main.c$(ObjectSuffix): ../../src/main.c $(IntermediateDirectory)/up_up_src_main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/ayush/Documents/Projects/INTP/INTP/src/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_main.c$(DependSuffix): ../../src/main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_main.c$(DependSuffix) -MM ../../src/main.c

$(IntermediateDirectory)/up_up_src_main.c$(PreprocessSuffix): ../../src/main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_main.c$(PreprocessSuffix) ../../src/main.c

$(IntermediateDirectory)/up_up_src_intp.c$(ObjectSuffix): ../../src/intp.c $(IntermediateDirectory)/up_up_src_intp.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/ayush/Documents/Projects/INTP/INTP/src/intp.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_intp.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_intp.c$(DependSuffix): ../../src/intp.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_intp.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_intp.c$(DependSuffix) -MM ../../src/intp.c

$(IntermediateDirectory)/up_up_src_intp.c$(PreprocessSuffix): ../../src/intp.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_intp.c$(PreprocessSuffix) ../../src/intp.c

$(IntermediateDirectory)/up_up_src_parser.c$(ObjectSuffix): ../../src/parser.c $(IntermediateDirectory)/up_up_src_parser.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/ayush/Documents/Projects/INTP/INTP/src/parser.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_parser.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_parser.c$(DependSuffix): ../../src/parser.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_parser.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_parser.c$(DependSuffix) -MM ../../src/parser.c

$(IntermediateDirectory)/up_up_src_parser.c$(PreprocessSuffix): ../../src/parser.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_parser.c$(PreprocessSuffix) ../../src/parser.c

$(IntermediateDirectory)/up_up_src_sds_sds.c$(ObjectSuffix): ../../src/sds/sds.c $(IntermediateDirectory)/up_up_src_sds_sds.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/ayush/Documents/Projects/INTP/INTP/src/sds/sds.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_sds_sds.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_sds_sds.c$(DependSuffix): ../../src/sds/sds.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_sds_sds.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_sds_sds.c$(DependSuffix) -MM ../../src/sds/sds.c

$(IntermediateDirectory)/up_up_src_sds_sds.c$(PreprocessSuffix): ../../src/sds/sds.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_sds_sds.c$(PreprocessSuffix) ../../src/sds/sds.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/



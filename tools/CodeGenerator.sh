

namespace="WeAP"
#subNamespace="System"
subNamespace="Framework"

author="xzwang"
curDate=`date -d "0 day ago" "+%Y-%m-%d"`


GenerateHeadFile()
{    
    echo "#ifndef __WeAP_${className}_H__"                          > $headFile
    echo "#define __WeAP_${className}_H__"                         >> $headFile
    echo ""                                                        >> $headFile    
    echo "#include \"${parentClassName}.h\""                       >> $headFile  
    echo ""                                                        >> $headFile
    echo "namespace ${namespace} { namespace ${subNamespace} {"    >> $headFile
    echo ""                                                        >> $headFile
    echo "/**"                                                     >> $headFile
    echo " * "                                                     >> $headFile
    echo " * "                                                     >> $headFile
    echo " * @author ${author}"                                    >> $headFile
    echo " * @date ${curDate}"                                     >> $headFile	
    echo " */"                                                     >> $headFile
    echo "class ${className} : public ${parentClassName}"          >> $headFile
    echo "{"                                                       >> $headFile
    echo "public:"                                                 >> $headFile
    echo "    ${className}();"                                     >> $headFile
    echo "    virtual ~${className}();"                            >> $headFile	
    echo ""                                                        >> $headFile	
    echo ""                                                        >> $headFile	
    echo "private:"                                                >> $headFile
    echo "    ${className}(const ${className}& other);"            >> $headFile
	echo "    ${className}& operator=(const ${className}& other);" >> $headFile	
    echo ""                                                        >> $headFile
	echo "    void Init(const ${className}& other);"               >> $headFile
    echo ""                                                        >> $headFile	
    echo "protected:"                                              >> $headFile
    echo ""                                                        >> $headFile
    echo "};"                                                      >> $headFile
    echo ""                                                        >> $headFile
    echo "}}"                                                      >> $headFile
    echo ""                                                        >> $headFile
    echo ""                                                        >> $headFile
    echo "#endif //__WeAP_${className}_H__"                        >> $headFile
	echo ""                                                        >> $headFile
    
	echo "GenerateFile OK! ---$headFile"
}

GenerateCppFile()
{	
    echo ""                                                                  > $cppFile    
    echo "#include \"${className}.h\""                                      >> $cppFile 
    echo ""                                                                 >> $cppFile
    echo ""                                                                 >> $cppFile
    echo ""                                                                 >> $cppFile
    echo "namespace ${namespace} { namespace ${subNamespace} {"             >> $cppFile
    echo ""                                                                 >> $cppFile
    echo ""                                                                 >> $cppFile
    echo ""                                                                 >> $cppFile
    echo "${className}::${className}()"                                     >> $cppFile
    echo "{"                                                                >> $cppFile
    echo "}"                                                                >> $cppFile
    echo ""                                                                 >> $cppFile
    echo "${className}::${className}(const ${className}& other)"            >> $cppFile
    echo "{"                                                                >> $cppFile
    echo "    this->Init(other);"                                           >> $cppFile
    echo "}"                                                                >> $cppFile
    echo ""                                                                 >> $cppFile
    echo "${className}::~${className}()"                                    >> $cppFile
    echo "{"                                                                >> $cppFile
    echo "}"                                                                >> $cppFile
    echo ""                                                                 >> $cppFile
    echo "${className}& ${className}::operator=(const ${className}& other)" >> $cppFile
    echo "{"                                                                >> $cppFile
    echo "    if(this == &other)"                                           >> $cppFile
    echo "    {"                                                            >> $cppFile
    echo "        return *this;"                                            >> $cppFile
    echo "    }"                                                            >> $cppFile
    echo ""                                                                 >> $cppFile
    echo "    this->Init(other);"                                           >> $cppFile
    echo ""                                                                 >> $cppFile
    echo "    return *this;"                                                >> $cppFile	
    echo "}"                                                                >> $cppFile
    echo ""                                                                 >> $cppFile
    echo "void ${className}::Init(const ${className}& other)"               >> $cppFile
    echo "{"                                                                >> $cppFile
    echo "    /// @todo impl"                                               >> $cppFile
    echo "}"                                                                >> $cppFile	
    echo ""                                                                 >> $cppFile
    echo ""                                                                 >> $cppFile
    echo "}}"                                                               >> $cppFile
    
	echo "GenerateFile OK! ---$cppFile"
}


GenerateTestHeadFile()
{    
    echo "#ifndef __WeAP_${className}Test_H__"                     > $testHeadFile
    echo "#define __WeAP_${className}Test_H__"                    >> $testHeadFile
    echo ""                                                       >> $testHeadFile
    echo "#include \"${parentClassName}Test.h\""                  >> $testHeadFile          
    echo ""                                                       >> $testHeadFile
    echo "/**"                                                    >> $testHeadFile
    echo " * "                                                    >> $testHeadFile
    echo " * "                                                    >> $testHeadFile
    echo " * @author ${author}"                                   >> $testHeadFile
    echo " * @date ${curDate}"                                    >> $testHeadFile	
    echo " */"                                                    >> $testHeadFile
    echo "class ${className}Test : public ${parentClassName}Test" >> $testHeadFile
    echo "{"                                                      >> $testHeadFile
    echo "public:"                                                >> $testHeadFile
    echo "    ${className}Test();"                                >> $testHeadFile
    echo "    virtual ~${className}Test();"                       >> $testHeadFile
    echo ""                                                       >> $testHeadFile
    echo "    void Test();"                                       >> $testHeadFile
    echo ""                                                       >> $testHeadFile
    echo "protected:"                                             >> $testHeadFile
    echo ""                                                       >> $testHeadFile
    echo "};"                                                     >> $testHeadFile
    echo ""                                                       >> $testHeadFile
    echo ""                                                       >> $testHeadFile
    echo "#endif //__WeAP_${className}Test_H__"                   >> $testHeadFile
    
	echo "GenerateFile OK! ---$testHeadFile"
}


GenerateTestCppFile()
{    
    echo "#include \"${className}Test.h\""               > $testCppFile 
    echo ""                                             >> $testCppFile
    echo ""                                             >> $testCppFile
    echo ""                                             >> $testCppFile
    echo "${className}Test::${className}Test()"         >> $testCppFile
    echo "{"                                            >> $testCppFile
    echo "}"                                            >> $testCppFile
    echo ""                                             >> $testCppFile
    echo "${className}Test::~${className}Test()"        >> $testCppFile
    echo "{"                                            >> $testCppFile    
    echo "}"                                            >> $testCppFile
    echo ""                                             >> $testCppFile
    echo "void ${className}Test::Test()"                >> $testCppFile
    echo "{"                                            >> $testCppFile
    echo ""                                             >> $testCppFile
    echo "}"                                            >> $testCppFile
    echo ""                                             >> $testCppFile
    echo ""                                             >> $testCppFile
    echo ""                                             >> $testCppFile 
    echo "TEST_F(${className}Test, Test)"               >> $testCppFile
    echo "{"                                            >> $testCppFile
    echo "    Test();"                                  >> $testCppFile
    echo "}"                                            >> $testCppFile
    
	echo "GenerateFile OK! ---$testCppFile"
}

CodeGenerator()
{
    className="$1";
    parentClassName="$2"
    path="$3"
    
    headFile="${path}${className}.h"
    cppFile="${path}${className}.cpp"   
    
    testHeadFile="${path}${className}Test.h"
    testCppFile="${path}${className}Test.cpp"
    	
	GenerateHeadFile 
	GenerateCppFile
	GenerateTestHeadFile
	GenerateTestCppFile
	
	echo
	echo
}


if [ "$1" != "" ]; then
	className=$1
else
	echo "useage: sh CodeGenerator ClassName [ParentClassName] [Path]"
	exit 1
fi

if [ "$2" != "" ]; then
	parentClassName=$2
else
	parentClassName="Object"
fi

if [ "$3" != "" ]; then
	path=$3
else
	path="./src/"
fi


CodeGenerator ${className} ${parentClassName} ${path}



exit 0


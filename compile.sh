#!/bin/sh
function compile()
{
    mkdir -p build
    cd build
    echo "génération du makefile ..."
    qmake -makefile ../src/project.pro > /dev/null
    echo "compilation ..."
    make > /dev/null
    if [ $? -gt 0 ]
    then echo "erreur de compilation"
        exit 1
    fi
    return
}



if [ $# -eq 0 ]
then
    compile
elif [ $1 == "run" ]
then
    ./build/project
elif [ $1 == "test" ]
then
    
    compile
    echo "lancement ..."
    ./project
    
fi

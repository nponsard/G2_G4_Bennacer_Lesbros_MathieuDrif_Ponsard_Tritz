#!/bin/bash
cd ../ressources
echo $PWD
while [ -f running ];
    do aplay 'theme.wav' 
done

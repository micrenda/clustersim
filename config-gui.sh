#!/bin/sh

if [ -e  util/clustersim-gui/target/clustersim-gui-*-jar-with-dependencies.jar ]
then
  java -jar util/clustersim-gui/target/clustersim-gui-*-jar-with-dependencies.jar $*
else
  echo "You have to compile 'clustersim-gui'."
  echo "Have a look inside the directory: util/clustersim-gui/"
fi

#!/bin/sh

cd lib/libconfig-master/libconfig/
mvn clean install
cd ../../../
mvn clean package

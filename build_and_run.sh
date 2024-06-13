#!/bin/sh

echo "Baue Server..." &&
cd ./server &&
./build.sh &&
echo "Fertig!" &&

echo "Baue Client..." &&
cd ../client &&
./build.sh &&
echo "Fertig!" &&

echo "Starte Server (Asynchron)..." &&
cd ../server &&
(./forscher &) &&
echo "Fertig!" &&

echo "Starte Client..." &&
cd ../client &&
wine forscher.exe

echo "Stoppe Server..." &&
killall forscher &&
echo "Fertig!"
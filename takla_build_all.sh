#!/bin/bash

cd ../pkgbuild

mkdir -p arch

mkdir -p arch/src

cp -u ../takla/AUR/* arch/

cd arch

find . -name takla\*.xz -delete

find . -name takla\*.rpm -delete

find . -name takla\*.deb -delete

rm -r usr/

cd src
	if [ -d master ] ; then
		cd master && git pull origin master && cd ..
		msg "The local files are updated."
	else
		git clone ../../../takla --single-branch master
	fi

cd ..

makepkg -s
# linux32 makepkg -src --config ~/.makepkg.i686.conf

mv takla*.xz takla.xz

tar xf takla.xz

rm .INSTALL .MTREE .PKGINFO takla.xz

fpm -s dir -t deb -a "amd64" -n "takla" --category 'Qt,Education' --deb-field  'Depends: libqtgui4' --description 'Text And Keyboard Layout Analyzer' --deb-field 'Provides:ktla' --url  'http://github.com/omidnikta/takla' --license GPL2 --vendor '' -v $1 -m 'Omid Nikta' usr

mv -f takla*_amd64.deb ../../gh-pages/Downloads/takla_amd64.deb

fpm -s dir -t rpm -n "takla" --category 'Qt,Education' --description 'Text And Keyboard Layout Analyzer'  --url 'http://github.com/omidnikta/takla' --license GPL2 --vendor '' -v $1 -m 'Omid Nikta' -d 'libqt4' usr

mv -f takla-*.x86_64.rpm ../../gh-pages/Downloads/takla_suse.x86_64.rpm

fpm -s dir -t rpm -n "takla" --category 'Qt,Education' --description 'Text And Keyboard Layout Analyzer'  --url 'http://github.com/omidnikta/takla' --license GPL2 --vendor '' -v $1 -m 'Omid Nikta' -d 'qt-x11' usr

mv -f takla-*.x86_64.rpm ../../gh-pages/Downloads/takla_fedora.x86_64.rpm
cd ..

mkdir -p win64

mkdir -p win64/takla-build

cd win64/takla-build

x86_64-w64-mingw32-qmake-qt5 ../../../takla

make clean

make

cp release/takla.exe ../

cd ../..

mkdir -p win32

mkdir -p win32/takla-build

cd win32/takla-build

i686-w64-mingw32-qmake-qt5 ../../../takla

make clean

make

cp release/takla.exe ../

# This is an example PKGBUILD file. Use this as a start to creating your own,
# and remove these comments. For more information, see 'man PKGBUILD'.
# NOTE: Please fill out the license field for your package! If it is unknown,
# then please put 'unknown'.

# Maintainer: Michael Kuc <michaelkuc6@gmail.com>
pkgname=slstatus
pkgver=1.0
pkgrel=1
pkgdesc="A custom version modified for my purposes."
arch=('i686' 'x86_64')
url="https://github.com/Crystalix007/slstatus"
license=('MIT/X Consortium license'/)
depends=('libx11')
provides=('slstatus')
conflicts=('slstatus-git')
epoch=1
source=("arg.h"
	"config.def.h"
	"config.mk"
	"Makefile"
	"slstatus.1"
	"slstatus.c"
	"slstatus.h"
	"util.c"
	"util.h"
	"LICENSE"
	"README")

prepare(){
	ln -s $startdir/components/ $srcdir/
	make clean
}

build() {
	make
}

check() {
	: #Do nothing
}

package() {
	make PREFIX=/usr DESTDIR="$pkgdir/" install
	install -m644 -D $srcdir/LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
	install -m644 -D $srcdir/README "$pkgdir/usr/share/doc/$pkgname/README"
}

md5sums=(SKIP
         SKIP
         SKIP
         SKIP
         SKIP
         SKIP
         SKIP
         SKIP
         SKIP
         SKIP
         SKIP)

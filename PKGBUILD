# Maintainer: Niklas Hedlund <nojan1989@gmail.com>
pkgname=nojyatzy-git
pkgver=10.5aa12cd
pkgrel=1
pkgdesc="Simple console based yatzy"
url="http://github.com/nojan1/nojyatzy"
arch=('x86_64' 'i686')
license=('GPLv3')
optdepends=()
makedepends=("gcc")
source=('git://github.com/nojan1/nojyatzy.git')
md5sums=('SKIP')

_gitname='nojyatzy'

pkgver() {
  cd $_gitname
  echo $(git rev-list --count HEAD).$(git rev-parse --short HEAD)
}

build() {
  cd "$srcdir/$_gitname"
  make
}

package() {
  cd "$srcdir/$_gitname"
  make DESTDIR="$pkgdir" PREFIX="/usr" HIGHSCOREPATH="/usr/share/$_gitname/highscore.bin" install
 
  mkdir -p "$pkgdir/usr/share/$_gitname/" 
  #echo "" > "$pkgdir/usr/share/$_gitname/highscore.bin"
  #chmod 666 "$pkgdir/usr/share/$_gitname/highscore.bin"
  echo "" > highscore.bin
  install -m666 highscore.bin "$pkgdir/usr/share/$_gitname/highscore.bin"
  rm highscore.bin
}

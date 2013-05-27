# Maintainer: Niklas Hedlund <nojan1989@gmail.com>
pkgname=nojyatzy-git
pkgver=20130527
pkgrel=1
pkgdesc="Simple console based yatzy"
url="http://github.com/nojan1/nojyatzy"
arch=('x86_64' 'i686')
license=('GPLv3')
depends=('php' 'mysql')
optdepends=()
makedepends=("git")

_gitroot='git://github.com/nojan1/nojyatzy.git'
_gitname='nojyatzy'


build() {
  cd "${srcdir}"
  msg "Connecting to GIT server...."

   if [[ -d "$_gitname" ]]
   then
	cd "$_gitname"
	git pull origin
	msg "The local files are updated."
   else
	git clone "$_gitroot" "$_gitname"
   fi

    msg "GIT checkout done or server timeout"
    msg "Starting build..."

    rm -rf "$srcdir/$_gitname-build"
    git clone "$srcdir/$_gitname" "$srcdir/$_gitname-build"
    echo "" > highscore.bin
}

package() {
  cd "${srcdir}/$_gitname-build"
  make DESTDIR="${pkgdir}" PREFIX="/usr" HIGHSCOREPATH="/usr/share/$_gitname/highscore.bin" install
 
  mkdir -p "${pkgdir}/usr/share/$_gitname/" 
  install -m666 "highscore.bin" "${pkgdir}/usr/share/$_gitname/highscore.bin"
}

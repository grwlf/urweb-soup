{libraries ? {}}

let

uwb = (import <urweb-build>) libraries;

in with uwb;

rec {

  lib = mkLib {

    name = "Soup";

    libraries = {
      prelude = thirdparty ./lib/urweb-prelude;
      bootstrap = thirdparty ./lib/uru3/Bootstrap;
      uru3 = thirdparty ./lib/uru3/Uru;
    };

    statements = [
      (set "allow url 'http://github.com*'")
      (set "allow url 'http://impredicative.com*'")
      (set "allow url 'https://camo.githubusercontent.com*'")
      (embed-css ./Soup.css)
      (obj-cpp-11 ./Analytics.cpp)
      (ffi ./Analytics.urs)
      (include ./Analytics.h)
      (src1 ./Soup.ur)
    ];
  };

}



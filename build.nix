{libs ? []}

let

uwb = (import <urweb-build>) libs;

in with uwb;

rec {

  lib = mkLib {
    name = "Soup";

    statements = [
      (set "allow url 'http://github.com*'")
      (set "allow url 'http://impredicative.com*'")
      (set "allow url 'https://camo.githubusercontent.com*'")
      (embed-css ./Soup.css)
      (obj-cpp-11 ./Analytics.cpp)
      (ffi ./Analytics.urs)
      (include ./Analytics.h)
      (src1 ./Soup.ur)

      (lib bootstrap ./lib/uru3/Bootstrap)
      (lib prelude ./lib/uru3/Uru)
      (lib uru ./lib/uru3/Uru)

      # library Bootstrap.lib
      # library Uru.lib
      # library Prelude.lib
    ];
  };

}



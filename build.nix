{libraries ? {}} :

let

uwb = (import <urweb-build>) { inherit libraries; };

in with uwb;

rec {

  soup = mkLib {

    name = "Soup";

    libraries = {
      prelude = thirdparty ./lib/urweb-prelude;
      bootstrap = thirdparty ./lib/uru3/Bootstrap;
      uru = thirdparty ./lib/uru3/Uru;
    };

    statements = [
      (set "allow url http://github.com*")
      (set "allow url http://impredicative.com*")
      (set "allow url https://camo.githubusercontent.com*")
      (embed-css ./Soup.css)

      (include ./Analytics.h)
      (obj-cpp-11 ./Analytics.cpp)
      (ffi ./Analytics.urs)

      (include ./MD5_FFI.h)
      (ffi ./MD5_FFI.urs)
      (obj {
        compiler = "gcc";
        source=./MD5_FFI.c;
        suffixes = [".c"];
        cflags=["-I${./.}"];
       })

      (src1 ./Soup.ur)
    ];
  };

}



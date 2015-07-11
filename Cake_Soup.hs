module Cake_Soup where

import Development.Cake3
import Development.Cake3.Ext.UrWeb as UW
import Development.Cake3.Utils.Slice

import qualified Cake_Bootstrap as Bootstrap
import qualified Cake_URU as Uru
import qualified Cake_Prelude as Prelude
import Cake_Soup_P

lib = uwlib (file "lib.urp") $ do
  library Bootstrap.lib
  library Uru.lib
  library Prelude.lib
  allow url "http://github.com*"
  allow url "http://impredicative.com*"
  allow url "https://camo.githubusercontent.com*"
  embed (file "Soup.css")

  src (file "Analytics.cpp","-std=c++11","-lstdc++")
  ffi (file "Analytics.urs")
  include (file "Analytics.h")

  src (file "Unsafe.cpp","-std=c++11","-lstdc++")
  ffi (file "Unsafe.urs")
  include (file "Unsafe.h")

  ffi (file "HTML5Tags.urs")
  ur (file "Snippets.ur")
  ur (file "Soup.ur")

main = writeDefaultMakefiles $ do
  rule $ do
    phony "all"
    depend lib


structure P = Prelude
structure L = List
structure B = Bootstrap

val cl = @@CSS.list

fun footer_doc_links (l:list xbody) : xbody =
  <xml>
  <li style="display:inline">
  {P.head l}
  </li>
  {List.mapX (fn i => <xml>
    <li style="display:inline">·</li>
    <li style="display:inline">
    {i}
    </li>
  </xml>) (P.tail l)}
  </xml>

fun forkme_ribbon (u:url) : xbody =
  <xml>
    <a href={u}>
      <img style="position:absolute; top:0; right:0; border:0;" src={bless "https://camo.githubusercontent.com/365986a132ccd6a44c23a9169022c0b5c890c387/68747470733a2f2f73332e616d617a6f6e6177732e636f6d2f6769746875622f726962626f6e732f666f726b6d655f72696768745f7265645f6161303030302e706e67"} alt="Fork me on GitHub" data={data_attr data_kind "canonical-src" "https://s3.amazonaws.com/github/ribbons/forkme_right_red_aa0000.png"}/>
    </a>
  </xml>

fun badge (txt:string) (num:int) : xbody =
  <xml>
    <button class={cl (B.btn :: B.btn_primary :: [])}>{[txt]}  <span class={B.badge}>{[num]}</span></button>
  </xml>

fun narrow_container (x:xbody) : xbody =
  <xml>
    <div class={B.container} style="margin-top:50px; margin-bottom:100px; max-width:730px; padding-bottom:50px">
      {x}
    </div>
  </xml>

fun narrow_footer (x:xbody) : xbody =
  <xml>
    <div style="margin-bottom:20px;position:absolute;bottom:0; width:100%; height:100px;">
      <div class={B.container} style="text-align:center">
        {x}
      </div>
    </div>
  </xml>

con dpage = Uru.dpage
con need = [BOOTSTRAP=unit]
con out = need ++ [SOUP=unit]

val act = {
  Container = narrow_container,
  Footer = narrow_footer
  }

fun narrow [t:::{Type}] [t~out]
  (* (f: typeof(act) -> record (dpage (t ++ out)) -> transaction page) *)
  f
  (r:record (dpage (t ++ need)))
  : transaction page = 
  f act (Uru.addStylesheet (Soup_css.url) (Uru.addTag [#SOUP] {} r))


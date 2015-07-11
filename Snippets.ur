

fun googleAnalytics (uid:int) : xhead =
  Unsafe.s2xhead (
    "<script>
      (function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
      (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
      m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
      })(window,document,'script','//www.google-analytics.com/analytics.js','ga');
      ga('create', '"^ (show uid) ^ "', 'auto');
      ga('send', 'pageview');
    </script>"
  )

fun paypalDonate (a:{Email : string, Service : string}) : xbody =
  Unsafe.s2xbody (
    "<form action='https://www.paypal.com/cgi-bin/webscr' method='post' target='_top'>
    <input type='hidden' name='cmd' value='_donations'>
    <input type='hidden' name='business' value='"^a.Email^"'>
    <input type='hidden' name='lc' value='RU'>
    <input type='hidden' name='item_name' value='"^a.Service^"'>
    <input type='hidden' name='currency_code' value='RUB'>
    <input type='hidden' name='bn' value='PP-DonationsBF:btn_donate_SM.gif:NonHosted'>
    <input type='image' src='https://www.paypalobjects.com/ru_RU/RU/i/btn/btn_donate_SM.gif' border='0' name='submit' alt='PayPal — более безопасный и легкий способ оплаты через Интернет!'>
    <img alt='' border='0' src='https://www.paypalobjects.com/ru_RU/i/scr/pixel.gif' width='1' height='1'>
    </form>"
  )

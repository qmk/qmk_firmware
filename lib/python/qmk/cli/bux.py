"""QMK Bux

World domination secret weapon.
"""
from milc import cli
from milc.subcommand import config


@cli.subcommand('QMK Bux miner.', hidden=True)
def bux(cli):
    """QMK bux
    """
    if not cli.config.user.bux:
        bux = 0
    else:
        bux = cli.config.user.bux

    cli.args.read_only = False
    config.set_config('user', 'bux', bux + 1)
    cli.save_config()

    buck = r"""
@@BBBBBBBBBBBBBBBBBBBBK    `vP8#####BE2~   x###g_     `S###q  n##}  -j#Bl.   vBBBBBBBBBBBBBBBBBBBB@@
@B   `:!:                 ^#@#]-   `!t@@&. 7@@B@#^   _Q@Q@@R  y@@l:P@#1'                   `!!_   B@
@B  r@@@B                 g@@|      ` N@@u 7@@iv@@u *#@z"@@R  y@@&@@Q-                    l@@@D   B@
@B   !#@B                 ^#@#x-   I@B@@&' 7@@i "B@Q@@r _@@R  y@@l.k#@W:                  `:@@D   B@
@B    B@B                  `v3g#####B0N#d. v##x  'ckk:  -##A  u##i  `lB#I_                  @@D   B@
@B    B@B                                                                                   @@D   B@
@B    B@B                                    `._":!!!=~^*|)r^~:'                            @@D   B@
@B    ~*~                             `,=)]}y2tjIIfKfKfaPsffsWsUyx~.                        **!   B@
@B          .*r***r=              _*]yzKsqKUfz22IAA3HzzUjtktzHWsHsIz].                            B@
@B         )v`  ,  !1-         -rysHHUzUzo2jzoI22ztzkyykt2zjzUzIa3qPsl'        !r*****`           B@
@B        :}    @`  .j       `xzqdAfzKWsj2kkcycczqAsk2zHbg&ER5q55SNN5U~   !RBB#d`c#1 f#\BQ&v      B@
@B        _y   ]#   ,c       vUWNWWPsfsssN9WyccnckAfUfWb0DR0&R5RRRddq2_  `@D`jr@2U@#c3@1@Qc-      B@
@B         !7!    .r]`       }AE0RdRqNd9dNR9fUIzzosPqqAddNNdER9EE9dPy!    BQ!zy@iU@.Q@@y@8x-      B@
@B           :****>.         '7adddDdR&gRNdRbd&dNNbbRdNdd5NdRRD0RSf}-     .k0&EW`xR .8Q=NRRx      B@
@B        =**-rx*r}r~}"        ;n2jkzsf3N3zsKsP5dddRddddRddNNqPzy\"            '~****"            B@
@B        :!!~!;=~r>:*_         `:^vxikylulKfHkyjzzozoIoklix|^!-`                                 B@
@B                                    ```'-_""::::!:_-.``                                         B@
@B   `-                                                                                       .`  B@
@B   r@=                                  In source we trust                                  @H  B@
@B   r@=                                                                                      @H  B@
@B  -g@=                `}&###E7  W#g. :#Q n####~   R###8k ;#&  `##.7#8-`R#z                 t@H  B@
@B   r@=                8@R=-=R@g R@@#:!@@ 2@&!:`   8@1=@@!*@B  `@@- v@#8@y                   @H  B@
@B   r@=               :@@-   _@@_R@fB#}@@ 2@@@#    8@@#@Q.*@B  `@@-  y@@N                    @H  B@
@B   `.                 g@9=_~D@g R@}`&@@@ 2@&__`   8@u_Q@2!@@^-x@@` Y@QD@z                   .`  B@
@@BBBBBBBBBBBBBBBBBBB_  `c8@@@81` S#] `N#B l####v   D###BA. vg@@#0~ i#&' 5#K   RBBBBBBBBBBBBBBBBBB@@
""" # noqa: Do not care about the ASCII art
    print(f"{buck}\nYou've been blessed by the QMK gods!\nYou have {cli.config.user.bux} QMK bux.")

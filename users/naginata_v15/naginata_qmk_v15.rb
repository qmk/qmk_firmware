# 小書はシフト冗長を手で修正しないといけません

tanda = <<ETANDA
ゔ|き|て|し|{←}|{→}|{BS}|る|す|へ|@|[  |
ろ|け|と|か|っ  |く  |あ  |い|う|ー|:|]  |
ほ|ひ|は|こ|そ  |た  |な  |ん|ら|れ|\|
ETANDA

shifted = <<ESHIFTED
   |ぬ|り |ね|+{←}|+{→}|さ       |よ|え|ゆ|`|{{}|
 ふ|め|に |ま|ち   |や   |の       |も|つ|せ|*|{}}|
 ほ|ひ|を |、|み   |お   |。{Enter}|む|わ|れ|_|
ESHIFTED

mode1l = <<MEND
^{End}    |『』{改行}{↑}|/*ディ*/|^s            |・                             ||||||||
……{改行}|(){改行}{↑}  |？{改行}|「」{改行}{↑}|{改行}{End}{改行}「」{改行}{↑}||||||||
││{改行}|【】{改行}{↑}|！{改行}|{改行}{↓}    |{改行}{End}{改行}{Space}       |||||||
MEND

mode1r = <<MEND
|||||{Home}      |+{End}{BS}|{vk1Csc079}|{Del} |{Esc 3}|  |  |
|||||{Enter}{End}|{↑}      |+{↑}      |+{↑ 7}|^i|  |  |
|||||{End}       |{↓}      |+{↓}      |+{↓ 7}|^u|  |
MEND

mode2l = <<MEND
^x{BS}{Del}^v                           |^x『^v』{改行}{Space}+{↑}^x|{Home}{改行}{Space 3}{End}|{Home}{改行}{Space 1}{End}  |〇{改行}                        ||||||||
《》{改行}{↑}                          |^x(^v){改行}{Space}+{↑}^x  |{Space 3}                 |^x「^v」{改行}{Space}+{↑}^x|／{改行}                        ||||||||
^x｜{改行}^v《》{改行}{↑}{Space}+{↑}^x|^x【^v】{改行}{Space}+{↑}^x|{Home}{BS}{Del 3}{End}    |{Home}{BS}{Del 1}{End}      |　　　×　　　×　　　×{改行 2}|||||||
MEND

mode2r = <<MEND
|||||+{Home}|^x     |^v     |^y      |^z|  |  |
|||||^c     | {→ 5}|+{→ 5}|+{→ 20}|+{→}|  |  |
|||||+{End} | {← 5}|+{← 5}|+{← 20}|+{←}|  |
MEND

eiji    = %w(Q W E R T  Y U I O P  A S D F G  H J K L SCLN  Z X C V B  N M COMM DOT SLSH)
eiji_r  = %w(Y U I O P  H J K L SCLN N M COMM DOT SLSH)
eiji_l  = %w(Q W E R T  A S D F G  Z X C V B)

tanda = tanda.split("|").map{|c| c.strip}
tanda.delete_at(35)
tanda.delete_at(34)
tanda.delete_at(23)
tanda.delete_at(22)
tanda.delete_at(11)
tanda.delete_at(10)

shifted = shifted.split("|").map{|c| c.strip}
shifted.delete_at(35)
shifted.delete_at(34)
shifted.delete_at(23)
shifted.delete_at(22)
shifted.delete_at(11)
shifted.delete_at(10)

kana      = %w(あ い う え お か き く け こ さ し す せ そ た ち つ て と な に ぬ ね の は ひ ふ へ ほ ま み む め も や ゆ よ ら り る れ ろ わ を ん ー)
r_kana    = %w(a i u e o ka ki ku ke ko sa si su se so ta ti tu te to na ni nu ne no ha hi hu he ho ma mi mu me mo ya yu yo ra ri ru re ro wa wo nn -)

daku      = %w(が ぎ ぐ げ ご ざ じ ず ぜ ぞ だ ぢ づ で ど ば び ぶ べ ぼ ゔ)
r_daku    = %w(ga gi gu ge go za zi zu ze zo da di du de do ba bi bu be bo vu)
t_daku    = %w(か き く け こ さ し す せ そ た ち つ て と は ひ ふ へ ほ う)

handaku   = %w(ぱ ぴ ぷ ぺ ぽ)
t_handaku = %w(は ひ ふ へ ほ)
r_handaku = %w(pa pi pu pe po)

kogaki    = %w(ゃ ゅ ょ ぁ ぃ ぅ ぇ ぉ ゎ っ ヶ ヵ)
t_kogaki  = %w(や ゆ よ あ い う え お わ っ け か)
r_kogaki  = %w(xya xyu xyo xa xi xu xe xo xwa xtu xke xka)

kumiawase = []
r_kumiawase = []
kumiawase << %w(しゃ しゅ しょ じゃ じゅ じょ)
r_kumiawase << %w(sya syu syo zya zyu zyo)
kumiawase << %w(きゃ きゅ きょ ぎゃ ぎゅ ぎょ)
r_kumiawase << %w(kya kyu kyo gya gyu gyo)
kumiawase << %w(ちゃ ちゅ ちょ ぢゃ ぢゅ ぢょ)
r_kumiawase << %w(tya tyu tyo dya dyu dyo)
kumiawase << %w(にゃ にゅ にょ)
r_kumiawase << %w(nya nyu nyo)
kumiawase << %w(ひゃ ひゅ ひょ びゃ びゅ びょ ぴゃ ぴゅ ぴょ)
r_kumiawase << %w(hya hyu hyo bya byu byo pya pyu pyo)
kumiawase << %w(みゃ みゅ みょ)
r_kumiawase << %w(mya myu myo)
kumiawase << %w(りゃ りゅ りょ)
r_kumiawase << %w(rya ryu ryo)

gairai = []
r_gairai = []
gairai << %w(てぃ てゅ でぃ でゅ)
r_gairai << %w(thi thu dhi dhu)
gairai << %w(とぅ どぅ)
r_gairai << %w(toxu doxu)
gairai << %w(しぇ ちぇ じぇ ぢぇ)
r_gairai << %w(sye tye zye dye)

gairai << %w(ふぁ ふぃ ふぇ ふぉ ふゅ)
r_gairai << %w(fa fi fe fo fyu)
gairai << %w(いぇ)
r_gairai << %w(ixe)
gairai << %w(うぃ うぇ うぉ ゔぁ ゔぃ ゔぇ ゔぉ ゔゅ)
r_gairai << %w(wi we uxo va vi ve vo vuxyu)
gairai << %w(くぁ くぃ くぇ くぉ くゎ ぐぁ ぐぃ ぐぇ ぐぉ ぐゎ)
r_gairai << %w(kuxa kuxi kuxe kuxo kuxwa guxa guxi guxe guxo guxwa)
gairai << %w(つぁ つぃ つぇ つぉ)
r_gairai << %w(tsa tsi tse tso)

kumiawase.flatten!
r_kumiawase.flatten!
gairai.flatten!
r_gairai.flatten!

def teigi(a, b, c, prefix="", suffix="")
  _a = [a].flatten.map{|k| "B_" + k}.join("|")
  sprintf("  {%-32s", ".key = #{prefix}#{_a}#{suffix}") + sprintf("%-20s", ", .kana = \"#{b}\"") + "}, // #{c}"
end

puts "  // 清音"
kana.each_with_index do |k, i|
  j = tanda.index(k)
  if j && j >= 0
    puts teigi(eiji[j], r_kana[i], k)
  end
  j = shifted.index(k)
  if j && j >= 0
    puts teigi(eiji[j], r_kana[i], k, "B_SHFT|")
  end
end

puts
puts "  // 濁音"
daku.each_with_index do |k, i|
  j = tanda.index(t_daku[i]) || shifted.index(t_daku[i])
  if j && j >= 0
    if eiji_r.index(eiji[j])
      puts teigi(eiji[j], r_daku[i], k, "B_F|")
      # puts teigi(eiji[j], r_daku[i], k + "(冗長)", "B_F|", "|B_SHFT")
    else
      puts teigi(eiji[j], r_daku[i], k, "B_J|")
      # puts teigi(eiji[j], r_daku[i], k + "(冗長)", "B_J|", "|B_SHFT")
    end
  end
end

puts
puts "  // 半濁音"
handaku.each_with_index do |k, i|
  j = tanda.index(t_handaku[i]) || shifted.index(t_handaku[i])
  if j && j >= 0
    if eiji_r.index(eiji[j])
      puts teigi(eiji[j], r_handaku[i], k, "B_V|")
      # puts teigi(eiji[j], r_handaku[i], k + "(冗長)", "B_V|", "|B_SHFT")
    else
      puts teigi(eiji[j], r_handaku[i], k, "B_M|")
      # puts teigi(eiji[j], r_handaku[i], k + "(冗長)", "B_M|", "|B_SHFT")
    end
  end
end

puts
puts "  // 小書き"
kogaki.each_with_index do |k, i|
  j = tanda.index(k)
  if j && j >= 0
    puts teigi(eiji[j], r_kogaki[i], k)
    next
  end
  j = shifted.index(k)
  if j && j >= 0
    puts teigi(eiji[j], r_kogaki[i], k, "B_SHFT|")
    next
  end

  j = tanda.index(t_kogaki[i]) || shifted.index(t_kogaki[i])
  if j && j >= 0
    puts teigi(eiji[j], r_kogaki[i], k, "B_Q|")
    puts teigi(eiji[j], r_kogaki[i], k, "B_Q|B_SHFT|")
    # puts teigi(eiji[j], r_kogaki[i], k, "B_V|B_M|")
    # puts teigi(eiji[j], r_kogaki[i], k + "(冗長)", "B_V|B_M|", "|B_SHFT")
  end
end

puts
puts "  // 清音拗音 濁音拗音 半濁拗音"
kumiawase.each_with_index do |k, i|
  j = tanda.index(k[0])
  if j && j >= 0
    e0 = eiji[j]
  end
  unless e0
    j = shifted.index(k[0])
    if j && j >= 0
      e0 = eiji[j]
    end
  end
  unless e0
    l = daku.index(k[0])
    if l && l >= 0
      j = tanda.index(t_daku[l]) || shifted.index(t_daku[l])
      if j && j >= 0
        if eiji_r.index(eiji[j])
          e0 = ["F", eiji[j]]
        else
          e0 = ["J", eiji[j]]
        end
      end
    end
  end
  unless e0
    l = handaku.index(k[0])
    if l && l >= 0
      j = tanda.index(t_handaku[l]) || shifted.index(t_handaku[l])
      if j && j >= 0
        if eiji_r.index(eiji[j])
          e0 = ["V", eiji[j]]
        else
          e0 = ["M", eiji[j]]
        end
      end
    end
  end

  l = kogaki.index(k[1])
  j = tanda.index(t_kogaki[l]) || shifted.index(t_kogaki[l])
  if j && j >= 0
    e1 = eiji[j]
    puts teigi([e0, e1], r_kumiawase[i], k)
    # puts teigi([e0, e1], r_kumiawase[i], k + "(冗長)", "", "|B_SHFT")
  end
end

puts
puts "  // 清音外来音 濁音外来音"
gairai.each_with_index do |k, i|
  j = tanda.index(k[0]) || shifted.index(k[0])
  if j && j >= 0
    if eiji_r.index(eiji[j])
      e0 = ["V", eiji[j]]
    else
      e0 = ["M", eiji[j]]
    end
  end
  unless e0
    l = daku.index(k[0])
    if l && l >= 0
      j = tanda.index(t_daku[l]) || shifted.index(t_daku[l])
      if j && j >= 0
        if eiji_r.index(eiji[j])
          e0 = ["F", eiji[j]]
        else
          e0 = ["J", eiji[j]]
        end
      end
    end
  end

  l = kogaki.index(k[1])
  j = tanda.index(t_kogaki[l]) || shifted.index(t_kogaki[l])
  if j && j >= 0
    e1 = eiji[j]
    puts teigi([e0, e1], r_gairai[i], k)
    # puts teigi([e0, e1], r_gairai[i], k + "(冗長)", "", "|B_SHFT")
  end
end


# 編集モード

$henshu = {
"/*ディ*/"          => ["kana", "\"dhi\""],
"？{改行}"      => ["kana"  , "\"?\"SS_TAP(X_ENTER)"],
"！{改行}"      => ["kana"  , "\"!\"SS_TAP(X_ENTER)"],
"{Home}"        => ["kana", "SS_TAP(X_HOME)", "SS_LCTL(\"a\")"],
"{End}"         => ["kana", "SS_TAP(X_END)", "SS_LCTL(\"e\")"],
"+{Home}"       => ["kana", "SS_LSFT(SS_TAP(X_HOME))", "SS_LSFT(SS_LCTL(SS_TAP(NGUP)))"],
"+{End}"        => ["kana", "SS_LSFT(SS_TAP(X_END))", "SS_LSFT(SS_LCTL(\"e\"))"],
"^{End}"        => ["kana", "SS_LCTL(SS_TAP(X_END))", "SS_LCMD(SS_LCTL(\"e\"))"],
"+{End}{BS}"    => ["kana", "SS_LSFT(SS_TAP(X_END))SS_TAP(X_BSPACE)", "SS_LSFT(SS_LCTL(\"e\"))SS_TAP(X_BSPACE)"], # 末消
"{vk1Csc079}"   => ["kana", "SS_TAP(X_INT4)"], # 再変換
"{Del}"         => ["kana", "SS_TAP(X_DELETE)"],
"{Esc 3}"       => ["kana", "SS_TAP(X_ESCAPE)SS_TAP(X_ESCAPE)SS_TAP(X_ESCAPE)"],
"{↑}"          => ["kana", "SS_TAP(NGUP)"],
"{↓}"          => ["kana", "SS_TAP(NGDN)"],
"+{↑}"         => ["kana", "SS_LSFT(SS_TAP(NGUP))"],
"+{↓}"         => ["kana", "SS_LSFT(SS_TAP(NGDN))"],
"{↑ 5}"        => ["kana", "SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)"],
"{↓ 5}"        => ["kana", "SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)"],
"+{↑ 7}"        => ["kana", "SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)"],
"+{↓ 7}"        => ["kana", "SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)"],
"+{→ 5}"       => ["kana", "SS_LSFT(SS_TAP(NGRT)SS_TAP(NGRT)SS_TAP(NGRT)SS_TAP(NGRT)SS_TAP(NGRT))"],
"+{← 5}"       => ["kana", "SS_LSFT(SS_TAP(NGLT)SS_TAP(NGLT)SS_TAP(NGLT)SS_TAP(NGLT)SS_TAP(NGLT))"],
"{→ 5}"        => ["kana", "SS_TAP(NGRT)SS_TAP(NGRT)SS_TAP(NGRT)SS_TAP(NGRT)SS_TAP(NGRT)"],
"{← 5}"        => ["kana", "SS_TAP(NGLT)SS_TAP(NGLT)SS_TAP(NGLT)SS_TAP(NGLT)SS_TAP(NGLT)"],
"^{PgUp}"       => ["kana", "SS_LCTL(SS_TAP(X_PGUP))", "SS_TAP(X_PGUP)"],
"^{PgDn}"       => ["kana", "SS_LCTL(SS_TAP(X_PGDOWN))", "SS_TAP(X_PGDOWN)"],
"^{PgUp 5}"       => ["kana", "SS_LCTL(SS_TAP(X_PGUP)SS_TAP(X_PGUP)SS_TAP(X_PGUP)SS_TAP(X_PGUP)SS_TAP(X_PGUP))", "SS_TAP(X_PGUP)SS_TAP(X_PGUP)SS_TAP(X_PGUP)SS_TAP(X_PGUP)SS_TAP(X_PGUP)"],
"^{PgDn 5}"       => ["kana", "SS_LCTL(SS_TAP(X_PGDOWN)SS_TAP(X_PGDOWN)SS_TAP(X_PGDOWN)SS_TAP(X_PGDOWN)SS_TAP(X_PGDOWN))", "SS_TAP(X_PGDOWN)SS_TAP(X_PGDOWN)SS_TAP(X_PGDOWN)SS_TAP(X_PGDOWN)SS_TAP(X_PGDOWN)"],
"{Enter}{End}"  => ["kana", "SS_TAP(X_ENTER)SS_TAP(X_END)"],
"{Home}{改行}{Space 3}{End}"=> ["kana", "SS_TAP(X_HOME)SS_TAP(X_ENTER)SS_TAP(X_SPACE)SS_TAP(X_SPACE)SS_TAP(X_SPACE)SS_TAP(X_END)", "SS_LCTL(\"a\")SS_TAP(X_ENTER)SS_TAP(X_SPACE)SS_TAP(X_SPACE)SS_TAP(X_SPACE)SS_LCTL(\"e\")"], # 台マクロ
"{Home}{改行}{Space 1}{End}"=> ["kana", "SS_TAP(X_HOME)SS_TAP(X_ENTER)SS_TAP(X_SPACE)SS_TAP(X_END)", "SS_LCTL(\"a\")SS_TAP(X_ENTER)SS_TAP(X_SPACE)SS_LCTL(\"e\")"], # ト マクロ

"+{↑ 5}" => ["kana", "SS_LSFT(SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP)SS_TAP(NGUP))"],
"+{↓ 5}" => ["kana", "SS_LSFT(SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN)SS_TAP(NGDN))"],
"+{PgUp}" => ["kana", "SS_LSFT(SS_TAP(X_PGUP))"],
"+{PgDn}" => ["kana", "SS_LSFT(SS_TAP(X_PGDOWN))"],
"^x{BS}{Del}^v" => ["kana", "SS_LCTL(\"x\")SS_TAP(X_BSPACE)SS_TAP(X_DELETE)SS_LCTL(\"v\")", "SS_LCMD(\"x\")SS_TAP(X_BSPACE)SS_TAP(X_DELETE)SS_LCMD(\"v\")"],
"{Home}{BS}{Del 3}{End}" => ["kana", "SS_TAP(X_HOME)SS_TAP(X_BSPACE)SS_TAP(X_DELETE)SS_TAP(X_DELETE)SS_TAP(X_DELETE)SS_TAP(X_END)"],
"{Home}{BS}{Del 1}{End}" => ["kana", "SS_TAP(X_HOME)SS_TAP(X_BSPACE)SS_TAP(X_DELETE)SS_TAP(X_END)"],
"{→}" => ["kana", "SS_TAP(NGRT)"],
"+{→}" => ["kana", "SS_LSFT(SS_TAP(NGRT))"],
"{←}" => ["kana", "SS_TAP(NGLT)"],
"+{←}" => ["kana", "SS_LSFT(SS_TAP(NGLT))"],
"{改行}{↓}" => ["kana", "SS_TAP(X_ENTER)SS_TAP(NGDN)"],
"{改行}{End}{改行}{Space}" => ["kana", "SS_TAP(X_ENTER)SS_TAP(X_END)SS_TAP(X_ENTER)SS_TAP(X_SPACE)"],

"^x(^v){改行}{Space}+{↑}^x" => ["macro", ""],
"^x「^v」{改行}{Space}+{↑}^x" => ["macro", ""],
"『』{改行}{↑}" => ["macro", ""],
"(){改行}{↑}" => ["macro", ""],
"「」{改行}{↑}" => ["macro", ""],
"{改行}{End}{改行}「」{改行}{↑}" => ["macro", ""],
"【】{改行}{↑}" => ["macro", ""],
"《》{改行}{↑}" => ["macro", ""],
"^x『^v』{改行}{Space}+{↑}^x" => ["macro", ""],

"｜{改行}"      => ["uc"  , "｜", "nagitatesenn"],
"・"            => ["uc"  , "・", "nagichuutenn"],
"……{改行}"    => ["uc"  , "……", "nagitentenn"],
"／{改行}"      => ["uc"  , "／", "naginaname"],
"《{改行}"      => ["uc"  , "《", "nagikakkohio"],
"》{改行}"      => ["uc"  , "》", "nagikakkomio"],
"「{改行}"      => ["uc"  , "「", "nagikakkohiu"],
"」{改行}"      => ["uc"  , "」", "nagikakkomiu"],
"({改行}"       => ["uc"  , "(", "nagikakkohika"],
"){改行}"       => ["uc"  , ")", "nagikakkomika"],
"││{改行}"    => ["uc"  , "││", "nagitatesenni"],
"〇{改行}"      => ["uc"  , "〇", "nagimaru"],
"【{改行}"      => ["uc"  , "【", "nagikakkohia"],
"】{改行}"      => ["uc"  , "】", "nagikakkomia"],
"〈{改行}"      => ["uc"  , "〈", "nagikakkohii"],
"〉{改行}"      => ["uc"  , "〉", "nagikakkomii"],
"『{改行}"      => ["uc"  , "『", "nagikakkohie"],
"』{改行}"      => ["uc"  , "』", "nagikakkomie"],

"^x｜{改行}^v《》{改行}{↑}{Space}+{↑}^x"=> ["macro", ""], # ルビ
"」{改行 2}「{改行}"=> ["macro", ""],
"」{改行 2}{Space}"=> ["macro", ""],
"　　　×　　　×　　　×{改行 2}"=> ["macro", ""],
"^x【^v】{改行}{Space}+{↑}^x"=> ["macro", ""],
"+{→ 20}"=> ["macro", ""],
"+{← 20}"=> ["macro", ""],

"{Space 3}"     => ["kana", "SS_TAP(X_SPACE)SS_TAP(X_SPACE)SS_TAP(X_SPACE)"],
"^i"            => ["kana", "SS_LCTL(\"i\")", "SS_LCTL(\"k\")"], # カタカナ
"^u"            => ["kana", "SS_LCTL(\"u\")", "SS_LCTL(\"j\")"], # ひらがな
"^s"            => ["kana", "SS_LCTL(\"s\")", "SS_LCMD(\"s\")"],
"^x"            => ["kana", "SS_LCTL(\"x\")", "SS_LCMD(\"x\")"],
"^v"            => ["kana", "SS_LCTL(\"v\")", "SS_LCMD(\"v\")"],
"^y"            => ["kana", "SS_LCTL(\"y\")", "SS_LCMD(\"y\")"],
"^z"            => ["kana", "SS_LCTL(\"z\")", "SS_LCMD(\"z\")"],
"^c"            => ["kana", "SS_LCTL(\"c\")", "SS_LCMD(\"c\")"],
}

qwerty    = %w(Q W E R T  Y U I O P NO NO A S D F G  H J K L SCLN NO NO Z X C V B  N M COMM DOT SLSH NO)

mode1l = mode1l.split("|").map{|x| x.strip}
mode1r = mode1r.split("|").map{|x| x.strip}
mode2l = mode2l.split("|").map{|x| x.strip}
mode2r = mode2r.split("|").map{|x| x.strip}


$hwin = []
$hmac = []
$uwin = []
$umac = []
$htate = []

def outputHenshu(pk, m, k)
  if $henshu[m][0] == "kana"
    if ($henshu[m][1].include?("NGUP") || $henshu[m][1].include?("NGDN") || $henshu[m][1].include?("NGLT") || $henshu[m][1].include?("NGRT"))
      $hwin << "//{.key = #{pk}|B_#{k}\t\t, .kana = #{$henshu[m][1]}}, // #{m}"
      $htate << "  {.key = #{pk}|B_#{k}\t\t, .kana = #{$henshu[m][1]}}, // #{m}"
    else
      $hwin << "  {.key = #{pk}|B_#{k}\t\t, .kana = #{$henshu[m][1]}}, // #{m}"
      if $henshu[m][2]
        $hmac << "  {.key = #{pk}|B_#{k}\t\t, .kana = #{$henshu[m][2]}}, // #{m}"
      end
    end
  end
  if $henshu[m][0] == "uc"
    $uwin << "  {.key = #{pk}|B_#{k}\t\t, .win   = \"#{$henshu[m][1]}\",\t\t.mac = \"#{$henshu[m][2] || $henshu[m][1]}\"}, // #{m}"
    $hwin << "//{.key = #{pk}|B_#{k}\t\t, .win   = \"#{$henshu[m][1]}\",\t\t.mac = \"#{$henshu[m][2] || $henshu[m][1]}\"}, // #{m}"
  end
  if $henshu[m][0] == "macro"
    $hwin << "//{.key = #{pk}|B_#{k}\t\t, .macro , // #{m}"
  end
end

qwerty.each_with_index do |k, i|
  unless $henshu.key? mode1l[i]
    puts "missing #{mode1l[i]}"
    next
  end
  m =  mode1l[i]
  pk = "B_J|B_K"
  outputHenshu(pk, m, k)
end

qwerty.each_with_index do |k, i|
  unless $henshu.key? mode1r[i]
    puts "missing #{mode1r[i]}"
    next
  end
  m =  mode1r[i]
  pk = "B_D|B_F"
  outputHenshu(pk, m, k)
end

qwerty.each_with_index do |k, i|
  unless $henshu.key? mode2l[i]
    puts "missing #{mode2l[i]}"
    next
  end
  m =  mode2l[i]
  pk = "B_M|B_COMM"
  outputHenshu(pk, m, k)
end

qwerty.each_with_index do |k, i|
  unless $henshu.key? mode2r[i]
    puts "missing #{mode2r[i]}"
    next
  end
  m =  mode2r[i]
  pk = "B_C|B_V"
  outputHenshu(pk, m, k)
end

puts "// 編集モード Win/Linux"
puts $hwin

puts "// 編集モード 縦横"
puts $htate

puts "// 編集モード Mac"
puts $hmac

puts "// 編集モードunicode"
puts $uwin

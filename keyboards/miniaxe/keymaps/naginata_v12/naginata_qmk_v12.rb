
eiji    = %w(Q W E R T  Y U I O P  A S D F G  H J K L SCLN  Z X C V B  N M COMM DOT SLSH)
eiji_r  = %w(Y U I O P  H J K L SCLN N M COMM DOT SLSH)
eiji_l  = %w(Q W E R T  A S D F G  Z X C V B)

tanda   = %w(_ き て し < > 削 る す へ ろ ひ と か っ く あ い う ー ほ け は こ そ た な ん ら れ)

shifted = %w(_ ね り め < > さ よ え ゆ せ ぬ に ま ち や の も わ つ ほ け を 、 み お 。 む ふ れ)

kana      = %w(あ い う え お か き く け こ さ し す せ そ た ち つ て と な に ぬ ね の は ひ ふ へ ほ ま み む め も や ゆ よ ら り る れ ろ わ を ん ー)
r_kana    = %w(a i u e o ka ki ku ke ko sa si su se so ta ti tu te to na ni nu ne no ha hi hu he ho ma mi mu me mo ya yu yo ra ri ru re ro wa wo nn -)

daku      = %w(が ぎ ぐ げ ご ざ じ ず ぜ ぞ だ ぢ づ で ど ば び ぶ べ ぼ ゔ)
r_daku    = %w(ga gi gu ge go za zi zu ze zo da di du de do ba bi bu be bo vu)
t_daku    = %w(か き く け こ さ し す せ そ た ち つ て と は ひ ふ へ ほ う)

handaku   = %w(ぱ ぴ ぷ ぺ ぽ)
t_handaku = %w(は ひ ふ へ ほ)
r_handaku = %w(pa pi pu pe po)

kogaki    = %w(ゃ ゅ ょ ぁ ぃ ぅ ぇ ぉ ゎ っ)
t_kogaki  = %w(や ゆ よ あ い う え お わ っ)
r_kogaki  = %w(xya xyu xyo xa xi xu xe xo xwa xtu)

kumiawase = []
r_kumiawase = []
kumiawase << %w(しぇ しゃ しゅ しょ じぇ じゃ じゅ じょ)
r_kumiawase << %w(sye sya syu syo je ja ju jo)
kumiawase << %w(きゃ きゅ きょ ぎゃ ぎゅ ぎょ)
r_kumiawase << %w(kya kyu kyo gya gyu gyo)
kumiawase << %w(ちぇ ちゃ ちゅ ちょ ぢぇ ぢゃ ぢゅ ぢょ)
r_kumiawase << %w(che cha chu cho dye dya dyu dyo)
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
r_gairai << %w(texi texyu dexi dexyu)
gairai << %w(とぅ どぅ)
r_gairai << %w(toxu doxu)
gairai << %w(しぇ ちぇ じぇ ぢぇ)
r_gairai << %w(sixe tixe jixe dixe)

gairai << %w(ふぁ ふぃ ふぇ ふぉ ふゅ)
r_gairai << %w(fa fi fe fo fyu)
gairai << %w(うぃ うぇ うぉ ゔぁ ゔぃ ゔぇ ゔぉ ゔゅ)
r_gairai << %w(uxi uxe uxo va vi ve vo vuxyu)
gairai << %w(くぁ くぃ くぇ くぉ くゎ ぐぁ ぐぃ ぐぇ ぐぉ ぐゎ)
r_gairai << %w(kuxa kuxi kuxe kuxo kuxwa guxa guxi guxe guxo guxwa)
gairai << %w(つぁ つぃ つぇ つぉ)
r_gairai << %w(tuxa tuxi tuxe tuxo)

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
  if j && j > 0
    puts teigi(eiji[j], r_kana[i], k)
  end
  j = shifted.index(k)
  if j && j > 0
    puts teigi(eiji[j], r_kana[i], k, "B_SHFT|")
  end
end

puts
puts "  // 濁音"
daku.each_with_index do |k, i|
  j = tanda.index(t_daku[i]) || shifted.index(t_daku[i])
  if j && j > 0
    if eiji_r.index(eiji[j])
      puts teigi(eiji[j], r_daku[i], k, "B_F|")
      puts teigi(eiji[j], r_daku[i], k + "(冗長)", "B_F|", "|B_SHFT")
    else
      puts teigi(eiji[j], r_daku[i], k, "B_J|")
      puts teigi(eiji[j], r_daku[i], k + "(冗長)", "B_J|", "|B_SHFT")
    end
  end
end

puts
puts "  // 半濁音"
handaku.each_with_index do |k, i|
  j = tanda.index(t_handaku[i]) || shifted.index(t_handaku[i])
  if j && j > 0
    if eiji_r.index(eiji[j])
      puts teigi(eiji[j], r_handaku[i], k, "B_V|")
      puts teigi(eiji[j], r_handaku[i], k + "(冗長)", "B_V|", "|B_SHFT")
    else
      puts teigi(eiji[j], r_handaku[i], k, "B_M|")
      puts teigi(eiji[j], r_handaku[i], k + "(冗長)", "B_M|", "|B_SHFT")
    end
  end
end

puts
puts "  // 小書き"
kogaki.each_with_index do |k, i|
  j = tanda.index(k)
  if j && j > 0
    puts teigi(eiji[j], r_kogaki[i], k)
    next
  end
  j = shifted.index(k)
  if j && j > 0
    puts teigi(eiji[j], r_kogaki[i], k, "B_SHFT|")
    next
  end

  j = tanda.index(t_kogaki[i]) || shifted.index(t_kogaki[i])
  if j && j > 0
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
  if j && j > 0
    e0 = eiji[j]
  end
  unless e0
    j = shifted.index(k[0])
    if j && j > 0
      e0 = eiji[j]
    end
  end
  unless e0
    l = daku.index(k[0])
    if l && l > 0
      j = tanda.index(t_daku[l]) || shifted.index(t_daku[l])
      if j && j > 0
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
    if l && l > 0
      j = tanda.index(t_handaku[l]) || shifted.index(t_handaku[l])
      if j && j > 0
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
  if j && j > 0
    e1 = eiji[j]
    puts teigi([e0, e1], r_kumiawase[i], k)
    puts teigi([e0, e1], r_kumiawase[i], k + "(冗長)", "", "|B_SHFT")
  end
end

puts
puts "  // 清音外来音 濁音外来音"
gairai.each_with_index do |k, i|
  j = tanda.index(k[0]) || shifted.index(k[0])
  if j && j > 0
    if eiji_r.index(eiji[j])
      e0 = ["V", eiji[j]]
    else
      e0 = ["M", eiji[j]]
    end
  end
  unless e0
    l = daku.index(k[0])
    if l && l > 0
      j = tanda.index(t_daku[l]) || shifted.index(t_daku[l])
      if j && j > 0
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
  if j && j > 0
    e1 = eiji[j]
    puts teigi([e0, e1], r_gairai[i], k)
    puts teigi([e0, e1], r_gairai[i], k + "(冗長)", "", "|B_SHFT")
  end
end

# QMK मैकेनिकल कीबोर्ड फर्मवेयर

[![वर्तमान संस्करण](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![संस्करण की स्थिति](https://travis-ci.org/qmk/qmk_firmware.svg?branch=master)](https://travis-ci.org/qmk/qmk_firmware)
[![डिस्कॉर्ड](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![प्रलेखन की स्थिति](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub सहायक](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub शाखाएँ](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

## QMK फर्मवेयर क्या है?

QMK (*Quantum Mechanical Keyboard*) एक मुक्त स्रोत वर्ग है जो QMK फर्मवेयर, QMK टूलबॉक्स, qmk.fm और इन प्रलेखनो का संचालन करता है। QMK फर्मवेयर एक कीबोर्ड फर्मवेयर है, जो [tmk\_keyboard](http://github.com/tmk/tmk_keyboard) पर आधारित है, जो विशेष रूप से, Atmel AVR माइक्रोकंट्रोलर पर कुछ उपयोगी सुविधाओं को लागू करता है। विशेष रूप से, [OLKB उत्पाद लाइन](http://olkb.com), [ErgoDox EZ](http://www.ergodox-ez.com) कीबोर्ड, और [Clueboard उत्पाद लाइन](http://clueboard.co/)। इसे ARM की चिप्स में ChibiOS का इस्तेमाल कर भी डाला गया हैं। आप इसे अपने खुद के कीबोर्ड पीसीबी के लिए भी उपयोग कर सकते हैं।

## इसे कैसे प्राप्त करें

यदि आप QMK के कीमैप, कीबोर्ड, या अन्य सुविधाओं मे योगदान करना चाहते हैं तो सबसे आसान तरीका है  [Github के माध्यम से repo fork करना](https://github.com/qmk/qmk_firmware#fork-destination-box), अपने परिवर्तनों को बनाने के लिए local रूप से अपने repo को clone करें, उसे push कर, अपने शाखाओं से [Pull Request](https://github.com/qmk/qmk_firmware/pulls) प्रस्तुत करें।

अन्यथा, आप इसे सीधे डाउनलोड कर सकते हैं ([zip](https://github.com/qmk/qmk_firmware/zipball/master), [tar](https://github.com/qmk/qmk_firmware/tarball/master)), git के clone (`git@github.com:qmk/qmk_firmware.git`), या https (`https://github.com/qmk/qmk_firmware.git`) से।

## संकलन (कम्पाइल) कैसे करें

इससे पहले कि आप संकलन करने में सक्षम हों, आपको एक [environment स्थापित करना होगा](getting_started_build_tools.md) AVR या/और ARM विकास के लिए। एक बार पूर्ण हो जाने के बाद, आप निम्नलिखित नोटेशन के साथ कीबोर्ड और कीमैप बनाने के लिए `make` कमांड का उपयोग करेंगे:

    make planck/rev4:default
यह `default` कीमैप के साथ `planck` के `rev4` संशोधन का निर्माण करेगा। सभी कीबोर्ड में संशोधन नहीं होते हैं (जिसे सबप्रोजेक्ट या फ़ोल्डर भी कहा जाता है), जिस स्थिति में, इसे छोड़ा जा सकता है:

    make preonic:default

## कैसे अनुकूलित करें

QMK के पास बहुत सारी [विशेषताएं](features.md) और गहराई में जानने के लिए [संदर्भ दस्तावेजो](http://docs.qmk.fm) का एक अच्छा संग्रहालय है। अधिकांश विशेषताओं का उपयोग आपके [कीमैप](keymap.md), और [कीकोड](keycodes.md) को बदलकर किया जाता है।
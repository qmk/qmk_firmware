# Autocorrection

This is taken from [Pascal Getreuer's implemenation](https://getreuer.info/posts/keyboards/autocorrection/index.html), with a number of modifications. 

To enabled Autocorrection, add `AUTOCORRECTION_ENABLE = yes` to your `rules.mk` file. 

This is mostly a reproduction of Pascal's docs:

## Overview
Some words are more prone to typos than others. I have a habit of typo-ing *ouput* and *fitler*. This post describes a rudimentary autocorrection implementation that runs on your keyboard with QMK.

The animation below shows the effect as I type *aparent*. As I press the final t, the autocorrection feature detects the typo and automatically sends keys to correct it:

Example: Autocorrecting *aparent* → apparent.

**Features**:
* It runs on your keyboard, so it is always active no matter what software.
* Low resource cost: for an autocorrection dictionary of 70 entries, firmware size cost is 1620 bytes and average CPU cost per key press is about 20 µs.
* It is case insensitive. It corrects Fitler to Filter and FITLER to FILTER.
* It works within words. It corrects fitlered, fitlering, and useful for programming, within longer identifiers like DesignButterworthFitle*r.

**Limitations**: Running autocorrection on the keyboard comes with some constraints. It is rudimentary like I said:
* It is limited to alphabet characters a–z. No accented or Unicode letters; I’m sorry this probably isn’t useful for languages besides English.
* It does not follow mouse or hotkey driven cursor movement.

## Taking autocorrection for a test drive
With the above flashed to your keyboard, try for instance typing the misspelled word ouput. The instant you type the final t, the word should be speedily autocorrected to output. As further tests, try becuase and invliad.

Here is the full list of typos corrected using the provided autocorrection_data.h file. : is a special character denoting a word break. See below for how to change the autocorrection dictionary.

```
:guage        -> gauge
:the:the:     -> the
:thier        -> their
:ture         -> true
accomodate    -> accommodate
acommodate    -> accommodate
aparent       -> apparent
aparrent      -> apparent
apparant      -> apparent
apparrent     -> apparent
aquire        -> acquire
becuase       -> because
cauhgt        -> caught
cheif         -> chief
choosen       -> chosen
cieling       -> ceiling
collegue      -> colleague
concensus     -> consensus
contians      -> contains
cosnt         -> const
dervied       -> derived
fales         -> false
fasle         -> false
fitler        -> filter
flase         -> false
foward        -> forward
frequecy      -> frequency
gaurantee     -> guarantee
guaratee      -> guarantee
heigth        -> height
heirarchy     -> hierarchy
inclued       -> include
interator     -> iterator
intput        -> input
invliad       -> invalid
lenght        -> length
liasion       -> liaison
libary        -> library
listner       -> listener
looses:       -> loses
looup         -> lookup
manefist      -> manifest
namesapce     -> namespace
namespcae     -> namespace
occassion     -> occasion
occured       -> occurred
ouptut        -> output
ouput         -> output
overide       -> override
postion       -> position
priviledge    -> privilege
psuedo        -> pseudo
recieve       -> receive
refered       -> referred
relevent      -> relevant
repitition    -> repetition
reuslt        -> result
retrun        -> return
retun         -> return
reutrn        -> return
saftey        -> safety
seperate      -> separate
singed        -> signed
stirng        -> string
strign        -> string
swithc        -> switch
swtich        -> switch
thresold      -> threshold
udpate        -> update
widht         -> width
```

## Firmware size and CPU costs
I am anxiously aware that a keyboard microcontroller has limited resources. So I was sure to measure how much memory and CPU time autocorrection consumes during development. These measurements are for the example autocorrection dictionary as used above, which has 70 entries:
* **Firmware size**: Autocorrection increases my firmware size by a total of 1620 bytes. Breaking that down, 1104 bytes are for the autocorrection_data array and 516 bytes for the autocorrection code.
* **CPU time**: On my Elite-C microcontrollers, the average CPU time for process_autocorrection to process an alpha key press is around 20 µs. Consider this a rough order-of-magnitude cost. Processing cost increases (more trie nodes are visited) when recent input is close to a known typo, with the max being when a long typo is matched.

The costs are not free but reasonable. For reference, the firmware size cost for mouse keys is 2124 bytes and the CPU time to process a layer switch is about 70 µs, so autocorrection is cheaper than those things. Of course, the cost scales with the size of the autocorrection dictionary, so keep that in mind if you add a lot more entries.

## How does it work?
The function process_autocorrection maintains a small buffer of recent key presses. On each key press, it checks whether the buffer ends in a recognized typo, and if so, automatically sends keystrokes to correct it.

The tricky part is how to efficiently check the buffer for typos. We don’t want to spend too much memory or time on storing or searching the typos. A good solution is to represent the typos with a trie data structure. A trie is a tree data structure where each node is a letter, and words are formed by following a path to one of the leaves.


An example trie.
Since we search whether the buffer ends in a typo, we store the trie writing in reverse. The trie is queried starting from the last letter, then second to last letter, and so on, until either a letter doesn’t match or we reach a leaf, meaning a typo was found.

## Changing the autocorrection dictionary
The file autocorrection_data.h encodes the typos to correct. While you could simply use the version of this file provided above for a practical configuration, you can make your own to personalize the autocorrection to your most troublesome typos:

1. First, create an autocorrection dictionary autocorrection_dict.txt, like

  ```
:thier        -> their
fitler        -> filter
lenght        -> length
ouput         -> output
widht         -> width
```
  For a practical 70-entry example, see autocorrection_dict.txt. And for a yet larger 400-entry example, see autocorrection_dict_extra.txt.

  The syntax is `typo -> correction`. Typos and corrections are case insensitive, and any whitespace before or after the typo and correction is ignored. The typo must be only the letters a–z, or the special character : representing a word break. The correction may have any characters.

2. Use the make_autocorrection_data.py Python script to process the dictionary

```
$ python3 make_autocorrection_data.py
Processed 70 autocorrection entries to table with 1104 bytes.
```
The script arranges the entries in autocorrection_dict.txt into a trie and generates autocorrection_data.h with the serialized trie embedded as an array.

3. Finally, recompile and flash your keymap.

The generated C header looks like this:

autocorrection_data.h
```c
// Generated code.

#define AUTOCORRECTION_MIN_LENGTH 5  // "cheif"
#define AUTOCORRECTION_MAX_LENGTH 10  // "accomodate"

static const uint8_t autocorrection_data[1104] PROGMEM = {108, 43, 0, 6,
  71, 0, 7, 81, 0, 8, 199, 0, 9, 240, 1, 10, 250, 1, 11, 26, 2, 17, 53, 2,
  18, 190, 2, 19, 202, 2, 21, 212, 2, 22, 20, 3, 23, 67, 3, 28, 16, 4, 0,
  72, 50, 0, 22, 60, 0, 0, 11, 23, 44, 8, 11, 23, 44, 0, 132, 0, 8, 22, 18,
  18, 15, 0, 132, 115, 101, 115, 0, 11, 23, 12, 26, 22, 0, 129, 99, 104, 0,
  68, 94, 0, 8, 106, 0, 15, 174, 0, 21, 187, 0, 0, 12, 15, 25, 17, 12, 0,
  131, 97, 108, 105, 100, 0, 74, 119, 0, 12, 129, 0, 21, 140, 0, 24, 165,
  0, 0, 17, 12, 22, 0, 131, 103, 110, 101, 100, 0, 25, 21, 8, 7, 0, 131,
  105, 118, 101, 100, 0, 72, 147, 0, 24, 156, 0, 0, 9, 8, 21, 0, 129, 114,
  101, 100, 0, 6, 6, 18, 0, 129, 114, 101, 100, 0, 15, 6, 17, 12, 0, 129,
  100, 101, 0, 18, 22, 8, 21, 11, 23, 0, 130, 104, 111, 108, 100, 0, 4, 26,
  18, 9, 0, 131, 114, 119, 97, 114, 100, 0, 68, 233, 0, 6, 246, 0, 7, 4, 1,
  8, 16, 1, 10, 52, 1, 15, 81, 1, 21, 90, 1, 22, 117, 1, 23, 144, 1, 24,
  215, 1, 25, 228, 1, 0, 6, 19, 22, 8, 16, 4, 17, 0, 130, 97, 99, 101, 0,
  19, 4, 22, 8, 16, 4, 17, 0, 131, 112, 97, 99, 101, 0, 12, 21, 8, 25, 18,
  0, 130, 114, 105, 100, 101, 0, 23, 0, 68, 25, 1, 17, 36, 1, 0, 21, 4, 24,
  10, 0, 130, 110, 116, 101, 101, 0, 4, 21, 24, 4, 10, 0, 135, 117, 97,
  114, 97, 110, 116, 101, 101, 0, 68, 59, 1, 7, 69, 1, 0, 24, 10, 44, 0,
  131, 97, 117, 103, 101, 0, 8, 15, 12, 25, 12, 21, 19, 0, 130, 103, 101,
  0, 22, 4, 9, 0, 130, 108, 115, 101, 0, 76, 97, 1, 24, 109, 1, 0, 24, 20,
  4, 0, 132, 99, 113, 117, 105, 114, 101, 0, 23, 44, 0, 130, 114, 117, 101,
  0, 4, 0, 79, 126, 1, 24, 134, 1, 0, 9, 0, 131, 97, 108, 115, 101, 0, 6,
  8, 5, 0, 131, 97, 117, 115, 101, 0, 4, 0, 71, 156, 1, 19, 193, 1, 21,
  203, 1, 0, 18, 16, 0, 80, 166, 1, 18, 181, 1, 0, 18, 6, 4, 0, 135, 99,
  111, 109, 109, 111, 100, 97, 116, 101, 0, 6, 6, 4, 0, 132, 109, 111, 100,
  97, 116, 101, 0, 7, 24, 0, 132, 112, 100, 97, 116, 101, 0, 8, 19, 8, 22,
  0, 132, 97, 114, 97, 116, 101, 0, 10, 8, 15, 15, 18, 6, 0, 130, 97, 103,
  117, 101, 0, 8, 12, 6, 8, 21, 0, 131, 101, 105, 118, 101, 0, 12, 8, 11,
  6, 0, 130, 105, 101, 102, 0, 17, 0, 76, 3, 2, 21, 16, 2, 0, 15, 8, 12, 6,
  0, 133, 101, 105, 108, 105, 110, 103, 0, 12, 23, 22, 0, 131, 114, 105,
  110, 103, 0, 70, 33, 2, 23, 44, 2, 0, 12, 23, 26, 22, 0, 131, 105, 116,
  99, 104, 0, 10, 12, 8, 11, 0, 129, 104, 116, 0, 72, 69, 2, 10, 80, 2, 18,
  89, 2, 21, 156, 2, 24, 167, 2, 0, 22, 18, 18, 11, 6, 0, 131, 115, 101,
  110, 0, 12, 21, 23, 22, 0, 129, 110, 103, 0, 12, 0, 86, 98, 2, 23, 124,
  2, 0, 68, 105, 2, 22, 114, 2, 0, 12, 15, 0, 131, 105, 115, 111, 110, 0,
  4, 6, 6, 18, 0, 131, 105, 111, 110, 0, 76, 131, 2, 22, 146, 2, 0, 23, 12,
  19, 8, 21, 0, 134, 101, 116, 105, 116, 105, 111, 110, 0, 18, 19, 0, 131,
  105, 116, 105, 111, 110, 0, 23, 24, 8, 21, 0, 131, 116, 117, 114, 110, 0,
  85, 174, 2, 23, 183, 2, 0, 23, 8, 21, 0, 130, 117, 114, 110, 0, 8, 21, 0,
  128, 114, 110, 0, 7, 8, 24, 22, 19, 0, 131, 101, 117, 100, 111, 0, 24,
  18, 18, 15, 0, 129, 107, 117, 112, 0, 72, 219, 2, 18, 3, 3, 0, 76, 229,
  2, 15, 238, 2, 17, 248, 2, 0, 11, 23, 44, 0, 130, 101, 105, 114, 0, 23,
  12, 9, 0, 131, 108, 116, 101, 114, 0, 23, 22, 12, 15, 0, 130, 101, 110,
  101, 114, 0, 23, 4, 21, 8, 23, 17, 12, 0, 135, 116, 101, 114, 97, 116,
  111, 114, 0, 72, 30, 3, 17, 38, 3, 24, 51, 3, 0, 15, 4, 9, 0, 129, 115,
  101, 0, 4, 12, 23, 17, 18, 6, 0, 131, 97, 105, 110, 115, 0, 22, 17, 8, 6,
  17, 18, 6, 0, 133, 115, 101, 110, 115, 117, 115, 0, 74, 86, 3, 11, 96, 3,
  15, 118, 3, 17, 129, 3, 22, 218, 3, 24, 232, 3, 0, 11, 24, 4, 6, 0, 130,
  103, 104, 116, 0, 71, 103, 3, 10, 110, 3, 0, 12, 26, 0, 129, 116, 104, 0,
  17, 8, 15, 0, 129, 116, 104, 0, 22, 24, 8, 21, 0, 131, 115, 117, 108,
  116, 0, 68, 139, 3, 8, 150, 3, 22, 210, 3, 0, 21, 4, 19, 19, 4, 0, 130,
  101, 110, 116, 0, 85, 157, 3, 25, 200, 3, 0, 68, 164, 3, 21, 175, 3, 0,
  19, 4, 0, 132, 112, 97, 114, 101, 110, 116, 0, 4, 19, 0, 68, 185, 3, 19,
  193, 3, 0, 133, 112, 97, 114, 101, 110, 116, 0, 4, 0, 131, 101, 110, 116,
  0, 8, 15, 8, 21, 0, 130, 97, 110, 116, 0, 18, 6, 0, 130, 110, 115, 116,
  0, 12, 9, 8, 17, 4, 16, 0, 132, 105, 102, 101, 115, 116, 0, 83, 239, 3,
  23, 6, 4, 0, 87, 246, 3, 24, 254, 3, 0, 17, 12, 0, 131, 112, 117, 116, 0,
  18, 0, 130, 116, 112, 117, 116, 0, 19, 24, 18, 0, 131, 116, 112, 117,
  116, 0, 70, 29, 4, 8, 41, 4, 11, 51, 4, 21, 69, 4, 0, 8, 24, 20, 8, 21,
  9, 0, 129, 110, 99, 121, 0, 23, 9, 4, 22, 0, 130, 101, 116, 121, 0, 6,
  21, 4, 21, 12, 8, 11, 0, 135, 105, 101, 114, 97, 114, 99, 104, 121, 0, 4,
  5, 12, 15, 0, 130, 114, 97, 114, 121, 0};
```

## Troubleshooting
### Avoiding false triggers
By default, typos are searched within words, to find typos within longer identifiers like maxFitlerOuput. While this is useful, a consequence is that autocorrection will falsely trigger when a typo happens to be a substring of a correctly-spelled word. For instance, if we had thier -> their as an entry, it would falsely trigger on (correct, though relatively uncommon) words like “wealthier” and “filthier.”

The solution is to set a word break : before and/or after the typo to constrain matching. : matches space, period, comma, underscore, digits, and most other non-alpha characters.

| Text | thier | :thier | thier: | :thier: |
|------|-------|--------|--------|---------|
|see thier typo|matches|matches|matches|matches|
it’s thiers    |matches|matches|no|no|
wealthier words|matches|no|matches|no|

:thier: is most restrictive, matching only when thier is a whole word.

The make_autocorrection_data.py script makes an effort to check for entries that would false trigger as substrings of correct words. It searches each typo against a dictionary of 25K English words from the english_words Python package, provided it’s installed.

### Overriding autocorrection
Occasionally you might actually want to type a typo (for instance, while editing autocorrection_dict.txt) without being autocorrected. Here is a way to do that:

1. Begin typing the typo.
2. Before typing the last letter, press and release the Ctrl or Alt key.
3. Type the remaining letters.

This works because the autocorrection implementation doesn’t understand hotkeys, so it resets itself whenever a modifier other than shift is held.

Alternatively, the `AUTO_CTN` keycode will toggle autocorrection on and off.

## Closing thoughts
Based on my own use, an autocorrection dictionary of a few dozen entries is enough to help in day-to-day writing. On the other hand, it is of course far from comprehensively checking that every word is spelled correctly. Keyboard microcontrollers might not have the resources check against a full English dictionary any time soon, but a lot of editors and other software have good integrated spell check features.

I suggest to enable and use spell check in combination with autocorrection:
* Sublime: Open the View menu and enable “Spell Check.”
* Eclipse: Open the Window menu, click Preferences, and search for “Spelling.”
* Vim: Type :set spell, and misspellings will be highlighted. Use ]s to jump to the next misspelled word and z= to get suggested corrections for the word under the cursor. See the :help spell documentation. Vim also has an abbreviations feature that can autocorrect misspellings (see :help abbreviations).
* Emacs: Use M-x flyspell-mode to enable Flyspell mode in the current buffer. Or for programming, use M-x flyspell-prog-mode to check comments and strings only. See the spelling documentation. There is also an abbreviations feature that can do autocorrection.

Some useful resources:

* Wikipedia has a [large list of common typos](https://en.wikipedia.org/wiki/Wikipedia:Lists_of_common_misspellings/For_machines).
* EmacsWiki has another [list of typos](https://www.emacswiki.org/emacs/autocorrection_abbrev_defs).
* You can find data on English word frequencies at https://www.wordfrequency.info/samples.asp.

# Appendix: Trie binary data format
This section details how the trie is serialized to byte data in autocorrection_data. You don’t need to care about this to use this autocorrection implementation. But I document it for the record in case anyone is interested in modifying the implementation, or just curious how it works.

What I did here is fairly arbitrary, but it is simple to decode and gets the job done.

## Encoding
All autocorrection data is stored in a single flat array autocorrection_data. Each trie node is associated with a byte offset into this array, where data for that node is encoded, beginning with root at offset 0. There are three kinds of nodes. The highest two bits of the first byte of the node indicate what kind:

* 00 ⇒ chain node: a trie node with a single child.
* 01 ⇒ branching node: a trie node with multiple children.
* 10 ⇒ leaf node: a leaf, corresponding to a typo and storing its correction.

An example trie.
Branching node. Each branch is encoded with one byte for the keycode (KC_A–KC_Z) followed by a link to the child node. Links between nodes are 16-bit byte offsets relative to the beginning of the array, serialized in little endian order.

All branches are serialized this way, one after another, and terminated with a zero byte. As described above, the node is identified as a branch by setting the two high bits of the first byte to 01, done by bitwise ORing the first keycode with 64. keycode. The root node for the above figure would be serialized like:

    +-------+-------+-------+-------+-------+-------+-------+
    | R|64  |    node 2     |   T   |    node 3     |   0   |
    +-------+-------+-------+-------+-------+-------+-------+

Chain node. Tries tend to have long chains of single-child nodes, as seen in the example above with f-i-t-l in fitler. So to save space, we use a different format to encode chains than branching nodes. A chain is encoded as a string of keycodes, beginning with the node closest to the root, and terminated with a zero byte. The child of the last node in the chain is encoded immediately after. That child could be either a branching node or a leaf.

In the figure above, the f-i-t-l chain is encoded as

    +-------+-------+-------+-------+-------+
    |   L   |   T   |   I   |   F   |   0   |
    +-------+-------+-------+-------+-------+
If we were to encode this chain using the same format used for branching nodes, we would encode a 16-bit node link with every node, costing 8 more bytes in this example. Across the whole trie, this adds up. Conveniently, we can point to intermediate points in the chain and interpret the bytes in the same way as before. E.g. starting at the i instead of the l, and the subchain has the same format.

Leaf node. A leaf node corresponds to a particular typo and stores data to correct the typo. The leaf begins with a byte for the number of backspaces to type, and is followed by a null-terminated ASCII string of the replacement text. The idea is, after tapping backspace the indicated number of times, we can simply pass this string to QMK’s send_string_P function. For fitler, we need to tap backspace 3 times (not 4, because we catch the typo as the final ‘r’ is pressed) and replace it with lter. To identify the node as a leaf, the two high bits are set to 10 by ORing the backspace count with 128:

    +-------+-------+-------+-------+-------+-------+
    | 3|128 |  'l'  |  't'  |  'e'  |  'r'  |   0   |
    +-------+-------+-------+-------+-------+-------+
## Decoding
This format is by design decodable with fairly simple logic. A 16-bit variable state represents our current position in the trie, initialized with 0 to start at the root node. Then, for each keycode, test the highest two bits in the byte at state to identify the kind of node.

* 00 ⇒ chain node: If the node’s byte matches the keycode, increment state by one to go to the next byte. If the next byte is zero, increment again to go to the following node.
* 01 ⇒ branching node: Search the branches for one that matches the keycode, and follow its node link.
* 10 ⇒ leaf node: a typo has been found! We read its first byte for the number of backspaces to type, then pass its following bytes to send_string_P to type the correction.

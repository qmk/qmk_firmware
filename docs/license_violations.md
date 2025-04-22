# License Violations

QMK Firmware has seen its fair share of license violations, which hurts the community and frustrates the QMK maintainers.

Typical non-compliance includes:

* Not providing any source code
* Providing "crippled" source code, such as a wired-only firmware for a wireless-capable board

Boards from vendors who don't provide source code are proving to be a significant time sink as the QMK team and other support helpers volunteer their time trying to determine which board someone has before they can help -- and in these cases they can't help. Occasionally this is followed by abuse; something that QMK and its volunteers should not be subjected to, rather redirected to the vendor in question.

The QMK team now actively directs support requests back to each vendor - vendors must provide their own product support for their boards. The QMK team are volunteers, the vendor must not expect the team to act as their support staff.

## Offending Vendors

The QMK team cannot tell you which boards you should or should not purchase, but please consider the lack of license compliance from the following vendors before making your decision. If you wish to look at the boards upstream QMK Firmware currently supports, you can search [here](https://browse.qmk.fm/).

If you own a board from one of the following vendors already, consider asking them for the equivalent QMK source code if it's not already available. With enough customers demanding corresponding source code, vendors may start to change their policies.

| Vendor                       | Reason                                                                                                                                                                                                                                                                                                                              |
|------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Ajazz                        | Selling tri-mode boards based on QMK without sources.                                                                                                                                                                                                                                                                               |
| Alpaca / Apos                | Selling wireless boards with "open" source code, but linking against closed-source wireless libraries. Crippled source code already unknowingly merged to QMK.                                                                                                                                                                      |
| Attack Shark                 | Selling tri-mode boards based on QMK without sources. (Clones of Ajazz?)                                                                                                                                                                                                                                                            |
| BBB Keyboard                 | Selling tri-mode boards based on QMK without sources, attempted upstreaming crippled firmware without wireless.                                                                                                                                                                                                                     |
| Chosfox                      | Selling L75 wired/wireless boards based on QMK without sources, just `via.json` provided. Raised on discord over multiple weeks without response.                                                                                                                                                                                   |
| CIDOO                        | Selling wired boards based on QMK without sources, just `via.json` provided.                                                                                                                                                                                                                                                        |
| ColorReco                    | Selling tri-mode boards based on QMK without sources.                                                                                                                                                                                                                                                                               |
| Darmoshark                   | Selling wired boards based on QMK without sources, just `via.json` provided.                                                                                                                                                                                                                                                        |
| Epomaker                     | Lots of historical keyboards with `via.json` but no corresponding sources. Wireless code for a small handful provided, pending core cleanup for QMK upstreaming. Most other boards have source nowhere to be seen.                                                                                                                  |
| Ergokbd (IFKB)               | At least their crkbd clone ships with QMK+Vial, seemingly refuses to disclose sources despite multiple customers requesting them.                                                                                                                                                                                                   |
| iLovBee                      | Official 30-day copyright source code request issued Sep 11 2024 due to deception on PR, no response received. Ambiguity on PRs -- marketing says wireless, PR author said wired-only, then included wireless code anyway. Seemingly intentionally deceptive.                                                                       |
| KiiBOOM                      | Seems to use the same OEM as Epomaker, same problems.                                                                                                                                                                                                                                                                               |
| kprepublic                   | Makes no attempt to release source code, all boards in QMK are reverse-engineered, created, and supported by the community. New board variants magically appear without telling customers they're incompatible with existing QMK versions, in some cases bricking boards or requiring ISP flashing.                                 |
| Luminkey                     | Selling tri-mode boards based on QMK without sources, just `via.json` provided.                                                                                                                                                                                                                                                     |
| Meletrix                     | Selling tri-mode boards based on QMK without sources, just `via.json` provided.                                                                                                                                                                                                                                                     |
| mmd / Smartmmd / i-game.tech | Ambiguity on PRs -- marketing says wireless, PR author said wired-only, then included wireless code anyway. Seemingly intentionally deceptive.                                                                                                                                                                                      |
| MyKeyClub                    | Community-supported JRIS75, vendor was contacted by community members and refused to cooperate.                                                                                                                                                                                                                                     |
| owlab                        | Selling wired based on QMK without sources, just `via.json` provided. Ambiguous as to whether or not wireless firmware is based on QMK, given that their configuration tool looks very similar to VIA.                                                                                                                              |
| pressplayid                  | Selling wired and tri-mode boards based on QMK without sources, just `via.json` provided                                                                                                                                                                                                                                            |
| qwertykeys                   | Selling wired and tri-mode boards based on QMK without sources, just `via.json` provided.                                                                                                                                                                                                                                           |
| Redragon                     | Selling tri-mode boards based on QMK without sources, attempted upstreaming crippled firmware without wireless.                                                                                                                                                                                                                     |
| Riccks                       | Selling tri-mode boards based on QMK without sources.                                                                                                                                                                                                                                                                               |
| Royal Kludge                 | PRs for fake boards in order to attain VIA compatibility identified. Lots of other keyboards with `via.json` but no corresponding sources, attempted upstreaming crippled firmware without wireless. Wireless code for some provided, pending core cleanup for QMK upstreaming. PRs including different manufacturer names as well. |
| Shenzhen Hangsheng           | PR submissions with crippled firmware, debating with maintainers about wireless despite marketing material clearly stating tri-mode.                                                                                                                                                                                                |
| Tacworks                     | Selling tri-mode boards based on QMK, crippled firmware already merged into QMK without wireless without QMK team realising.                                                                                                                                                                                                        |
| TKD / Vertex                 | Selling tri-mode boards based on QMK without sources, attempted upstreaming crippled firmware without wireless.                                                                                                                                                                                                                     |
| WOBKEY                       | Selling tri-mode boards based on QMK without sources, attempted upstreaming crippled firmware without wireless.                                                                                                                                                                                                                     |
| Weikav                       | Selling tri-mode boards based on QMK without sources, just `via.json` provided.                                                                                                                                                                                                                                                     |
| Womier                       | Selling tri-mode boards based on QMK without sources, attempted upstreaming crippled firmware without wireless.                                                                                                                                                                                                                     |
| Wuque Studio                 | Selling wired and tri-mode boards based on QMK without sources, just `via.json` provided.                                                                                                                                                                                                                                           |
| XVX                          | Ambiguity on PRs -- marketing says wireless, PR author said wired-only. Seemingly intentionally deceptive.                                                                                                                                                                                                                          |
| Yunzii                       | Selling tri-mode boards based on QMK without sources, just `via.json` provided.                                                                                                                                                                                                                                                     |
| Zuoya                        | Selling tri-mode boards based on QMK without sources, just `via.json` provided.                                                                                                                                                                                                                                                     |

::: danger Violations
Links are not provided above as the QMK team does not wish to inadvertently promote purchases of boards in violation of QMK's license.
:::

## Licensing

QMK Firmware's license requires full disclosure of source code for any firmware which is based on QMK. This includes any of the following scenarios:

* Use of public QMK Firmware, but with "closed source" privately-held board definitions
* Vendor-customised QMK Firmware, which the vendor keeps private for building their own boards
* Any other non-QMK firmware which includes portions of QMK Firmware, such as adaptation of `via.c` into any other non-QMK firmware, even if used as a reference when translated to another programming language.

As per the GPL license requirements, vendors must provide entire source code for the as-shipped firmware.

QMK has traditionally been lenient with this clause -- providing source code to the QMK community is necessary but reproducing the exact build may not be possible. QMK has required functionally-equivalent source code to be made available. In rare cases exact code may be requested; vendors must keep copies regardless.

At minimum, vendors must provide the source code through some distribution mechanism. This could potentially be an clearly available downloadable copy of the code online, a fork of QMK Firmware, or even a DVD accompanying the product in the box.

If sources are unable to be provided in a timely fashion, QMK may revoke the vendor's license, effectively rendering them unable to leverage QMK.

Vendors choosing to keep things closed-source because of a desire to have a "competitive edge" compared to other vendors is unacceptable to both QMK and the community, and is a breach of the QMK license. There's no reason to do so; any new or interesting vendor-specific feature will be quickly replicated by other vendors or the community anyway.

## QMK PR Considerations

Vendors who submit PRs to QMK Firmware whilst not providing full sources for all of their license-violating boards will be put on hold until source code for all violating boards is provided. Intentional deception may result in boards being removed from QMK and all future PRs for that manufacturer being denied outright.

Submitting crippled source code in order to attain a merge into QMK Firmware to pave the way for VIA support is unacceptable. This includes submitting a wired-only firmware for a wireless-capable board, or any other PR which does not include key features as-advertised.

Reusing the `VID` and `PID` for multiple boards (such as for two variants, wired and wireless) is an unacceptable scenario as this creates confusion for support. Many customers have flashed boards with the wrong firmware, which could have been avoided if vendors were obvious about their board identification mechanisms.

If there is sufficient ambiguity about a board, supporting evidence will need to be presented to the QMK team. This may include impartial third parties who can demonstrate a board's existence and can confirm its feature set, such as well-known content producers; popular review sites or notable video creators may be leveraged. If such evidence is unavailable, as a last resort the vendor may be required to ship a fully functional board in full retail packaging to QMK maintainers for verification. Engineering samples will not be accepted, as one-off boards have been deceptively used in the past.

PRs submitted to upstream QMK should not expect an instant merge just because source code has been provided -- code from OEMs has historically been of a quality lower than QMK standards, so as per the [PR checklist](pr_checklist) submitters should make the changes as small as possible and be prepared to change their implementation.

## Detection

If the QMK team identifies or is informed of a license violation from a vendor:

* Any current and future PRs for that vendor will be indefinitely put on hold, preventing merge into QMK Firmware, thus preventing any out-of-the-box VIA support
* Any existing keyboards from the vendor may be removed from QMK Firmware
* Vendors will be added to the _offending vendors_ list above

Repeated violations may result in that vendor being disallowed from contributing the QMK in its entirety. In the worst case, the QMK team may choose to revoke a vendor's license to use QMK Firmware outright.

## Remediation

Vendors must provide fully-featured source code for each of their identified violations, matching the feature capabilities of their as-shipped products. This will usually be in their own fork of QMK Firmware while awaiting a merge into upstream.

Once all identified violations have been remediated, current and future PRs will no longer be on hold and the vendor will be removed from the offending vendors list above.

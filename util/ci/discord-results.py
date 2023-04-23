#!/usr/bin/env python3

import argparse
import os
import re
import sys
from pathlib import Path
from discord_webhook import DiscordWebhook, DiscordEmbed

parser = argparse.ArgumentParser(prog='discord-results.py', description='Sends a Discord webhook notification at the end of a CI run.')
parser.add_argument('-b', '--branch')
parser.add_argument('-k', '--keymap')
parser.add_argument('-u', '--url')
args = parser.parse_args()

qmk_dir = Path(__file__).resolve().parents[2].resolve()

keyboard_re = re.compile(r'CI Metadata: KEYBOARD=(.*)$', re.MULTILINE)
keymap_re = re.compile(r'CI Metadata: KEYMAP=(.*)$', re.MULTILINE)

successful_builds = sum([len(list(qmk_dir.glob(f'*.{extension}'))) for extension in ['uf2', 'bin', 'hex']])
failures = list(sorted([f.resolve() for f in (qmk_dir / '.build/').glob('failed.log.*')]))
failed_builds = []
for f in failures:
    with open(f) as fh:
        data = fh.read()
        kb = keyboard_re.search(data).group(1)
        km = keymap_re.search(data).group(1)
        failed_builds.append(f'{kb}:{km}')

webhook = DiscordWebhook(url=os.getenv('DISCORD_WEBHOOK'), username="QMK GitHub CI")
if len(failed_builds) > 0:
    failstr = ''
    for f in failed_builds:
        if len(failstr) >= 1800:
            failstr += '<<snip>>'
            break
        failstr += f'{f}\n'

    embed = DiscordEmbed(title=f':infinity: CI Build Failure ({args.branch}, {args.keymap})', description=f'**{successful_builds}** builds succeeded, **{len(failed_builds)}** builds failed:```{failstr}```', color='ff9999')
else:
    embed = DiscordEmbed(title=f':infinity: CI Build Success ({args.branch}, {args.keymap})', description=f'**{successful_builds}** builds succeeded.', color='99ff99')

embed.add_embed_field(name='Build Target', value=f'[**{args.branch}**](https://github.com/qmk/qmk_firmware/tree/{args.branch}) / **{args.keymap}** keymap')
embed.add_embed_field(name='Workflow Run', value=f'[**Link**]({args.url})')
embed.set_timestamp()

webhook.add_embed(embed)
webhook.execute()

import sys
import subprocess
import os

class Command:
    def __init__(self, kb, km) -> None:
        self.kb = kb
        self.km = km
        self.arguments = []

    def prepend_argument(self, argument):
        self.arguments.insert(0, argument)
        self.arguments.insert(0, '-e')

    def add_argument(self, argument):
        self.arguments.append('-e')
        self.arguments.append(argument)

    def add_argument_raw(self, argument):
        self.arguments.append(argument)

    def build(self):
        return ' '.join(self.build_list())

    def build_list(self):
        return ['make', f'{self.kb}:{self.km}'] + self.arguments

    def file_name(self):
        parts = []
        parts.append(self.kb.replace('/', '_'))
        parts.append(self.km)
        for argument in self.arguments:
            if argument.startswith('POINTING_DEVICE='):
                pointing_device = argument[len('POINTING_DEVICE='):]
                parts.append(pointing_device)
            elif argument.startswith('SIDE='):
                side = argument[len('SIDE='):]
                parts.append(side)
            elif argument.startswith('POINTING_DEVICE_POSITION='):
                pointing_device_position = argument[len('POINTING_DEVICE_POSITION='):]
                parts.append(pointing_device_position)
            elif argument.startswith('OLED='):
                parts.append('oled')
            elif argument.startswith('OLED_FLIP='):
                pass # parts.append('flip')
        return '_'.join(parts)

def build_commands():
    commands = []
    for kb in ['crkbd/rev1', 'idank/spankbd', 'lily58/rev1', 'idank/sweeq']:
        for left_pointing_device in ['trackpoint', 'trackball', 'cirque35', 'cirque40', '']:
            for right_pointing_device in ['trackpoint', 'trackball', 'cirque35', 'cirque40', '']:
                if left_pointing_device == 'trackpoint' and right_pointing_device == 'trackpoint':
                    continue
                if left_pointing_device and right_pointing_device:
                    for side in ('left', 'right'):
                        command = Command(kb, 'via')
                        command.add_argument(f'POINTING_DEVICE={left_pointing_device}_{right_pointing_device}')
                        command.add_argument(f'SIDE={side}')
                        if (left_pointing_device == 'trackball' and side == 'left') \
                            or (right_pointing_device == 'trackball' and side == 'right'):
                            command.add_argument(f'TRACKBALL_RGB_RAINBOW=yes')
                        commands.append(command)
                else:
                    for with_oled in [True, False]:
                        command = Command(kb, 'via')
                        if with_oled:
                            command.add_argument(f'OLED=yes')
                            command.add_argument(f'OLED_FLIP=yes')
                        if left_pointing_device:
                            command.add_argument(f'POINTING_DEVICE={left_pointing_device}')
                            command.add_argument(f'POINTING_DEVICE_POSITION=left')
                            if left_pointing_device == 'trackball':
                                command.add_argument(f'TRACKBALL_RGB_RAINBOW=yes')
                        elif right_pointing_device:
                            command.add_argument(f'POINTING_DEVICE={right_pointing_device}')
                            command.add_argument(f'POINTING_DEVICE_POSITION=right')
                            if right_pointing_device == 'trackball':
                                command.add_argument(f'TRACKBALL_RGB_RAINBOW=yes')
                        else:
                            pass

                        commands.append(command)

    return commands

def main() -> int:
    reviung_command = Command('reviung/reviung41', 'via')
    reviung_command.prepend_argument('USER_NAME=idank')
    reviung_command.add_argument('POINTING_DEVICE_POSITION=middle')
    reviung_command.add_argument('POINTING_DEVICE=trackball')
    reviung_command.add_argument('TRACKBALL_RGB_RAINBOW=yes')

    commands = [
        Command('keyball/keyball39', 'via'),
        Command('keyball/keyball44', 'via'),
        Command('keyball/keyball61', 'via'),
    ]
    commands.append(reviung_command)
    for command in build_commands():
        command.prepend_argument('USER_NAME=idank')
        commands.append(command)

    os.makedirs('build_all', exist_ok=True)
    commands_file = open('build_all/commands.txt', 'w')
    for command in commands:
        command.add_argument_raw('-j20')
        command.prepend_argument(f'TARGET={command.file_name()}')
        print(f'Making {command.file_name()}: {command.build()}')
        run_command_check_output(command.build().split())
        # move the file to buid_all
        os.rename(f'{command.file_name()}.uf2', 'build_all/' + f'{command.file_name()}.uf2')
        commands_file.write(f'{command.file_name()}: {command.build()}\n')
    return 0

def run_command_check_output(command):
    print(f'Running: {command}')
    output = subprocess.check_output(command)
    return output

if __name__ == '__main__':
    sys.exit(main())

import random


def main():
    print("#define BUILD_ID ((uint32_t)0x{:08X})".format(random.randrange(0, 2 ** 24 - 1)))


if __name__ == "__main__":
    main()

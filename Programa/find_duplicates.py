import sys


def main():
    if len(sys.argv) < 1:
        print("Specify file")
        return

    with open(sys.argv[1]) as f:
        seen = set()
        for line in f:
            line_lower = line.lower()
            if line_lower in seen:
                print(line)
            else:
                seen.add(line_lower)


if __name__ == '__main__':
    main()

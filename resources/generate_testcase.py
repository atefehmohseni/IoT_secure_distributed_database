import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--type', '-t', type=str, choices=['read', 'write', 'delete'],
                    required=True, action='store', help='Type of testcase to generate')
args = parser.parse_args()

if args.type == 'read':
    with open('../test/read_testcase.txt', 'w') as f:
        for i in range(100):
            f.write('r\n')
            f.write(f'key{i}\n')
        f.write('q\n')
elif args.type == 'write':
    with open('../test/write_testcase.txt', 'w') as f:
        for i in range(100):
            f.write('w\n')
            f.write(f'key{i}\n')
            f.write(f'value{i}\n')
        f.write('q\n')
elif args.type == 'delete':
    with open('../test/delete_testcase.txt', 'w') as f:
        for i in range(100):
            f.write('r\n')
            f.write(f'key{i}\n')
        f.write('q\n')
import re
import sys

from src.generate_get_instruction import OPS

file_path = sys.argv[1]
ops = set(OPS)

with open(file_path) as reader:
    lines = []
    for line in reader:
        line = re.sub(r'^\d+', '', line).strip()
        if line.startswith('*') or len(line) == 0:
            lines.append(line)
            continue
        first, rest = line.split(' ', 1)
        if first in ops:
            loc, op = '', first
            rest = rest.split(' ', 1)
            address, comment = rest[0], ''
            if len(rest) > 1:
                comment = rest[1]
        else:
            loc = first
            rest = rest.split(' ', 2)
            op, address, comment = rest[0], rest[1], ''
            if len(rest) > 2:
                comment = rest[2]
        line = loc
        line += ' ' * (8 - len(line))
        line += op
        line += ' ' * (13 - len(line))
        line += address
        line += ' ' * (32 - len(line))
        line += comment
        line = line.rstrip()
        lines.append(line)

with open(file_path, 'w') as writer:
    for line in lines:
        writer.write(line + '\n')

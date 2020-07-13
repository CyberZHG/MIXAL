MIXAL
=====

![Unit Tests](https://github.com/CyberZHG/MIXAL/workflows/Unit%20Tests/badge.svg)
[![Deploy](https://github.com/CyberZHG/MIXAL/workflows/Deploy/badge.svg)](https://cyberzhg.github.io/MIXAL/)
[![Build Status](https://travis-ci.org/CyberZHG/MIXAL.svg?branch=master)](https://travis-ci.org/CyberZHG/MIXAL)
[![Coverage Status](https://coveralls.io/repos/github/CyberZHG/MIXAL/badge.svg?branch=master)](https://coveralls.io/github/CyberZHG/MIXAL?branch=travis)
[![Version](https://img.shields.io/pypi/v/mixal.svg)](https://pypi.org/project/mixal/)
![Downloads](https://img.shields.io/pypi/dm/mixal.svg)
![License](https://img.shields.io/pypi/l/keras-bert.svg)

\[[中文](https://github.com/CyberZHG/MIXAL/blob/master/README.zh-CN.md)|[English](https://github.com/CyberZHG/MIXAL/blob/master/README.md)\]

[MIX](https://en.wikipedia.org/wiki/MIX)汇编语言模拟器。

## 安装

确定系统中有较新的C++编译器，然后执行：

```bash
pip install mixal
```

如果是MacOS的用户，可能需要加上环境变量：

```bash
MACOSX_DEPLOYMENT_TARGET=10.9 pip install mixal
```

## 示例

一段找最大值的代码：

```python
import random
import mixal

# 初始化一个执行环境
computer = mixal.Computer()

# 寄存器J的调用位置
end_point = 3500

# 加载一段汇编代码，在最后将寄存器J的位置设置为HLT，以确保函数执行结束后可以停机
computer.loadCodes([
    'X       EQU  1000',
    '        ORIG 3000',
    'MAXIMUM STJ  EXIT',
    'INIT    ENT3 0,1',
    '        JMP  CHANGEM',
    'LOOP    CMPA X,3',
    '        JGE  *+3',
    'CHANGEM ENT2 0,3',
    '        LDA  X,3',
    '        DEC3 1',
    '        J3P  LOOP',
    'EXIT    JMP  *',
    '        ORIG {}'.format(end_point),
    '        HLT',
])

num_numbers, max_val = 100, 0
# 寄存器I1存储了数字的个数
computer.rI1.set(num_numbers)
# 寄存器J存储了返回位置
computer.rJ.set(end_point)
for i in range(1001, 1001 + num_numbers):
    val = random.randint(0, 100000)
    # 为环境内容设置随机值
    computer.memoryAt(i).set(val)
    max_val = max(max_val, val)
# 不断运行直到遇到HLT指令
computer.executeUntilHalt()
print('Expected:', max_val)
# 寄存器A中包含了最大值结果
print('Actual:', computer.rA.value())
# 执行这段代码消耗的单位时间，不包含最后的HLT
print('Compute Cost:', computer.elapsed())
```

import os
import codecs
import platform
from setuptools import setup, find_packages, Extension

current_path = os.path.abspath(os.path.dirname(__file__))


def read_file(*parts):
    with codecs.open(os.path.join(current_path, *parts), 'r', 'utf8') as reader:
        return reader.read()


def get_requirements(*parts):
    with codecs.open(os.path.join(current_path, *parts), 'r', 'utf8') as reader:
        return list(map(lambda x: x.strip(), reader.readlines()))


sources = []
for source_dir in ['src', 'deps/UChar/src']:
    for name in os.listdir(source_dir):
        if name.endswith('.cpp') or name.endswith('.cxx'):
            sources.append(os.path.join(source_dir, name))

extra_compile_args = ['-std=c++11']
if platform.system() == 'Darwin':
    extra_compile_args.append('-stdlib=libc++')
ext_module = Extension(
    '_mixal',
    sources=sources,
    include_dirs=['include', 'deps/UChar/include'],
    extra_compile_args=extra_compile_args,
)

setup(
    name='mixal',
    version='1.157.5',
    ext_modules=[ext_module],
    packages=find_packages(),
    url='https://github.com/CyberZHG/MIXAL',
    license='MIT',
    author='CyberZHG',
    author_email='CyberZHG@users.noreply.github.com',
    description='MIX Assembly Language Simulator',
    long_description=read_file('README.md'),
    long_description_content_type='text/markdown',
    install_requires=get_requirements('requirements.txt'),
    classifiers=(
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ),
)

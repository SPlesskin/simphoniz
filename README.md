[![SPlesskin](https://circleci.com/gh/SPlesskin/simphoniz.svg?style=svg)](https://circleci.com/gh/SPlesskin/simphoniz)

# Simphoniz

Simphoniz is a command-line tool which allows sorting photos according to their creation time. It
uses [EXIF metadata](https://en.wikipedia.org/wiki/Exif) to arrange files in a chronological folder
structure.

## Installation

Simphoniz is a [Qt 5](https://www.qt.io/) application which has been developped and mainly tested on
Linux Debian Stretch (Debian 9). [CMake](https://cmake.org/) 3.7 or higher and a C++14 compiler are
required to build the project. Moreover, it depends on the [Genepy](https://github.com/SPlesskin/genepy)
library which must be installed beforehand.

```bash
cd external
mkdir build && cd build
cmake -G"Unix Makefiles" -DSIMPHONIZ_EXTERNAL_BUILD_TYPE=Release ..
make
cd ../..
mkdir build && cd build
cmake -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
sudo make install
```

## Usage

<p align="center">
    <img src="resources/images/demo.svg?sanitize=true" alt="simphoniz demo" />
</p>

## Support

If you have any questions, please send an email to <erwan.grace@outlook.fr>.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would
like to change.

Please make sure to update the tests as appropriate.

## License

[GNU GPL v3.0](https://choosealicense.com/licenses/gpl-3.0/)

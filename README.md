# PS3 Update File Swapper

Something I whipped up in about 4 hours to make a cool swappable "PS3 Update file" system.

## Requirements

* C++ compiler that supports C++ 17 or above
* CMake

## Build

The program makes use of the CMake build system.
You can compile on Linux as follows:

```bash
git clone
cmake . -B build
cd build
make
```

the resulting executable will be located in `build/dist` folder.

### Note

For the executable to function as intended on Linux, please mount the update FAT32 partition with the `exec` option. By default, binaries in FAT32 partitions are not executable.

```bash
sudo mount -o exec /dev/sdX#
```

## File Structure

Set up the files as follows:

```text
|- PS3UpdateSwapper (The executable)
|- HFW_PS3UPDAT.PUP
|- CFW_PS3UPDAT.PUP
```

The executable will take turns renaming OFW and HFW files into `PS3UPDAT.PUP`. The current file is tracked through the `Current-is-*FW` file created. The file's name allows seeing which file is currently named `PS3UPDAT.PUP`. The `Current-is-*FW` file itself is empty, only the name matters.

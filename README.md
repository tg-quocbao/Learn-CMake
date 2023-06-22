# Learn-CMake

## Giới thiệu CMake
Trong bài viết này mình sẽ trình bày các ví dụ đơn giản và mang tính ứng dụng cao trong việc áp dụng CMake để xây dựng một project C++. Các ví dụ mình đều thực hiện trên Ubuntu.

Tiện ích **make** và **Makefiles** cung cấp một hệ thống build mà chúng ta có thể sử dụng để quản lý việc compile và re-compilation của một chương trình được viết bằng ngôn ngữ bất kỳ. Việc sử dụng Makefiles đôi khi lại có thể trở thành một công việc phức tạp trong trường hợp project mà chúng ta build có nhiều sub directories hoặc sẽ phải triển khai trên nhiều nền tảng khác nhau.

Để khắc phục điều đó thì CMake ra đời. CMake là một công cụ sinh Makefile đa nền tảng. Nói đơn giản thì CMake sẽ tự động tạo ra Makefiles cho project của chúng ta. Ngoài ra thì nó cũng làm được nhiều hơn nhưng trong khuôn khổ bài viết thì mình sẽ chỉ tập trung vào việc tự động sinh Makefiles cho các project C/C++.

## Ví dụ 1: Hello World
Code cho project này có thể tìm thấy ở thư mục. Trong ví dụ này thì một chương trình `Hello World` đơn giản sẽ được build (HelloWorld.cpp):
```
#include<iostream>

int main(int argc, char *argv[]){
   std::cout << "Hello World!" << std::endl;
   return 0;
}
```
Ngoài file `HelloWorld.cpp` ra thì chúng ta sẽ cần đến một file khác ở cùng thư mục là `CMakeLists.txt` có nội dung như sau:
```
cmake_minimum_required(VERSION 2.8.9)
project (hello)
add_executable(hello helloworld.cpp)
```
File này chỉ có 3 dòng và có ý nghĩa như sau:

- Dòng đầu tiên sẽ định nghĩa phiên bản thấp nhất của CMake dành cho project này.

- Dòng thứ hai sử dụng lệnh `project()` để đặt tên cho project.

- Dòng thứ ba là lệnh `add_executable()`. Lệnh này nhằm mục đích tạo thêm một executable. Đối số đầu truyền vào là tên của executable sẽ được tạo, đối số thứ hai là source file sẽ được dùng để build executable.

Để build project thì hãy chắc chắn rằng CMake đã được cài đặt trên máy. Nếu hệ điều hành của bạn là một flavor của Linux thì hãy cài dặt nó thông qua package manager, ví dụ như với Ubuntu:
```
FRAMGIA\luong.the.vinh@framgia0221-pc:~$ sudo apt-get install cmake
FRAMGIA\luong.the.vinh@framgia0221-pc:~$ cmake -version
cmake version 3.5.1
```
Điều hướng terminal đến thư mục chứa code project và check xem có đủ 2 file ở trên không:
```
FRAMGIA\luong.the.vinh@framgia0221-pc:~$ cd ~/Workspaces/Examples/exploringBB/extras/cmake/helloworld/
FRAMGIA\luong.the.vinh@framgia0221-pc:~/Workspaces/Examples/exploringBB/extras/cmake/helloworld$ ls
CMakeLists.txt  helloworld.cpp
```
Bây giờ thì chúng ta đã sẵn sàng để build project HelloWorld sử dụng CMake. Chúng ta sẽ thực thi lệnh `cmake` kèm đường dẫn chứa source code và file CmakeLists.txt. Trong trường hợp này thì "." sẽ dùng để trỏ đến thư mục hiện tại:
```
FRAMGIA\luong.the.vinh@framgia0221-pc:~/Workspaces/Examples/exploringBB/extras/cmake/helloworld$ cmake .
-- The C compiler identification is GNU 5.4.0
-- The CXX compiler identification is GNU 5.4.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/luong.the.vinh/Workspaces/Examples/exploringBB/extras/cmake/helloworld
```
CMake sẽ xác định cấu hình môi trường được cài đặt trên máy và tạo một file Makefile cho project này. Chúng ta có thể xem và edit Makefile được tạo này, tuy nhiên thì những sự thay đổi chúng ta tạo ra sẽ bị ghi đè lại mỗi lần chúng ta chạy lại lệnh `cmake`.

Một khi Makefile đã được tạo thì chúng ta sẽ dùng lệnh `make` để build project:
```
FRAMGIA\luong.the.vinh@framgia0221-pc:~/Workspaces/Examples/exploringBB/extras/cmake/helloworld$ make
Scanning dependencies of target hello
[ 50%] Building CXX object CMakeFiles/hello.dir/helloworld.cpp.o
[100%] Linking CXX executable hello
[100%] Built target hello
FRAMGIA\luong.the.vinh@framgia0221-pc:~/Workspaces/Examples/exploringBB/extras/cmake/helloworld$ ls -l hello
-rwxr-xr-x 1 FRAMGIA\luong.the.vinh FRAMGIA\domain^users 9224 Th08 20 09:58 hello
FRAMGIA\luong.the.vinh@framgia0221-pc:~/Workspaces/Examples/exploringBB/extras/cmake/helloworld$ ./hello
Hello World!
```
Project chúng ta build đã chạy! Như các bạn thấy thì quá trình build chương trình HelloWorld.cpp này thực sự có hơi rườm rà nhưng lại rất quan trọng đối với những người mới học bởi nó giải thích các hoạt động cơ bản của CMake. Bây giờ thì chúng ta đã sẵn sàng xem xét đến một số ví dụ CMake phức tạp hơn.
## Ví dụ 2: Một project với nhiều directory
Khi project của chúng ta bắt đầu phình to thì chúng ta sẽ muốn quản lý chúng dưới dạng nhiều sub-directory. Việc sử dụng Makeflies trở nên khá dài dòng khi có sự hiện diện của sub-directories do trong thực tế thì việc tạo một Makefile trong mỗi sub-directory là việc rất phổ biến. Các Makefile này sau đó sẽ được gọi bởi Makefile trong thư mục cha.

Cmake sẽ tỏ ra rất hữu dụng trong trường hợp này. Trong ví dụ này thì một project với cấu trúc thư mục điển hình sẽ được sử dụng. Chúng ta sẽ điều hướng terminal đến thư mục `/exploringBB/extras/cmake/student` có cấu trúc thư mục như sau:
```
FRAMGIA\luong.the.vinh@framgia0221-pc:~/Workspaces/Examples/exploringBB/extras/cmake/student$ tree
.
├── build
├── CMakeLists.txt
├── include
│   └── Student.h
└── src
    ├── mainapp.cpp
    └── Student.cpp

3 directories, 4 files
```
Các bạn có thể thấy là tất cả các file header (.h) được đặt trong thư mục `include` và tất cả các file mã nguồn (.cpp) được đặt trong thư mục `src`. Ngoài ra thì có cả thư mục `build` (hiện đang rỗng) được sử dụng để chứa các file binary executable và các file tạm cần thiết cho quá trình build. File CmakeLists.txt cho project này sẽ có một chút khác biệt so với file được sử dụng trong ví dụ 1:
```
cmake_minimum_required(VERSION 2.8.9)
project(directory_test)

include_directories(include)

#set(SOURCES src/mainapp.cpp src/Student.cpp)

file(GLOB SOURCES "src/*.cpp")

add_executable(testStudent ${SOURCES})
```
Các thay đổi quan trọng trong file CMake này là như sau:

- Hàm `include_directories()` được sử dụng để tích hợp các file header vào trong môi trường build.
- Hàm `set(SOURCE...)` có thể được sử dụng để đặt một biến (SOURCE) chứa tất cả tên của các file source (.cpp) trong project. Tuy nhiên thì bởi mỗi một file source cần được thêm một cách thủ công nên dòng tiếp theo sẽ được dùng thay thế lệnh này và hàm set sẽ bị comment lại.
- Hàm `file()` được sử dụng để thêm source file vào project. `GLOB` (hoặc `GLOB_RECURSE`) sẽ được sử dụng để tạo một danh sách các file thỏa mãn expression được khai báo (ví dụ: `src/*.cpp`) và thêm chúng vào biến SOURCE.
- Hàm `add_executable()` sử dụng biến `SOURCE` thay vì việc sử dụng tham chiếu cụ thể của từng source file để build một chương trình executable là `testStudent`.

Trong ví dụ này thì tất cả các file build sẽ được đặt ở trong thư mục `build`. Chúng ta có thể làm việc này một cách dễ dàng bằng cách gọi `cmake` từ thư mục `build` như sau:
```
FRAMGIA\luong.the.vinh@framgia0221-pc:~/Workspaces/Examples/exploringBB/extras/cmake/student$ cd build
FRAMGIA\luong.the.vinh@framgia0221-pc:~/Workspaces/Examples/exploringBB/extras/cmake/student/build$ cmake ..
-- The C compiler identification is GNU 5.4.0
-- The CXX compiler identification is GNU 5.4.0
...
```
Thư mục `build` lúc này sẽ bao gồm Makefile cho project, Makefile sẽ tham chiếu chính xác đến các file trong thư mục `src` và `include`. Project lúc này sẽ có thể được build từ thư mục `build` sử dụng lệnh `make`
```
FRAMGIA\luong.the.vinh@framgia0221-pc:~/Workspaces/Examples/exploringBB/extras/cmake/student/build$ ls
CMakeCache.txt  CMakeFiles  cmake_install.cmake  Makefile
FRAMGIA\luong.the.vinh@framgia0221-pc:~/Workspaces/Examples/exploringBB/extras/cmake/student/build$ make
...
FRAMGIA\luong.the.vinh@framgia0221-pc:~/Workspaces/Examples/exploringBB/extras/cmake/student/build$ ls
CMakeCache.txt  CMakeFiles  cmake_install.cmake  Makefile  testStudent
FRAMGIA\luong.the.vinh@framgia0221-pc:~/Workspaces/Examples/exploringBB/extras/cmake/student/build$ ./testStudent
A student with name Joe

```
Một ưu điểm dễ thấy của cách tiếp cận này là tất cả các file liên quan đến quá trình build đều nằm trong thư mục build. Để clean project thì chúng ta đơn giản là chỉ cần xóa đệ quy tất cả files/directories nằm trong thư mục build, ví dụ:
```
FRAMGIA\luong.the.vinh@framgia0221-pc:~/Workspaces/Examples/exploringBB/extras/cmake/student/build$ cd ..
FRAMGIA\luong.the.vinh@framgia0221-pc:~/Workspaces/Examples/exploringBB/extras/cmake/student$ rm -r build/*
FRAMGIA\luong.the.vinh@framgia0221-pc:~/Workspaces/Examples/exploringBB/extras/cmake/student$ tree
.
├── build
├── CMakeLists.txt
├── include
│   └── Student.h
└── src
    ├── mainapp.cpp
    └── Student.cpp

3 directories, 4 files

```
Như các bạn thấy thì cấu trúc cây thư mục của project là tương tự như trước khi `cmake` được thực thi.

**Lưu ý:** Mỗi lần thêm source file mới vào project thì chúng ta sẽ phải chạy lại `cmake`. Do chúng ta cần phải cập nhật lại Makefiles cho những thay đổi mới.

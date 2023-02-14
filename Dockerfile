FROM stateoftheartio/qt6:6.4-gcc-aqt

USER root
RUN apt-get update \
  && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
  clang-tidy file appstream gnupg2 libgl-dev libvulkan-dev wget zlib1g-dev python3-pip clazy libgtest-dev cmake clang lldb lld build-essential libglvnd-dev libgl1-mesa-dev

# Setup GTest
COPY GTest /usr/lib/x86_64-linux-gnu/cmake/GTest

COPY hello.cc /data/hello.cc
COPY Swagger/ /data/Swagger/




RUN cd /data/Swagger/ && export QT_SELECT=qt6 && cmake -G "Unix Makefiles" -DCMAKE_PREFIX_PATH=/usr/lib/llvm-10 -DCMAKE_CXX_COMPILER=clazy -DCMAKE_CXX=clazy

RUN apt-get update && apt-get -qy install         \
        libclang-10-dev		\
    --no-install-recommends

RUN git clone https://github.com/include-what-you-use/include-what-you-use.git
RUN cd include-what-you-use && git checkout clang_10 && cd .. && mkdir build && cd build && cmake -G "Unix Makefiles" -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DCMAKE_PREFIX_PATH=/usr/lib/llvm-10 ../include-what-you-use && make && make install


RUN apt-get update && apt-get -qy install         \
        python		\
    --no-install-recommends


RUN echo $(clazy-standalone --version)
RUN cd /data/Swagger/ && mkdir build && cd build && CC="clang" CXX="clang++" cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .. && iwyu_tool.py -p ..
# ADD "https://www.random.org/cgi-bin/randbyte?nbytes=10&format=h" skipcache

RUN wget https://github.com/KDE/clazy/archive/refs/tags/v1.11.tar.gz && tar -xvf v1.11.tar.gz && cd clazy-1.11/ && cmake -DCMAKE_PREFIX_PATH=/usr/lib/llvm-10 -DCMAKE_BUILD_TYPE=Release -G Ninja && cmake --build . && cmake --build . --target install
RUN cd /data/Swagger/ && cd build && CC="clang" CXX="clang++" CLANGXX=clang++-10 cmake -DCMAKE_PREFIX_PATH=/usr/lib/llvm-10 -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .. && cd .. && find . -name "*cpp" | xargs clazy-standalone -checks=level2 -p compile_commands.json
RUN cd /data/Swagger/ && cd build && CC="clang" CXX="clazy" cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .. && cd .. && find . -name "*cpp" | xargs clang-tidy -checks=-*,clang-analyzer-*,-clang-analyzer-cplusplus* -p compile_commands.json

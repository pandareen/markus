FROM stateoftheartio/qt6:6.4-gcc-aqt

USER root
RUN apt-get update \
  && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
  clang-tidy libgtest-dev libclang-10-dev clang-format python file clang-tools-6.0 appstream gnupg2 libgl-dev libvulkan-dev wget zlib1g-dev python3-pip clazy libgtest-dev cmake clang lldb lld build-essential libglvnd-dev libgl1-mesa-dev


# # Setup GTest
COPY GTest /usr/lib/x86_64-linux-gnu/cmake/GTest

# COPY Swagger/ /data/Swagger/

ENV CC=clang
ENV CXX=clang++

# Install IWYU from source
RUN git clone https://github.com/include-what-you-use/include-what-you-use.git
RUN cd include-what-you-use && git checkout clang_10 && cd .. && mkdir build && cd build && cmake -G "Unix Makefiles" -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DCMAKE_PREFIX_PATH=/usr/lib/llvm-10 ../include-what-you-use && make && make install

# Install Clazy from source
RUN wget https://github.com/KDE/clazy/archive/refs/tags/v1.11.tar.gz && tar -xvf v1.11.tar.gz && cd clazy-1.11/ && cmake -DCMAKE_PREFIX_PATH=/usr/lib/llvm-10 -DCMAKE_BUILD_TYPE=Release -G Ninja && cmake --build . && cmake --build . --target install

# Running inspect and fix for CLAZY
#RUN cd /app/Swagger/ && export QT_SELECT=qt6 && cmake -G "Unix Makefiles" -DCMAKE_PREFIX_PATH=/usr/lib/llvm-10 -DCMAKE_CXX_COMPILER=clazy -DCMAKE_CXX=clazy -DCMAKE_EXPORT_COMPILE_COMMANDS=ON . && find . -name "*cpp" | xargs clazy-standalone -checks=level2 -export-fixes=/app/clazy-fixes.yaml -p compile_commands.json


# Running inspect and fix for IWYU
#RUN cd /app/Swagger/ && cmake -DCMAKE_PREFIX_PATH=/usr/lib/llvm-10 -DCMAKE_EXPORT_COMPILE_COMMANDS=ON . && iwyu_tool.py -p . | tee /app/iwyu-fixes.yaml

# Running inspect and fix for CLANG-TIDY
#RUN cd /app/Swagger/ && export QT_SELECT=qt6 && cmake -G "Unix Makefiles" -DCMAKE_PREFIX_PATH=/usr/lib/llvm-10 -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX=clang++ -DCMAKE_EXPORT_COMPILE_COMMANDS=ON . && find . -name "*cpp" | xargs clang-tidy --export-fixes=/app/clang-tidy-fixes.yaml -p compile_commands.json

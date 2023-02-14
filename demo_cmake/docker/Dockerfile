FROM stateoftheartio/qt6:6.4-gcc-aqt

USER root
RUN apt-get update \
  && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
  clang-tidy file appstream gnupg2 libgl-dev libvulkan-dev wget zlib1g-dev python3-pip libgtest-dev cmake build-essential libglvnd-dev libgl1-mesa-dev\
   && rm -rf /var/lib/apt/lists/*

# Setup GTest
COPY GTest /usr/lib/x86_64-linux-gnu/cmake/GTest

COPY hello.cc /data/hello.cc
COPY Swagger/ /data/Swagger/

RUN cd /data/Swagger/ && export QT_SELECT=qt6 && qmake -spec linux-clang QMAKE_CXX="clazy"
RUN aqt install-tool -O "$QT_PATH" linux desktop tools_ifw
RUN /usr/bin/python3 -m pip install --upgrade humanize
RUN /usr/bin/python3 -m pip install --upgrade PyGithub

# Make Qt6 libs from image available
RUN echo "/opt/Qt/6.4.0/gcc_64/lib" > /etc/ld.so.conf.d/qt.conf && ldconfig

COPY get_linuxdeploy_appimage.sh /tmp/
# Get linuxdeploy and build it
RUN /tmp/get_linuxdeploy_appimage.sh
RUN sudo wget https://github.com/AppImage/AppImageKit/releases/download/continuous/appimagetool-x86_64.AppImage -O /opt/appimagetool
RUN cd /opt/; sudo chmod +x appimagetool; sed -i 's|AI\x02|\x00\x00\x00|' appimagetool; sudo ./appimagetool --appimage-extract
RUN sudo mv /opt/squashfs-root /opt/appimagetool.AppDir
RUN sudo ln -s /opt/appimagetool.AppDir/AppRun /usr/local/bin/appimagetool
RUN git config --global --add safe.directory /app

ENV CMAKE_PREFIX_PATH=/usr/lib/x86_64-linux-gnu/cmake
ENV QT_QPA_PLATFORM=offscreen
ENV PATH="${PATH}:/opt"
ENV PATH="${PATH}:/usr/local/bin"
ENV PATH="${PATH}:/usr/bin"

RUN mkdir -p /app
RUN chown user /app

USER user
WORKDIR /app
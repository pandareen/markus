FROM ubuntu:latest

USER root

RUN apt-get update \
  && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
  libgl1-mesa-dev ca-certificates libfontconfig1

ENV QT_QPA_PLATFORM=offscreen
ENV APPIMAGE_EXTRACT_AND_RUN=1

RUN mkdir -p /start

ADD "https://www.random.org/cgi-bin/randbyte?nbytes=10&format=h" skipcache

COPY service.AppImage /start/service.AppImage


#RUN sudo wget https://github.com/AppImage/AppImageKit/releases/download/continuous/appimagetool-x86_64.AppImage -O /opt/appimagetool

RUN chmod +x /start/service.AppImage
#RUN sed -i 's|AI\x02|\x00\x00\x00|' /start/service.AppImage
RUN cd start;./service.AppImage --appimage-extract
RUN mv /start/squashfs-root /start/service.AppDir
RUN ln -s /start/service.AppDir/AppRun /usr/local/bin/service


ENV QT_QPA_PLATFORM=offscreen
ENV PATH="${PATH}:/opt"
ENV PATH="${PATH}:/usr/local/bin"
ENV PATH="${PATH}:/usr/bin"

WORKDIR /start/service.AppDir

CMD ./AppRun
FROM base/archlinux

MAINTAINER Sam Halliday, sam.halliday@gmail.com

ENV PATH /root/.jenv/shims:/root/.jenv/bin:$PATH
ENV COURSIER_VERBOSITY -1

ENV SCALA_VERSIONS 2.10.7 2.11.12 2.12.6
ENV SBT_VERSIONS 0.13.17 1.2.1

RUN \
  pacman -Sy --noconfirm jdk8-openjdk openjdk8-src sbt git &&\
  rm -rf /var/cache/pacman/pkg/ &&\
  git clone https://github.com/gcuisinier/jenv.git /root/.jenv &&\
  mkdir /root/.jenv/versions &&\
  jenv add /usr/lib/jvm/java-8-openjdk &&\
  jenv global 1.8

ENV JAVA_VERSIONS 1.8
# if I want to cross build java versions...
# ENV JAVA_VERSIONS 1.6 1.7 1.8
# RUN \
#   curl http://cdn.azul.com/zulu/bin/zulu6.19.0.1-jdk6.0.103-linux_x64.tar.gz -o jdk6.tar.gz &&\
#   mkdir /opt/zulu6 &&\
#   tar xf jdk6.tar.gz --strip-components=1 -C /opt/zulu6 &&\
#   rm jdk6.tar.gz &&\
#   pacman -Sy --noconfirm jdk7-openjdk openjdk7-src jdk9-openjdk openjdk9-src sbt git &&\
#   rm -rf /var/cache/pacman/pkg/ &&\
#   git clone https://github.com/gcuisinier/jenv.git /root/.jenv &&\
#   mkdir /root/.jenv/versions &&\
#   jenv add /opt/zulu6 &&\
#   jenv add /usr/lib/jvm/java-7-openjdk &&\
#   jenv add /usr/lib/jvm/java-9-openjdk

RUN \
  mkdir /tmp/sbt &&\
  cd /tmp/sbt &&\
  mkdir -p project project/project src/main/scala &&\
  touch src/main/scala/scratch.scala &&\
  for JAVA_VERSION in $JAVA_VERSIONS ; do\
  echo $JAVA_VERSION > .java-version ;\
  for SBT_VERSION in $SBT_VERSIONS ; do\
    echo "sbt.version=$SBT_VERSION" > project/build.properties &&\
    for SCALA_VERSION in $SCALA_VERSIONS ; do\
      echo "$JAVA_VERSION $SBT_VERSION $SCALA_VERSION" ;\
      sbt ++$SCALA_VERSION! clean update compile >/dev/null 2>&1 ;\
      echo 'addSbtPlugin("io.get-coursier" % "sbt-coursier" % "1.0.3")' > project/project/plugins.sbt ;\
      sbt ++$SCALA_VERSION! clean update compile >/dev/null 2>&1 ;\
      rm project/project/plugins.sbt >/dev/null 2>&1 ;\
    done ;\
  done ;\
  done &&\
  rm -rf /tmp/sbt /root/.coursier

# this image is optimised for running on gitlib ci with a cache for a custom
# coursier directory. ~/.coursier is ignored and all we care about is populating
# ~/.sbt, which we do not cache (gitlab only allows caching project files).

WORKDIR /root

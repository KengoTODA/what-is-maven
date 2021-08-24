FROM gitpod/workspace-full
RUN /home/gitpod/.sdkman/bin/sdkman-init.sh
RUN sdk install java 16.0.2-zulu

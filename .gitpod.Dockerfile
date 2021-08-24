FROM gitpod/workspace-full
RUN bash -c ". /home/gitpod/.sdkman/bin/sdkman-init.sh && sdk install java 16.0.2-zulu"

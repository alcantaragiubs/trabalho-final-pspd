FROM ubuntu:20.04 AS img

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y openssh-server \
    mpich mpich-doc \
    && \
    mkdir /var/run/sshd

# SSH server configuration.
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config
# SSH client configuration.
RUN echo "    StrictHostKeyChecking no" >> /etc/ssh/ssh_config
RUN echo "    UserKnownHostsFile /dev/null" >> /etc/ssh/ssh_config

COPY ./keys /root/.ssh/
COPY ./keys/id_rsa.pub /root/.ssh/authorized_keys
COPY ./hello.c /
COPY ./falha.c /

RUN mpicc hello.c -o hello
RUN mpicc falha.c -o falha

RUN chmod 700 /root/.ssh && chmod 600 /root/.ssh/authorized_keys

COPY setup.sh .
RUN chmod +x /setup.sh

CMD ["/usr/sbin/sshd", "-D"]